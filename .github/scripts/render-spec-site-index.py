#!/usr/bin/env python3
# Copyright 2025-2026, Contributors to the Grid Edge Interoperability & Security Alliance (GEISA), a Series of LF Projects, LLC.
# This file is licensed under the Community Specification License 1.0 available at:
# https://github.com/geisa/specification/blob/main/LICENSE.md or
# https://github.com/CommunitySpecification/Community_Specification/blob/main/1._Community_Specification_License-v1.md

import argparse
from functools import cmp_to_key
from datetime import datetime, timezone
import html
import json
import re
from pathlib import Path


SEMVER_RE = re.compile(
    r"^(?P<major>0|[1-9]\d*)\.(?P<minor>0|[1-9]\d*)\.(?P<patch>0|[1-9]\d*)"
    r"(?:-(?P<prerelease>[0-9A-Za-z]+(?:[.-][0-9A-Za-z]+)*))?"
    r"(?:\+(?P<build>[0-9A-Za-z]+(?:[.-][0-9A-Za-z]+)*))?$"
)


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description="Render the GEISA specification landing page."
    )
    parser.add_argument("--manifest", required=True, help="Path to release manifest JSON.")
    parser.add_argument("--output", required=True, help="Path to output HTML file.")
    parser.add_argument(
        "--latest-built-at",
        help="ISO-8601 build timestamp for the latest development draft.",
    )
    parser.add_argument(
        "--latest-source-version",
        help="Source version string used to build the latest development draft.",
    )
    return parser.parse_args()


def parse_semver(version: str) -> dict | None:
    match = SEMVER_RE.fullmatch(version)
    if not match:
        return None
    prerelease = match.group("prerelease")
    return {
        "major": int(match.group("major")),
        "minor": int(match.group("minor")),
        "patch": int(match.group("patch")),
        "prerelease": prerelease.split(".") if prerelease else [],
    }


def compare_prerelease_identifiers(left: str, right: str) -> int:
    left_numeric = left.isdigit()
    right_numeric = right.isdigit()
    if left_numeric and right_numeric:
        return (int(left) > int(right)) - (int(left) < int(right))
    if left_numeric != right_numeric:
        return -1 if left_numeric else 1
    return (left > right) - (left < right)


def compare_semver(left_version: str, right_version: str) -> int:
    left = parse_semver(left_version)
    right = parse_semver(right_version)
    if left is None or right is None:
        return (left_version > right_version) - (left_version < right_version)

    for field in ("major", "minor", "patch"):
        if left[field] != right[field]:
            return (left[field] > right[field]) - (left[field] < right[field])

    left_prerelease = left["prerelease"]
    right_prerelease = right["prerelease"]
    if not left_prerelease and not right_prerelease:
        return 0
    if not left_prerelease:
        return 1
    if not right_prerelease:
        return -1

    for left_identifier, right_identifier in zip(left_prerelease, right_prerelease):
        compare_result = compare_prerelease_identifiers(left_identifier, right_identifier)
        if compare_result != 0:
            return compare_result

    return (len(left_prerelease) > len(right_prerelease)) - (
        len(left_prerelease) < len(right_prerelease)
    )


def compare_releases(left: dict, right: dict) -> int:
    return compare_semver(left["version"], right["version"])


def load_releases(manifest_path: Path) -> list[dict]:
    releases = json.loads(manifest_path.read_text(encoding="utf-8"))
    releases.sort(key=cmp_to_key(compare_releases), reverse=True)
    return releases


def release_label(release: dict) -> str:
    version = release["version"]
    match = SEMVER_RE.fullmatch(version)
    if match and int(match.group("major")) == 0:
        return "Draft Release"
    if release.get("prerelease"):
        return "Prerelease"
    return "Release"


def current_official_release(releases: list[dict]) -> dict | None:
    return releases[0] if releases else None


def parse_iso8601(timestamp: str) -> datetime | None:
    try:
        parsed = datetime.fromisoformat(timestamp.replace("Z", "+00:00"))
    except ValueError:
        return None
    if parsed.tzinfo is None or parsed.utcoffset() is None:
        return None
    return parsed


def format_release_date(release: dict) -> str | None:
    published_at = release.get("published_at")
    if not published_at:
        return None
    published_dt = parse_iso8601(published_at)
    if published_dt is None:
        return None
    return f"Published: {published_dt.strftime('%B')} {published_dt.day}, {published_dt.year}"


def format_latest_build_time(latest_built_at: str | None) -> str | None:
    if not latest_built_at:
        return None
    built_dt = parse_iso8601(latest_built_at)
    if built_dt is None:
        raise ValueError(f"latest build timestamp must include timezone offset or Z: {latest_built_at}")
    built_dt = built_dt.astimezone(timezone.utc)
    return (
        f"Built: {built_dt.strftime('%B')} {built_dt.day}, {built_dt.year} "
        f"at {built_dt.strftime('%H:%M')} UTC"
    )


def format_latest_source_version(latest_source_version: str | None) -> str | None:
    if not latest_source_version:
        return None
    return latest_source_version.strip() or None


