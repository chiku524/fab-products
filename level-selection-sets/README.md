# Level Selection Sets

Unreal Engine editor plugin for [Fab](https://www.fab.com/) — **Level Selection Sets** saves **named actor selections** in the level editor so you can jump back to “all rooftop props,” “this light rig,” or “batch-edit this cluster” without hunting through the outliner every time.

**Positioning:** “Bookmarks for selections—iterate faster on big levels.”

This folder is one **product** inside the [fab-products monorepo](../README.md).

## Listing-ready package

The following are included for **Fab listing and customer delivery**:

| Deliverable | Location |
|-------------|----------|
| Master doc index | [`DOCUMENTATION.md`](DOCUMENTATION.md) |
| Installation | [`docs/INSTALLATION.md`](docs/INSTALLATION.md) |
| User guide | [`docs/USER_GUIDE.md`](docs/USER_GUIDE.md) |
| FAQ | [`docs/FAQ.md`](docs/FAQ.md) |
| Support | [`docs/SUPPORT.md`](docs/SUPPORT.md) |
| Listing copy (paste into Fab) | [`docs/FAB_LISTING_COPY.md`](docs/FAB_LISTING_COPY.md) |
| Media checklist | [`docs/MEDIA.md`](docs/MEDIA.md) |
| Packaging / RunUAT | [`docs/PACKAGING_FOR_FAB.md`](docs/PACKAGING_FOR_FAB.md) |
| Submission checklist | [`docs/SUBMISSION_CHECKLIST.md`](docs/SUBMISSION_CHECKLIST.md) |
| License | [`LICENSE`](LICENSE) |
| Changelog | [`CHANGELOG.md`](CHANGELOG.md) |
| Example project (separate host) | [`example-project/README.md`](example-project/README.md) |
| Plugin source + descriptor | [`LevelSelectionSets/`](LevelSelectionSets/) |
| Shared Fab rules | [`../docs/fab-technical-reference.md`](../docs/fab-technical-reference.md) |

**Before you submit:** Replace `[PUBLISHER_NAME]` and `[SUPPORT_EMAIL]` everywhere (including `.uplugin`, `LICENSE`, `SUPPORT.md`, and source headers). Set **`DocsURL`** / **`SupportURL`** in `LevelSelectionSets.uplugin` to your real URLs. After Fab publishes your product page, add **`FabURL`** to the `.uplugin` per Fab rules.

**Internal specs (optional for buyers):** [`docs/build-brief.md`](docs/build-brief.md), [`docs/product-package.md`](docs/product-package.md).

## Supported targets (v1)

- **Engine versions:** UE 5.4, 5.5, 5.6 — **one packaged zip per engine line** for Fab.  
- **Editor:** Windows 64-bit (Win64).  
- **Module:** `LevelSelectionSetsEditor`.

## Quick install (customers)

See [`docs/INSTALLATION.md`](docs/INSTALLATION.md): copy `LevelSelectionSets` into the project `Plugins/` folder, regenerate, build editor.
