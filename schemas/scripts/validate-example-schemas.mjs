//-----------------------------------------------------------------------------
// Copyright 2025-2026, Contributors to the Grid Edge Interoperability &
// Security Alliance (GEISA), a Series of LF Projects, LLC
//
// Licensed under the Apache License, Version 2.0. See LICENSE.
//-----------------------------------------------------------------------------
// Validates checked example payloads against the repo's JSON Schemas.
// This is separate from validate-json.mjs so parse failures and schema
// contract failures stay visible as different lint phases.

import { readdir, readFile } from "node:fs/promises";
import path from "node:path";
import { isDeepStrictEqual } from "node:util";

const ROOT = process.cwd();
// Keep this pass focused on checked repository content rather than generated
// output trees or local machine artifacts.
const EXCLUDED_DIRS = new Set([".git", "build", "dist", "node_modules", "tmp"]);

// Map each checked example family to the single schema it is expected to
// satisfy so semantic validation stays explicit and reviewable.
const SCHEMA_BY_PREFIX = [
  ["examples/actuator-", "geisa-actuator-schema.json"],
  ["examples/app-message-request-", "geisa-app-message-req-schema.json"],
  ["examples/app-message-response-", "geisa-app-message-rsp-schema.json"],
  ["examples/deployment-", "geisa-application-manifest-schema.json"],
  ["examples/metered-quantities-ac-meter-profile-", "profiles/geisa-metered-quantities-ac-meter-profile.json"],
  ["examples/metered-quantities-billing-profile-", "profiles/geisa-metered-quantities-billing-profile.json"],
  ["examples/platform-discovery-", "geisa-discovery-schema.json"],
  ["examples/sensor-", "geisa-sensor-schema.json"],
  ["examples/vendor-", "geisa-application-manifest-schema.json"],
  ["examples/waveform-", "geisa-waveform-schema.json"]
];

function schemaForExample(relPath)
{
  for (const [prefix, schemaName] of SCHEMA_BY_PREFIX)
  {
    if (relPath.startsWith(prefix))
    {
      return schemaName;
    }
  }

  return null;
}

async function loadJson(relPath)
{
  const contents = await readFile(path.join(ROOT, relPath), "utf8");
  return JSON.parse(contents);
}

function referencedSchemaNames(schema, currentSchemaName, seen = new Set())
{
  if (schema === null || typeof schema !== "object")
  {
    return seen;
  }

  if (Array.isArray(schema))
  {
    for (const entry of schema)
    {
      referencedSchemaNames(entry, currentSchemaName, seen);
    }
    return seen;
  }

  if (typeof schema.$ref === "string")
  {
    const [filePart] = schema.$ref.split("#", 2);
    if (filePart !== "")
    {
      seen.add(path.normalize(path.join(path.dirname(currentSchemaName), filePart)));
    }
  }

  for (const entry of Object.values(schema))
  {
    referencedSchemaNames(entry, currentSchemaName, seen);
  }

  return seen;
}

async function* walkJsonFiles(dir)
{
  const entries = await readdir(dir, { withFileTypes: true });

  for (const entry of entries)
  {
    const fullPath = path.join(dir, entry.name);

    if (entry.isDirectory())
    {
      if (!EXCLUDED_DIRS.has(entry.name))
      {
        yield* walkJsonFiles(fullPath);
      }
      continue;
    }

    if (entry.isFile() && entry.name.endsWith(".json"))
    {
      yield path.relative(ROOT, fullPath);
    }
  }
}

function pointerSegments(ref)
{
  if (!ref.startsWith("#"))
  {
    throw new Error(`external refs are not supported: ${ref}`);
  }

  const fragment = ref.slice(1);
  if (fragment === "")
  {
    return [];
  }

  if (!fragment.startsWith("/"))
  {
    throw new Error(`unsupported JSON Pointer fragment: ${ref}`);
  }

  return fragment
    .slice(1)
    .split("/")
    .map((segment) => segment.replaceAll("~1", "/").replaceAll("~0", "~"));
}

function resolveRef(schemaByName, currentSchemaName, ref)
{
  // The checked schema set relies on local refs and a small number of
  // cross-file refs; resolve only that repo-local surface here.
  let schema = null;
  let resolvedSchemaName = currentSchemaName;
  let fragment = ref;

  if (ref.includes("#"))
  {
    const [filePart, fragmentPart] = ref.split("#", 2);
    fragment = `#${fragmentPart}`;
    if (filePart === "")
    {
      schema = schemaByName.get(currentSchemaName) ?? null;
    }
    else
    {
      const resolvedName = path.normalize(path.join(path.dirname(currentSchemaName), filePart));
      schema = schemaByName.get(resolvedName) ?? null;
      if (schema === null)
      {
        const direct = schemaByName.get(filePart);
        if (direct !== undefined)
        {
          schema = direct;
          resolvedSchemaName = filePart;
        }
      }
      else
      {
        resolvedSchemaName = resolvedName;
      }
    }
  }
  else
  {
    schema = schemaByName.get(ref) ?? null;
    fragment = "#";
    if (schema !== null)
    {
      resolvedSchemaName = ref;
    }
  }

  if (schema === null)
  {
    return undefined;
  }

  let current = schema;

  for (const segment of pointerSegments(fragment))
  {
    if (current === undefined || current === null)
    {
      return undefined;
    }

    current = current[segment];
  }

  return { schema: current, schemaName: resolvedSchemaName };
}