def build_release_items(releases: list[dict]) -> str:
    if not releases:
        return (
            '<li class="release-item">'
            '<div><strong>No published releases yet</strong>'
            "<p>Published versioned releases will appear here automatically.</p>"
            "</div>"
            "</li>"
        )

    items = []
    for release in releases:
        version = html.escape(release["version"])
        url = html.escape(release["html_url"])
        label = html.escape(release_label(release))
        published_date = format_release_date(release)
        published_markup = f"<p>{html.escape(published_date)}</p>" if published_date else ""
        items.append(
            f"""
            <li class="release-item">
              <div>
                <strong>GEISA Specification {version}</strong>
                <p>{label} built from tag {html.escape(release["tag_name"])}.</p>
                {published_markup}
              </div>
              <div class="release-links">
                <a href="./{version}/index.html">HTML</a>
                <a href="./{version}/downloads/geisaspecification.pdf">PDF</a>
                <a href="{url}">GitHub release</a>
              </div>
            </li>
            """.strip()
        )
    return "\n".join(items)


def render_current_panel(release: dict | None) -> str:
    if release is None:
        return """
        <section class="panel" aria-labelledby="current-release-heading">
          <div class="section-label">Current official release</div>
          <h2 id="current-release-heading">No published GEISA release yet</h2>
          <p>
            Published GitHub releases will appear here automatically after they
            are released.
          </p>
        </section>
        """.strip()

    current_version = html.escape(release["version"])
    current_release_url = html.escape(release["html_url"])
    current_label = html.escape(release_label(release))
    published_date = format_release_date(release)
    published_markup = f"\n          <p>{html.escape(published_date)}</p>" if published_date else ""
    return f"""
        <section class="panel" aria-labelledby="current-release-heading">
          <div class="section-label">Current official release</div>
          <h2 id="current-release-heading">GEISA Specification {current_version} {current_label}</h2>
          <p>
            This is the newest published GEISA specification release. It is built
            from tag {html.escape(release["tag_name"])} and remains fixed while
            development continues on <code>main</code>.
          </p>{published_markup}
          <div class="actions">
            <a class="button" href="./{current_version}/index.html">Open HTML</a>
            <a class="button secondary" href="./{current_version}/downloads/geisaspecification.pdf">Download PDF</a>
            <a class="button secondary" href="{current_release_url}">Release notes</a>
          </div>
        </section>
    """.strip()


