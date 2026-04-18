# WorldBuilder Audit & Convert

Unreal Engine editor plugin for [Fab](https://www.fab.com/) — **WorldBuilder Audit & Convert** scans levels for expensive world-building patterns and helps convert repeated static mesh actors into cleaner setups (ISM/HISM), with presets, dry-run preview, and exportable audit reports.

**Positioning:** “Optimization for builders, not just engineers.”

## Repository contents

| Path | Description |
|------|-------------|
| [`docs/build-brief.md`](docs/build-brief.md) | V1 scope, features, UI, milestones, QA (from build brief) |
| [`docs/product-package.md`](docs/product-package.md) | Product naming, pricing, listing copy, media, seller deliverables |
| [`docs/research-notes.md`](docs/research-notes.md) | Fab technical requirements and publishing workflow (with links) |
| [`WorldBuilderAuditConvert/`](WorldBuilderAuditConvert/) | Fab-oriented plugin scaffold (C++ editor module) |

This repo holds the **specification and starter plugin layout** for implementation. Ship **one packaged plugin zip per supported engine version** for Fab submission.

## Supported targets (planned)

- **Engine versions:** UE 5.4, 5.5, 5.6  
- **Editor platform (V1):** Windows (Win64)  
- **Module:** `WorldBuilderAuditConvertEditor` (Editor)

## Using the plugin in a project

1. Copy the `WorldBuilderAuditConvert` folder into your project’s `Plugins/` directory (or clone this repo and symlink/copy).
2. Regenerate project files and build the editor.
3. After Fab assigns a product URL, add a top-level **`FabURL`** field to `WorldBuilderAuditConvert.uplugin` (string URL to your Fab listing) per [Fab technical requirements](https://support.fab.com/s/article/FAB-TECHNICAL-REQUIREMENTS). The scaffold omits this until you have an approved listing.

## Fab references

- [Fab Technical Requirements](https://support.fab.com/s/article/FAB-TECHNICAL-REQUIREMENTS)
- [Publishing assets for sale or free download in Fab](https://dev.epicgames.com/documentation/fab/publishing-assets-for-sale-or-free-download-in-fab?lang=en-US)

## License

Source in this repository intended for Unreal Engine development; assign your product license for marketplace distribution. Include publisher copyright notices in all source/header files per Fab rules.

## Changelog

See [`CHANGELOG.md`](CHANGELOG.md).
