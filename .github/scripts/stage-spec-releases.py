#!/usr/bin/env python3
# Copyright 2025-2026, Contributors to the Grid Edge Interoperability & Security Alliance (GEISA), a Series of LF Projects, LLC.
# This file is licensed under the Community Specification License 1.0 available at:
# https://github.com/geisa/specification/blob/main/LICENSE.md or
# https://github.com/CommunitySpecification/Community_Specification/blob/main/1._Community_Specification_License-v1.md

import argparse
import json
import os
import re
import shutil
import subprocess
import sys
from datetime import datetime
from pathlib import Path


SEMVER_RE = re.compile(
    r"^(?P<version>"
    r"(?P<major>0|[1-9]\d*)\.(?P<minor>0|[1-9]\d*)\.(?P<patch>0|[1-9]\d*)"
    r"(?:-(?P<prerelease>[0-9A-Za-z]+(?:[.-][0-9A-Za-z]+)*))?"
    r"(?:\+(?P<build>[0-9A-Za-z]+(?:[.-][0-9A-Za-z]+)*))?"
    r")$"
)
RESERVED_VERSIONS = {"latest", "assets", "downloads"}


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description="Build and stage published GEISA specification releases."
    )
    parser.add_argument("--manifest", required=True, help="Path to release manifest JSON.")
    parser.add_argument("--repo", required=True, help="Path to repository checkout.")
    parser.add_argument("--pages-dir", required=True, help="Path to Pages staging directory.")
    parser.add_argument("--work-dir", required=True, help="Temporary directory for worktrees.")
    return parser.parse_args()


def load_manifest(path: Path) -> object:
    return json.loads(path.read_text(encoding="utf-8"))


def run(
    command: list[str],
    *,
    cwd: Path | None = None,
    env: dict[str, str] | None = None,
    capture_output: bool = False,
) -> subprocess.CompletedProcess[str]:
    return subprocess.run(
        command,
        cwd=cwd,
        env=env,
        check=True,
        text=True,
        capture_output=capture_output,
    )


def parse_iso8601(timestamp: str) -> datetime:
    try:
        parsed = datetime.fromisoformat(timestamp.replace("Z", "+00:00"))
    except ValueError as exc:
        raise ValueError(f"invalid ISO-8601 timestamp: {timestamp}") from exc
    if parsed.tzinfo is None or parsed.utcoffset() is None:
        raise ValueError(f"timestamp must include timezone offset or Z: {timestamp}")
    return parsed


def normalize_tag(tag_name: str) -> str:
    match = SEMVER_RE.fullmatch(tag_name.removeprefix("v"))
    if not match:
        raise ValueError(
            f"unsupported release tag {tag_name!r}; expected optional leading 'v' and a semantic version"
        )
    return match.group("version")


def validate_manifest_entry(entry: object, index: int) -> dict:
    if not isinstance(entry, dict):
        raise ValueError(f"manifest entry {index} must be a JSON object")

    required_fields = {"tag_name", "version", "prerelease", "html_url", "published_at"}
    missing_fields = sorted(required_fields - set(entry))
    if missing_fields:
        raise ValueError(f"manifest entry {index} is missing required fields: {', '.join(missing_fields)}")

    for field_name in ("tag_name", "version", "html_url", "published_at"):
        field_value = entry[field_name]
        if not isinstance(field_value, str) or not field_value.strip():
            raise ValueError(f"manifest entry {index} field {field_name!r} must be a non-empty string")

    if not isinstance(entry["prerelease"], bool):
        raise ValueError(f"manifest entry {index} field 'prerelease' must be a boolean")

    tag_name = entry["tag_name"].strip()
    version = entry["version"].strip()
    normalized_version = normalize_tag(tag_name)
    if normalized_version != version:
        raise ValueError(
            f"manifest entry {index} tag/version mismatch: tag {tag_name!r} normalizes to "
            f"{normalized_version!r}, manifest version is {version!r}"
        )

    if version in RESERVED_VERSIONS:
        raise ValueError(f"manifest entry {index} version {version!r} uses reserved site directory name")

    version_path = Path(version)
    if version_path.name != version or version_path.parts != (version,):
        raise ValueError(f"manifest entry {index} version {version!r} is not a single safe path component")

    if any(token in version for token in ("/", "\\")) or version in {".", ".."} or ".." in version_path.parts:
        raise ValueError(f"manifest entry {index} version {version!r} contains path traversal or separators")

    parse_iso8601(entry["published_at"].strip())

    return {
        "tag_name": tag_name,
        "version": version,
        "prerelease": entry["prerelease"],
        "html_url": entry["html_url"].strip(),
        "published_at": entry["published_at"].strip(),
    }


