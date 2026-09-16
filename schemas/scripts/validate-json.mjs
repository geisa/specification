//-----------------------------------------------------------------------------
// Copyright 2025-2026, Contributors to the Grid Edge Interoperability &
// Security Alliance (GEISA), a Series of LF Projects, LLC
//
// Licensed under the Apache License, Version 2.0. See LICENSE.
//-----------------------------------------------------------------------------

import { readFile } from "node:fs/promises";
import { execFile } from "node:child_process";
import path from "node:path";
import { promisify } from "node:util";

const ROOT = process.cwd();
const run = promisify(execFile);

async function listTrackedJsonFiles() {
  const { stdout } = await run("git", ["ls-files", "*.json"]);
  return stdout
    .split("\n")
    .map((filePath) => filePath.trim())
    .filter(Boolean);
}

let count = 0;
let hasError = false;

for (const filePath of await listTrackedJsonFiles()) {
  count += 1;

  try {
    const contents = await readFile(path.join(ROOT, filePath), "utf8");
    JSON.parse(contents);
  } catch (err) {
    hasError = true;
    const message = err instanceof Error ? err.message : String(err);
    console.error(`${filePath}: ${message}`);
  }
}

if (hasError) {
  process.exit(1);
}

console.log(`Validated ${count} JSON file(s).`);