def render_html(
    releases: list[dict],
    latest_built_at: str | None,
    latest_source_version: str | None,
) -> str:
    current = current_official_release(releases)
    latest_built_time = format_latest_build_time(latest_built_at)
    latest_source_version = format_latest_source_version(latest_source_version)
    latest_built_markup = (
        f"\n          <p>{html.escape(latest_built_time)}</p>"
        if latest_built_time
        else ""
    )
    latest_source_version_markup = (
        f"\n          <p>Version: <code>{html.escape(latest_source_version)}</code></p>"
        if latest_source_version
        else ""
    )
    release_items = build_release_items(releases)
    current_panel = render_current_panel(current)

    return f"""<!doctype html>
<html lang="en">
<head>
  <meta charset="utf-8">
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <title>GEISA Specification</title>
  <style>
    :root {{
      color-scheme: light;
      --geisa-blue: #1f5f99;
      --geisa-blue-dark: #16456f;
      --geisa-green: #00a885;
      --text: #1f2933;
      --muted: #52606d;
      --border: #d9e2ec;
      --background: #f5f7fa;
      --card: #ffffff;
      --accent-bg: #eef7f4;
    }}

    * {{
      box-sizing: border-box;
    }}

    body {{
      margin: 0;
      background: var(--background);
      color: var(--text);
      font-family: -apple-system, BlinkMacSystemFont, "Segoe UI", sans-serif;
      line-height: 1.5;
    }}

    main {{
      max-width: 1280px;
      margin: 0 auto;
      padding: 48px 32px;
    }}

    .hero {{
      background: var(--card);
      border: 1px solid var(--border);
      border-radius: 18px;
      box-shadow: 0 16px 40px rgba(31, 41, 51, 0.08);
      padding: clamp(32px, 5vw, 56px);
    }}

    .brand {{
      display: flex;
      align-items: center;
      gap: 20px;
      margin-bottom: 24px;
    }}

    .brand img {{
      width: clamp(120px, 16vw, 220px);
      height: auto;
    }}

    .eyebrow {{
      color: var(--geisa-blue);
      font-size: 0.82rem;
      font-weight: 700;
      letter-spacing: 0.08em;
      text-transform: uppercase;
    }}

    h1 {{
      margin: 0.2em 0 0;
      color: var(--geisa-blue-dark);
      font-size: clamp(2rem, 5vw, 3.2rem);
      line-height: 1.05;
    }}

    h2 {{
      margin: 6px 0 8px;
      color: var(--geisa-blue-dark);
      font-size: clamp(1.45rem, 3vw, 2.1rem);
    }}

    .summary,
    .panel p,
    .release-item p,
    footer {{
      color: var(--muted);
    }}

    .summary {{
      font-size: 1.1rem;
      max-width: none;
    }}

    .sections {{
      display: grid;
      gap: 22px;
      margin-top: 32px;
    }}

    .panel {{
      padding: 22px 24px;
      background: var(--accent-bg);
      border: 1px solid rgba(0, 168, 133, 0.35);
      border-left: 6px solid var(--geisa-green);
      border-radius: 14px;
    }}

    .section-label {{
      color: var(--geisa-blue-dark);
      font-size: 0.82rem;
      font-weight: 800;
      letter-spacing: 0.08em;
      text-transform: uppercase;
    }}

    .actions {{
      display: flex;
      flex-wrap: wrap;
      gap: 12px;
      margin-top: 18px;
    }}

    a.button {{
      display: inline-block;
      padding: 12px 18px;
      border-radius: 10px;
      color: #ffffff;
      background: var(--geisa-blue);
      font-weight: 700;
      text-decoration: none;
    }}

    a.button.secondary {{
      color: var(--geisa-blue-dark);
      background: #e6f0f8;
    }}

    a.button:hover {{
      background: var(--geisa-blue-dark);
    }}

    a.button.secondary:hover {{
      color: #ffffff;
    }}

    .release-list {{
      list-style: none;
      margin: 18px 0 0;
      padding: 0;
      display: grid;
      gap: 14px;
    }}

    .release-item {{
      display: flex;
      justify-content: space-between;
      gap: 20px;
      padding: 16px;
      background: #fbfcfd;
      border: 1px solid var(--border);
      border-radius: 12px;
    }}

    .release-links {{
      display: flex;
      flex-wrap: wrap;
      gap: 12px;
      align-items: flex-start;
    }}

    .release-links a,
    .links a {{
      color: var(--geisa-blue-dark);
      font-weight: 700;
      text-decoration: none;
    }}

    .links {{
      display: grid;
      grid-template-columns: repeat(auto-fit, minmax(210px, 1fr));
      gap: 14px;
      margin-top: 28px;
    }}

    .link-card {{
      padding: 16px;
      background: #fbfcfd;
      border: 1px solid var(--border);
      border-radius: 12px;
    }}

    footer {{
      margin-top: 28px;
      font-size: 0.9rem;
    }}

    @media (max-width: 720px) {{
      .brand,
      .release-item {{
        flex-direction: column;
      }}
    }}
  </style>
</head>
<body>
  <main>
    <section class="hero">
      <div class="brand">
        <img src="./assets/geisa-pyramid.svg" alt="GEISA logo">
        <div>
          <div class="eyebrow">Grid Edge Interoperability &amp; Security Alliance</div>
          <h1>GEISA Specification</h1>
        </div>
      </div>

      <p class="summary">
        GEISA defines a consistent, secure, and interoperable computing
        environment for devices at the edge of the electric grid.
      </p>

      <div class="sections">
        {current_panel}

        <section class="panel" aria-labelledby="latest-draft-heading">
          <div class="section-label">Latest development draft</div>
          <h2 id="latest-draft-heading">Current unreleased draft</h2>
          <p>
            This draft is rebuilt from <code>main</code> on each publication and
            may include changes newer
            than the current official release.
          </p>{latest_source_version_markup}{latest_built_markup}
          <div class="actions">
            <a class="button" href="./latest/index.html">Open HTML</a>
            <a class="button secondary" href="./latest/downloads/geisaspecification.pdf">Download PDF</a>
          </div>
        </section>

        <section class="panel" aria-labelledby="available-releases-heading">
          <div class="section-label">Available releases</div>
          <h2 id="available-releases-heading">Published versions</h2>
          <ul class="release-list">
            {release_items}
          </ul>
        </section>
      </div>

      <div class="links">
        <div class="link-card">
          <a href="https://github.com/geisa">GEISA on GitHub</a>
          <p>Organization home, repositories, and project materials.</p>
        </div>
        <div class="link-card">
          <a href="https://github.com/geisa/specification">Specification repository</a>
          <p>Source repository for the latest draft and versioned releases.</p>
        </div>
        <div class="link-card">
          <a href="https://github.com/geisa/schemas">Schemas repository</a>
          <p>Schema and protobuf definitions for GEISA transactions.</p>
        </div>
        <div class="link-card">
          <a href="https://lfenergy.org/projects/geisa/">LF Energy GEISA project page</a>
          <p>General project information and LF Energy context.</p>
        </div>
      </div>
    </section>

    <footer>
      Copyright 2025-2026, Contributors to the Grid Edge Interoperability
      &amp; Security Alliance (GEISA), a Series of LF Projects, LLC.
    </footer>
  </main>
</body>
</html>
"""


def main() -> None:
    args = parse_args()
    releases = load_releases(Path(args.manifest))
    output_path = Path(args.output)
    output_path.parent.mkdir(parents=True, exist_ok=True)
    output_path.write_text(
        render_html(
            releases,
            args.latest_built_at,
            args.latest_source_version,
        ),
        encoding="utf-8",
    )


if __name__ == "__main__":
    main()
