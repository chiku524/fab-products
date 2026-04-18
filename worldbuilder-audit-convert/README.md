# WorldBuilder Audit & Convert

Unreal Engine editor plugin for [Fab](https://www.fab.com/) — **WorldBuilder Audit & Convert** scans levels for expensive world-building patterns and helps convert repeated static mesh actors into cleaner setups (ISM/HISM), with presets, dry-run preview, and exportable audit reports.

**Positioning:** “Optimization for builders, not just engineers.”

This folder is one **product** inside the [parent monorepo](../README.md).

## Contents

| Path | Description |
|------|-------------|
| [`docs/build-brief.md`](docs/build-brief.md) | V1 scope, features, UI, milestones, QA |
| [`docs/product-package.md`](docs/product-package.md) | Naming, pricing, listing copy, media, seller deliverables |
| [`WorldBuilderAuditConvert/`](WorldBuilderAuditConvert/) | Fab-oriented plugin scaffold (C++ editor module) |
| Shared Fab rules | [`../docs/fab-technical-reference.md`](../docs/fab-technical-reference.md) |

Ship **one packaged plugin zip per supported engine version** for Fab submission.

## Supported targets (planned)

- **Engine versions:** UE 5.4, 5.5, 5.6  
- **Editor platform (V1):** Windows (Win64)  
- **Module:** `WorldBuilderAuditConvertEditor` (Editor)

## Using the plugin in a project

1. Copy the `WorldBuilderAuditConvert` folder into your project’s `Plugins/` directory (or symlink from this monorepo).
2. Regenerate project files and build the editor.
3. After Fab assigns a product URL, add a top-level **`FabURL`** field to `WorldBuilderAuditConvert.uplugin` per [Fab technical requirements](https://support.fab.com/s/article/FAB-TECHNICAL-REQUIREMENTS). The scaffold omits this until you have an approved listing.

## Changelog

See [`CHANGELOG.md`](CHANGELOG.md).
