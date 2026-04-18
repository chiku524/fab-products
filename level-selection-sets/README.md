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
| Packaging scripts | [`scripts/README.md`](scripts/README.md) |
| QA checklist | [`docs/VERIFICATION.md`](docs/VERIFICATION.md) |
| Engine test matrix | [`docs/ENGINE_TEST_MATRIX.md`](docs/ENGINE_TEST_MATRIX.md) |
| Submission checklist | [`docs/SUBMISSION_CHECKLIST.md`](docs/SUBMISSION_CHECKLIST.md) |
| License | [`LICENSE`](LICENSE) |
| Changelog | [`CHANGELOG.md`](CHANGELOG.md) |
| Example project (separate host) | [`example-project/README.md`](example-project/README.md) |
| Plugin source + descriptor | [`LevelSelectionSets/`](LevelSelectionSets/) |
| Shared Fab rules | [`../docs/fab-technical-reference.md`](../docs/fab-technical-reference.md) |
| **New to UE?** Smoke testing | [`../docs/unreal-plugin-testing-beginner.md`](../docs/unreal-plugin-testing-beginner.md) |

**Fab listing:** Publisher **Immersive Labs** · **nico.builds@outlook.com** · `SupportURL` in `LevelSelectionSets.uplugin` is set to **`mailto:nico.builds@outlook.com`**. After Fab publishes your product page, add **`FabURL`** to the `.uplugin` per Fab rules. Optional: set **`DocsURL`** when you host documentation.

**Internal specs (optional for buyers):** [`docs/build-brief.md`](docs/build-brief.md), [`docs/product-package.md`](docs/product-package.md).

## Supported targets (v1)

- **Engine versions:** **UE 5.4 and newer** (Unreal Engine 5.x). Ship **one packaged plugin zip per engine minor line** you support (e.g. 5.4.x, 5.5.x) so binaries match the buyer’s editor.  
- **Editor:** Windows 64-bit (Win64).  
- **Module:** `LevelSelectionSetsEditor`.

## Quick install (customers)

See [`docs/INSTALLATION.md`](docs/INSTALLATION.md): copy `LevelSelectionSets` into the project `Plugins/` folder, regenerate, build editor.

## Publisher: build & test (UE 5.4+)

1. On a machine with a given engine line installed, run [`scripts/package-plugin.ps1`](scripts/package-plugin.ps1) (see [`scripts/README.md`](scripts/README.md)).  
2. Repeat for each minor line you sell (different `EngineRoot` / label per 5.4.x, 5.5.x, …).  
3. Follow [`docs/VERIFICATION.md`](docs/VERIFICATION.md) on a clean project per package.  
4. Fill [`docs/ENGINE_TEST_MATRIX.md`](docs/ENGINE_TEST_MATRIX.md) and ship the matching zip(s) on Fab.