def validate_manifest(manifest: object) -> list[dict]:
    if not isinstance(manifest, list):
        raise ValueError("release manifest top level must be a JSON list")

    validated_entries: list[dict] = []
    seen_tags: set[str] = set()
    seen_versions: set[str] = set()

    for index, entry in enumerate(manifest):
        validated_entry = validate_manifest_entry(entry, index)
        tag_name = validated_entry["tag_name"]
        version = validated_entry["version"]

        if tag_name in seen_tags:
            raise ValueError(f"duplicate release tag in manifest: {tag_name}")
        if version in seen_versions:
            raise ValueError(f"duplicate normalized release version in manifest: {version}")

        seen_tags.add(tag_name)
        seen_versions.add(version)
        validated_entries.append(validated_entry)

    return validated_entries


def ensure_release_outputs(worktree: Path) -> None:
    html_index = worktree / "build" / "html" / "index.html"
    pdf_path = worktree / "build" / "latex" / "geisaspecification.pdf"
    if not html_index.is_file():
        raise RuntimeError(f"missing HTML output file {html_index}")
    if not pdf_path.is_file():
        raise RuntimeError(f"missing PDF output file {pdf_path}")
    if pdf_path.stat().st_size == 0:
        raise RuntimeError(f"empty PDF output file {pdf_path}")


def ensure_staged_release_outputs(staged_release_dir: Path) -> None:
    html_index = staged_release_dir / "index.html"
    pdf_path = staged_release_dir / "downloads" / "geisaspecification.pdf"
    if not html_index.is_file():
        raise RuntimeError(f"missing staged HTML output file {html_index}")
    if not pdf_path.is_file():
        raise RuntimeError(f"missing staged PDF output file {pdf_path}")
    if pdf_path.stat().st_size == 0:
        raise RuntimeError(f"empty staged PDF output file {pdf_path}")


def assert_within_work_dir(work_dir: Path, worktree: Path) -> None:
    resolved_work_dir = work_dir.resolve()
    resolved_worktree = worktree.resolve()
    if resolved_work_dir not in resolved_worktree.parents:
        raise RuntimeError(f"refusing to clean worktree outside configured work dir: {resolved_worktree}")


def assert_within_pages_dir(pages_dir: Path, target: Path) -> None:
    resolved_pages_dir = pages_dir.resolve()
    resolved_target = target.resolve(strict=False)
    if resolved_target != resolved_pages_dir and resolved_pages_dir not in resolved_target.parents:
        raise RuntimeError(f"refusing to stage outside Pages dir: {resolved_target}")


def registered_worktrees(repo: Path, env: dict[str, str]) -> dict[Path, bool]:
    result = run(
        ["git", "worktree", "list", "--porcelain"],
        cwd=repo,
        env=env,
        capture_output=True,
    )
    worktrees: dict[Path, bool] = {}
    current_path: Path | None = None
    is_prunable = False
    for line in result.stdout.splitlines():
        if not line:
            if current_path is not None:
                worktrees[current_path] = is_prunable
            current_path = None
            is_prunable = False
            continue
        if line.startswith("worktree "):
            current_path = Path(line.removeprefix("worktree ")).resolve(strict=False)
            is_prunable = False
            continue
        if line.startswith("prunable "):
            is_prunable = True
    if current_path is not None:
        worktrees[current_path] = is_prunable
    return worktrees


def prune_worktrees(repo: Path, env: dict[str, str]) -> None:
    run(["git", "worktree", "prune"], cwd=repo, env=env)


def cleanup_worktree(repo: Path, work_dir: Path, worktree: Path, env: dict[str, str]) -> None:
    assert_within_work_dir(work_dir, worktree)
    worktree = worktree.resolve(strict=False)
    cleanup_errors: list[str] = []
    worktrees = registered_worktrees(repo, env)
    is_registered = worktree in worktrees

    if is_registered and worktree.exists():
        try:
            run(["git", "worktree", "remove", "--force", str(worktree)], cwd=repo, env=env)
        except subprocess.CalledProcessError as exc:
            cleanup_errors.append(f"git worktree remove failed for {worktree}: {exc}")
    elif worktree.exists():
        try:
            shutil.rmtree(worktree)
        except OSError as exc:
            cleanup_errors.append(f"filesystem cleanup failed for {worktree}: {exc}")

    try:
        if is_registered or not worktree.exists():
            prune_worktrees(repo, env)
    except subprocess.CalledProcessError as exc:
        cleanup_errors.append(f"git worktree prune failed: {exc}")

    if cleanup_errors:
        raise RuntimeError("; ".join(cleanup_errors))


