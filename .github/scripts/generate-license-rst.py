#!/usr/bin/env python3
# Copyright 2025-2026, Contributors to the Grid Edge Interoperability & Security Alliance (GEISA), a Series of LF Projects, LLC.
# This file is licensed under the Community Specification License 1.0 available at:
# https://github.com/geisa/specification/blob/main/LICENSE.md or
# https://github.com/CommunitySpecification/Community_Specification/blob/main/01-community-specification-license-v1.md

from __future__ import annotations

import argparse
import re
import textwrap
from dataclasses import dataclass
from pathlib import Path
from tempfile import NamedTemporaryFile


UPSTREAM_REPOSITORY = "CommunitySpecification/Community_Specification"
UPSTREAM_RELEASE_TAG = "V1.1"
UPSTREAM_COMMIT_SHA = "30b5a91973eeb84e7c8148924b4823ae2bf207fa"
UPSTREAM_SOURCE_PATH_AT_COMMIT = "1._Community_Specification_License-v1.md"
UPSTREAM_RAW_SHA256 = "cc2efe227e081828843c87cb78116f7cc852076593693c0595a7c96ed014f617"
DEFAULT_WRAP_WIDTH = 80

ROOT = Path(__file__).resolve().parents[2]
DEFAULT_INPUT = ROOT / "LICENSE.md"
DEFAULT_OUTPUT = ROOT / "source" / "license.generated.rst.inc"

TITLE_RE = re.compile(r"^# (?P<title>.+)$")
BOLD_HEADING_RE = re.compile(r"^\*\*(?P<heading>.+?)\*\*(?P<body>\s{2,}.+)?$")
ORDERED_ITEM_RE = re.compile(r"^(?P<number>\d+[.)])\s+(?P<text>.+)$")
INLINE_LINK_RE = re.compile(r"\[([^\]]+)\]\(([^)]+)\)")
UNSUPPORTED_LINE_RE = re.compile(r"^(?:>|```|~~~|\| |-\s)")


class ParseError(RuntimeError):
    pass


@dataclass(frozen=True)
class Block:
    kind: str
    value: str | list[str]


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description="Generate the RST include used by source/license.rst."
    )
    parser.add_argument("--input", type=Path, default=DEFAULT_INPUT)
    parser.add_argument("--output", type=Path, default=DEFAULT_OUTPUT)
    parser.add_argument(
        "--check",
        action="store_true",
        help="Run semantic fidelity and determinism checks.",
    )
    return parser.parse_args()


def convert_inline_markup(text: str) -> str:
    def replace_link(match: re.Match[str]) -> str:
        label = match.group(1)
        url = match.group(2)
        return f"`{label} <{url}>`_"

    return INLINE_LINK_RE.sub(replace_link, text.strip())


def collect_paragraph(lines: list[str], start: int) -> tuple[str, int]:
    parts = [lines[start].strip()]
    index = start + 1
    while index < len(lines):
        stripped = lines[index].strip()
        if not stripped:
            break
        if TITLE_RE.match(stripped) or BOLD_HEADING_RE.match(stripped) or ORDERED_ITEM_RE.match(stripped):
            break
        parts.append(stripped)
        index += 1
    return " ".join(parts).strip(), index


def collect_list(lines: list[str], start: int) -> tuple[list[str], int]:
    items: list[str] = []
    index = start
    while index < len(lines):
        match = ORDERED_ITEM_RE.match(lines[index].strip())
        if not match:
            break
        parts = [match.group("text").strip()]
        index += 1
        while index < len(lines):
            stripped = lines[index].strip()
            if not stripped:
                break
            if TITLE_RE.match(stripped) or BOLD_HEADING_RE.match(stripped) or ORDERED_ITEM_RE.match(stripped):
                break
            parts.append(stripped)
            index += 1
        items.append(" ".join(parts).strip())
        while index < len(lines) and not lines[index].strip():
            index += 1
        if index < len(lines) and not ORDERED_ITEM_RE.match(lines[index].strip()):
            break
    return items, index


def parse_markdown(text: str) -> list[Block]:
    blocks: list[Block] = []
    lines = text.replace("\r\n", "\n").replace("\r", "\n").split("\n")
    index = 0
    while index < len(lines):
        line = lines[index]
        stripped = line.strip()
        if not stripped:
            index += 1
            continue
        if line.startswith("\t"):
            raise ParseError(f"unsupported tab indentation on line {index + 1}")
        if UNSUPPORTED_LINE_RE.match(stripped):
            raise ParseError(f"unsupported markdown construct on line {index + 1}: {stripped}")

        title_match = TITLE_RE.match(stripped)
        if title_match:
            blocks.append(Block("title", title_match.group("title")))
            index += 1
            continue

        heading_match = BOLD_HEADING_RE.match(stripped)
        if heading_match:
            blocks.append(Block("section", heading_match.group("heading").strip()))
            body = heading_match.group("body")
            if body:
                blocks.append(Block("paragraph", body.strip()))
            index += 1
            continue

        if stripped.startswith("*") and stripped.endswith("*") and len(stripped) > 2:
            blocks.append(Block("italic", stripped[1:-1].strip()))
            index += 1
            continue

        if ORDERED_ITEM_RE.match(stripped):
            items, index = collect_list(lines, index)
            blocks.append(Block("list", items))
            continue

        paragraph, index = collect_paragraph(lines, index)
        blocks.append(Block("paragraph", paragraph))
    return blocks


def wrap_paragraph(text: str, *, width: int = DEFAULT_WRAP_WIDTH) -> str:
    return textwrap.fill(
        convert_inline_markup(text),
        width=width,
        break_long_words=False,
        break_on_hyphens=False,
    )


