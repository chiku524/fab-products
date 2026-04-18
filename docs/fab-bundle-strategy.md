# Fab bundle strategy (Immersive Labs / fab-products)

This repo can support an **all-in-one style offering** on Fab using **multiple files** (separate downloadables or multiple attachments per listing, per Fab’s current product setup), with a **minimum Unreal Engine version of 5.4** for anything that ships as a **code plugin**.

## Minimum engine: 5.4+

- **Code plugins** in this monorepo declare **`EngineVersion`** **5.4.0** (or compatible) as the **floor**. Buyers on **5.4 and newer** **5.x** use the **package built for their exact minor line** (e.g. 5.4.x vs 5.5.x)—not one binary for all of 5.x.
- **Non-plugin** products (e.g. documentation-only kits) are not tied to an engine build, but copy should still say they are written for **UE 5.4+** when relevant.

## Multiple files (recommended layout)

| File / role | Typical contents |
|-------------|------------------|
| **Plugin build — UE 5.4.x** | `RunUAT BuildPlugin` output for your 5.4-line engine install (Win64 editor). |
| **Plugin build — UE 5.5.x** | Same plugin, rebuilt when you support another minor line (separate zip). |
| **…** | Add one downloadable per **minor line** you sell. |
| **Documentation / starter kit** | Markdown + templates zip (no `.uplugin`). Can ship as its **own** file or listing. |

**Principle:** one **Fab** purchase can list **several downloads** so buyers grab the plugin zip for **their** engine plus optional docs—without stuffing unrelated engine binaries into a single archive.

## Naming buyers can understand

Use filenames like:

- `LevelSelectionSets-UE5.4-Win64.zip`
- `WorldBuilderAuditConvert-UE5.4-Win64.zip`
- `UnrealGameDevStarterKit-docs-v1.0.0.zip`

Match what your [`scripts/package-plugin.ps1`](../level-selection-sets/scripts/package-plugin.ps1) outputs under each product’s `dist/`.

## Listing copy

- State clearly: **minimum UE 5.4**, separate packages per **minor** line, **Windows 64-bit editor** where applicable.
- Link or attach the **starter kit** and **per-plugin** zips so expectations match [Fab technical requirements](fab-technical-reference.md).

## What this doc does not decide

Exact **Fab UI** for “one listing vs many” is set in the publisher portal; this file is the **engineering and packaging** contract for the monorepo.