def stage_release(worktree: Path, pages_dir: Path, version: str) -> None:
    release_dir = pages_dir / version
    temp_dir = pages_dir / f".{version}.tmp"
    backup_dir = pages_dir / f".{version}.bak"
    downloads_dir = temp_dir / "downloads"
    backup_preserved = False
    backup_holds_prior_release = False

    assert_within_pages_dir(pages_dir, temp_dir)
    assert_within_pages_dir(pages_dir, backup_dir)
    assert_within_pages_dir(pages_dir, release_dir)

    if temp_dir.exists():
        shutil.rmtree(temp_dir)
    if backup_dir.exists():
        shutil.rmtree(backup_dir)

    try:
        downloads_dir.mkdir(parents=True, exist_ok=True)
        shutil.copytree(worktree / "build" / "html", temp_dir, dirs_exist_ok=True)
        shutil.copy2(
            worktree / "build" / "latex" / "geisaspecification.pdf",
            downloads_dir / "geisaspecification.pdf",
        )
        ensure_staged_release_outputs(temp_dir)

        if release_dir.exists():
            release_dir.replace(backup_dir)
            backup_holds_prior_release = True
        if os.environ.get("GEISA_STAGE_RELEASE_FAIL_INSTALL") == version:
            raise RuntimeError(f"forced release-directory install failure for {version}")
        temp_dir.replace(release_dir)
        if backup_dir.exists():
            shutil.rmtree(backup_dir)
            backup_holds_prior_release = False
    except BaseException as install_error:
        if backup_holds_prior_release and not release_dir.exists() and backup_dir.exists():
            try:
                if os.environ.get("GEISA_STAGE_RELEASE_FAIL_RESTORE") == version:
                    raise RuntimeError(f"forced release-directory restore failure for {version}")
                backup_dir.replace(release_dir)
                backup_holds_prior_release = False
            except BaseException as restore_error:
                backup_preserved = True
                raise RuntimeError(
                    f"release install failed: {install_error}; "
                    f"backup restore failed: {restore_error}; "
                    f"preserved backup: {backup_dir}"
                ) from install_error
        raise
    finally:
        if temp_dir.exists():
            shutil.rmtree(temp_dir)
        if backup_dir.exists() and not (backup_holds_prior_release or backup_preserved):
            shutil.rmtree(backup_dir)


def main() -> None:
    args = parse_args()
    repo = Path(args.repo).resolve()
    pages_dir = Path(args.pages_dir).resolve()
    work_dir = Path(args.work_dir).resolve()
    work_dir.mkdir(parents=True, exist_ok=True)

    releases = validate_manifest(load_manifest(Path(args.manifest)))

    env = os.environ.copy()
    env["PATH"] = f"{repo / 'venv' / 'bin'}:{repo / '.github' / 'bin'}:{env['PATH']}"
    build_command = ["make", "clean", "all"]
    if shutil.which("xvfb-run", path=env["PATH"]):
        build_command = ["xvfb-run", "-a", "make", "clean", "all"]

    prune_worktrees(repo, env)

    for release in releases:
        version = release["version"]
        tag_name = release["tag_name"]
        worktree = work_dir / version
        if worktree.exists():
            cleanup_worktree(repo, work_dir, worktree, env)

        run(
            ["git", "worktree", "add", "--detach", str(worktree), f"refs/tags/{tag_name}"],
            cwd=repo,
            env=env,
        )

        build_error: BaseException | None = None
        cleanup_error: BaseException | None = None
        try:
            run(build_command, cwd=worktree, env=env)
            ensure_release_outputs(worktree)
            stage_release(worktree, pages_dir, version)
        except BaseException as exc:
            build_error = exc
        finally:
            try:
                cleanup_worktree(repo, work_dir, worktree, env)
            except BaseException as exc:
                cleanup_error = exc

        if build_error is not None:
            if cleanup_error is not None:
                print(f"cleanup after build failure also failed: {cleanup_error}", file=sys.stderr)
            raise build_error

        if cleanup_error is not None:
            raise cleanup_error


if __name__ == "__main__":
    main()