function typeMatches(value, typeName)
{
  switch (typeName)
  {
  case "object":
    return value !== null && typeof value === "object" && !Array.isArray(value);
  case "array":
    return Array.isArray(value);
  case "string":
    return typeof value === "string";
  case "integer":
    return typeof value === "number" && Number.isInteger(value);
  case "number":
    return typeof value === "number" && Number.isFinite(value);
  case "boolean":
    return typeof value === "boolean";
  case "null":
    return value === null;
  default:
    return false;
  }
}

function stripAnnotations(value)
{
  // Examples may carry reviewer-facing $comment fields even when payload
  // validation should treat them as non-contract annotations.
  if (Array.isArray(value))
  {
    return value.map((entry) => stripAnnotations(entry));
  }

  if (value !== null && typeof value === "object")
  {
    const stripped = {};
    for (const [key, entry] of Object.entries(value))
    {
      if (key === "$comment")
      {
        continue;
      }
      stripped[key] = stripAnnotations(entry);
    }
    return stripped;
  }

  return value;
}

function validateSchema(value, schema, schemaByName, currentSchemaName, instancePath = "")
{
  // This validator intentionally implements the JSON Schema feature subset used
  // by the checked example/schema set in this repository.
  if (schema === true)
  {
    return [];
  }

  if (schema === false)
  {
    return [`${instancePath || "/"} is not allowed`];
  }

  if (schema.$ref)
  {
    const resolved = resolveRef(schemaByName, currentSchemaName, schema.$ref);
    if (resolved === undefined)
    {
      return [`${instancePath || "/"} has unresolved ref ${schema.$ref}`];
    }

    return validateSchema(value, resolved.schema, schemaByName, resolved.schemaName, instancePath);
  }

  const errors = [];

  if (schema.const !== undefined && !isDeepStrictEqual(value, schema.const))
  {
    errors.push(`${instancePath || "/"} must equal the schema constant`);
  }

  if (schema.enum && !schema.enum.some((candidate) => isDeepStrictEqual(candidate, value)))
  {
    errors.push(`${instancePath || "/"} is not one of the allowed values`);
  }

  if (schema.oneOf)
  {
    const validCount = schema.oneOf.reduce(
      (count, subschema) => count + (validateSchema(value, subschema, schemaByName, currentSchemaName, instancePath).length === 0 ? 1 : 0),
      0
    );
    if (validCount !== 1)
    {
      errors.push(`${instancePath || "/"} must match exactly one schema in oneOf`);
    }
  }

  if (schema.anyOf)
  {
    const validCount = schema.anyOf.reduce(
      (count, subschema) => count + (validateSchema(value, subschema, schemaByName, currentSchemaName, instancePath).length === 0 ? 1 : 0),
      0
    );
    if (validCount < 1)
    {
      errors.push(`${instancePath || "/"} must match at least one schema in anyOf`);
    }
  }

  if (schema.allOf)
  {
    for (const subschema of schema.allOf)
    {
      errors.push(...validateSchema(value, subschema, schemaByName, currentSchemaName, instancePath));
    }
  }

  if (schema.not && validateSchema(value, schema.not, schemaByName, currentSchemaName, instancePath).length === 0)
  {
    errors.push(`${instancePath || "/"} must not match the schema in not`);
  }

  if (schema.if)
  {
    const ifMatches = validateSchema(value, schema.if, schemaByName, currentSchemaName, instancePath).length === 0;
    if (ifMatches && schema.then)
    {
      errors.push(...validateSchema(value, schema.then, schemaByName, currentSchemaName, instancePath));
    }
    if (!ifMatches && schema.else)
    {
      errors.push(...validateSchema(value, schema.else, schemaByName, currentSchemaName, instancePath));
    }
  }

  if (schema.type)
  {
    const types = Array.isArray(schema.type) ? schema.type : [schema.type];
    if (!types.some((typeName) => typeMatches(value, typeName)))
    {
      errors.push(`${instancePath || "/"} must be of type ${types.join(" or ")}`);
      return errors;
    }
  }

  if (typeof value === "string")
  {
    if (schema.minLength !== undefined && value.length < schema.minLength)
    {
      errors.push(`${instancePath || "/"} is shorter than ${schema.minLength}`);
    }
    if (schema.maxLength !== undefined && value.length > schema.maxLength)
    {
      errors.push(`${instancePath || "/"} is longer than ${schema.maxLength}`);
    }
    if (schema.pattern)
    {
      const pattern = new RegExp(schema.pattern);
      if (!pattern.test(value))
      {
        errors.push(`${instancePath || "/"} does not match pattern ${schema.pattern}`);
      }
    }
  }

  if (typeof value === "number")
  {
    if (schema.minimum !== undefined && value < schema.minimum)
    {
      errors.push(`${instancePath || "/"} is below minimum ${schema.minimum}`);
    }
    if (schema.maximum !== undefined && value > schema.maximum)
    {
      errors.push(`${instancePath || "/"} is above maximum ${schema.maximum}`);
    }
  }

  if (Array.isArray(value))
  {
    if (schema.minItems !== undefined && value.length < schema.minItems)
    {
      errors.push(`${instancePath || "/"} has fewer than ${schema.minItems} item(s)`);
    }
    if (schema.maxItems !== undefined && value.length > schema.maxItems)
    {
      errors.push(`${instancePath || "/"} has more than ${schema.maxItems} item(s)`);
    }
    if (schema.uniqueItems)
    {
      const seen = new Set();
      for (const item of value)
      {
        const key = JSON.stringify(item);
        if (seen.has(key))
        {
          errors.push(`${instancePath || "/"} has duplicate array items`);
          break;
        }
        seen.add(key);
      }
    }
    if (schema.items)
    {
      for (let index = 0; index < value.length; index += 1)
      {
        errors.push(...validateSchema(value[index], schema.items, schemaByName, currentSchemaName, `${instancePath}/${index}`));
      }
    }
  }

  if (value !== null && typeof value === "object" && !Array.isArray(value))
  {
    const properties = schema.properties ?? {};

    if (schema.required)
    {
      for (const requiredName of schema.required)
      {
        if (!Object.prototype.hasOwnProperty.call(value, requiredName))
        {
          errors.push(`${instancePath || "/"} is missing required property ${requiredName}`);
        }
      }
    }

    if (schema.minProperties !== undefined && Object.keys(value).length < schema.minProperties)
    {
      errors.push(`${instancePath || "/"} has fewer than ${schema.minProperties} properties`);
    }

    if (schema.maxProperties !== undefined && Object.keys(value).length > schema.maxProperties)
    {
      errors.push(`${instancePath || "/"} has more than ${schema.maxProperties} properties`);
    }

    for (const [name, propertySchema] of Object.entries(properties))
    {
      if (Object.prototype.hasOwnProperty.call(value, name))
      {
        errors.push(...validateSchema(value[name], propertySchema, schemaByName, currentSchemaName, `${instancePath}/${name}`));
      }
    }

    const allowAdditional = schema.additionalProperties;
    if (allowAdditional === false)
    {
      for (const key of Object.keys(value))
      {
        if (!Object.prototype.hasOwnProperty.call(properties, key))
        {
          errors.push(`${instancePath || "/"} has additional property ${key}`);
        }
      }
    }
    else if (allowAdditional && typeof allowAdditional === "object")
    {
      for (const key of Object.keys(value))
      {
        if (!Object.prototype.hasOwnProperty.call(properties, key))
        {
          errors.push(...validateSchema(value[key], allowAdditional, schemaByName, currentSchemaName, `${instancePath}/${key}`));
        }
      }
    }
  }

  return errors;
}