def render_rst(blocks: list[Block]) -> str:
    lines: list[str] = [
        "..",
        "   Generated from LICENSE.md by .github/scripts/generate-license-rst.py.",
        f"   Upstream repository: {UPSTREAM_REPOSITORY}",
        f"   Upstream release tag: {UPSTREAM_RELEASE_TAG}",
        f"   Upstream commit SHA: {UPSTREAM_COMMIT_SHA}",
        f"   Upstream source path at commit: {UPSTREAM_SOURCE_PATH_AT_COMMIT}",
        f"   Upstream raw SHA-256: {UPSTREAM_RAW_SHA256}",
        "",
    ]
    for block in blocks:
        if block.kind == "title":
            title = str(block.value)
            lines.extend([title, "=" * len(title), ""])
        elif block.kind == "section":
            lines.extend([f"**{convert_inline_markup(str(block.value))}**", ""])
        elif block.kind == "paragraph":
            lines.extend([wrap_paragraph(str(block.value)), ""])
        elif block.kind == "italic":
            lines.extend(
                [
                    textwrap.fill(
                        f"*{convert_inline_markup(str(block.value))}*",
                        width=DEFAULT_WRAP_WIDTH,
                        break_long_words=False,
                        break_on_hyphens=False,
                    ),
                    "",
                ]
            )
        elif block.kind == "list":
            for item in block.value:  # type: ignore[union-attr]
                lines.append(
                    textwrap.fill(
                        convert_inline_markup(str(item)),
                        width=DEFAULT_WRAP_WIDTH,
                        initial_indent="#. ",
                        subsequent_indent="   ",
                        break_long_words=False,
                        break_on_hyphens=False,
                    )
                )
            lines.append("")
        else:
            raise ParseError(f"unsupported block kind: {block.kind}")
    return "\n".join(lines).rstrip() + "\n"


def parse_generated_rst(text: str) -> list[Block]:
    blocks: list[Block] = []
    lines = text.splitlines()
    index = 0
    if lines and lines[0] == "..":
        index = 1
        while index < len(lines) and (lines[index].startswith("   ") or not lines[index].strip()):
            index += 1
    while index < len(lines):
        line = lines[index]
        stripped = line.strip()
        if not stripped:
            index += 1
            continue
        if index + 1 < len(lines) and lines[index + 1] == "=" * len(line):
            blocks.append(Block("title", line))
            index += 2
            continue
        if stripped.startswith("**") and stripped.endswith("**"):
            blocks.append(Block("section", stripped[2:-2]))
            index += 1
            continue
        if stripped.startswith("#. "):
            items: list[str] = []
            while index < len(lines) and lines[index].strip().startswith("#. "):
                parts = [lines[index].strip()[3:]]
                index += 1
                while index < len(lines) and lines[index].startswith("   "):
                    parts.append(lines[index].strip())
                    index += 1
                items.append(" ".join(parts))
                while index < len(lines) and not lines[index].strip():
                    index += 1
            blocks.append(Block("list", items))
            continue
        if stripped.startswith("*") and stripped.endswith("*") and len(stripped) > 2:
            blocks.append(Block("italic", stripped[1:-1]))
            index += 1
            continue
        parts = [stripped]
        index += 1
        while index < len(lines) and lines[index].strip():
            parts.append(lines[index].strip())
            index += 1
        paragraph = " ".join(parts)
        if paragraph.startswith("*") and paragraph.endswith("*") and len(paragraph) > 2:
            blocks.append(Block("italic", paragraph[1:-1]))
        else:
            blocks.append(Block("paragraph", paragraph))
    return blocks


def normalize_text(text: str) -> str:
    text = re.sub(r"`([^`]+) <([^>]+)>`_", r"\1 <\2>", text)
    return re.sub(r"\s+", " ", text.strip())


def normalize_blocks(blocks: list[Block]) -> list[tuple[str, str | tuple[str, ...]]]:
    normalized: list[tuple[str, str | tuple[str, ...]]] = []
    for block in blocks:
        if block.kind == "list":
            items = tuple(normalize_text(str(item)) for item in block.value)  # type: ignore[arg-type]
            normalized.append((block.kind, items))
        else:
            normalized.append((block.kind, normalize_text(str(block.value))))
    return normalized


def build_output(input_path: Path) -> tuple[list[Block], str]:
    source_text = input_path.read_text(encoding="utf-8")
    blocks = parse_markdown(source_text)
    return blocks, render_rst(blocks)


def write_atomic(path: Path, content: str) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)
    with NamedTemporaryFile("w", encoding="utf-8", dir=path.parent, delete=False) as handle:
        handle.write(content)
        temp_path = Path(handle.name)
    temp_path.replace(path)


def run_check(input_path: Path, output_path: Path) -> None:
    markdown_blocks, first = build_output(input_path)
    _, second = build_output(input_path)
    if first != second:
        raise SystemExit("generator output is not deterministic")

    generated_blocks = parse_generated_rst(first)
    if normalize_blocks(markdown_blocks) != normalize_blocks(generated_blocks):
        raise SystemExit("generated RST is not semantically equivalent to LICENSE.md")

    if not output_path.exists():
        raise SystemExit(f"generated include is missing: {output_path}")

    if output_path.read_text(encoding="utf-8") != first:
        raise SystemExit(f"generated include is stale: {output_path}")

    print("license fidelity check passed")


def main() -> None:
    args = parse_args()
    _, output = build_output(args.input)
    if args.check:
        run_check(args.input, args.output)
        return
    write_atomic(args.output, output)
    print(f"generated {args.output}")


if __name__ == "__main__":
    main()