async function main()
{
  const schemaByName = new Map();
  // Preload the explicitly-mapped schemas and any repo-local refs they use so
  // example validation can stay file-based and deterministic.
  const pendingSchemaNames = [...new Set(SCHEMA_BY_PREFIX.map((entry) => entry[1]))].sort();

  while (pendingSchemaNames.length > 0)
  {
    const schemaName = pendingSchemaNames.shift();
    if (schemaByName.has(schemaName))
    {
      continue;
    }

    schemaByName.set(schemaName, await loadJson(schemaName));
    for (const refSchemaName of referencedSchemaNames(schemaByName.get(schemaName), schemaName))
    {
      if (!schemaByName.has(refSchemaName))
      {
        pendingSchemaNames.push(refSchemaName);
      }
    }
  }

  let validatedCount = 0;
  let hasError = false;

  for await (const relPath of walkJsonFiles(path.join(ROOT, "examples")))
  {
    const schemaName = schemaForExample(relPath);
    if (schemaName === null)
    {
      continue;
    }

    validatedCount += 1;
    const schema = schemaByName.get(schemaName);
    const example = stripAnnotations(await loadJson(relPath));
    const errors = validateSchema(example, schema, schemaByName, schemaName);

    if (errors.length > 0)
    {
      hasError = true;
      console.error(`${relPath} -> ${schemaName}`);
      for (const error of errors)
      {
        console.error(`  ${error}`);
      }
    }
  }

  if (hasError)
  {
    // Fail the semantic-validation phase with a non-zero exit so npm/CI stops
    // immediately on schema/example contract regressions.
    process.exit(1);
  }

  console.log(`Validated ${validatedCount} example JSON file(s) against schema files.`);
}

main().catch((error) =>
{
  console.error(error instanceof Error ? error.message : String(error));
  // Treat loader or resolver failures the same way as validation failures for
  // CI-facing lint runs.
  process.exit(1);
});
