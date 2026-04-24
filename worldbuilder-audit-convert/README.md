# WorldBuilder Audit & Convert

Unreal Engine editor plugin for [Fab](https://www.fab.com/) — **WorldBuilder Audit & Convert** scans levels for expensive world-building patterns and helps convert repeated static mesh actors into cleaner setups (ISM/HISM), with presets, dry-run preview, and exportable audit reports.

**Positioning:** “Optimization for builders, not just engineers.”

This folder is one **product** inside the [fab-products monorepo](../README.md).

**Repository folder** is **`worldbuilder-audit-convert`** (some docs may say “audit converter” — same product). The Fab listing title is **WorldBuilder Audit & Convert** (matches `WorldBuilderAuditConvert.uplugin`).

**Bulk Win64 5.7 build:** this plugin is included in [`../scripts/build-fab-marketplace-drops-ue57.ps1`](../scripts/build-fab-marketplace-drops-ue57.ps1) (output `5-wbac\WorldBuilderAuditConvert-UE5.7-Win64` on the default short path).

## Listing-ready package

The following are included for **Fab listing and customer delivery**:

| Deliverable | Location |
|-------------|----------|
| Monorepo publisher index (all products) | [`../docs/fab-listing-index.md`](../docs/fab-listing-index.md) |
| Master doc index | [`DOCUMENTATION.md`](DOCUMENTATION.md) |
| Installation | [`docs/INSTALLATION.md`](docs/INSTALLATION.md) |
| User guide | [`docs/USER_GUIDE.md`](docs/USER_GUIDE.md) |
| FAQ | [`docs/FAQ.md`](docs/FAQ.md) |
| Support | [`docs/SUPPORT.md`](docs/SUPPORT.md) |
| Listing copy (paste into Fab) | [`docs/FAB_LISTING_COPY.md`](docs/FAB_LISTING_COPY.md) |
| Media checklist | [`docs/MEDIA.md`](docs/MEDIA.md) |
| Packaging / RunUAT | [`docs/PACKAGING_FOR_FAB.md`](docs/PACKAGING_FOR_FAB.md) |
| Testing | [`docs/TESTING.md`](docs/TESTING.md) |
| Packaging script | [`scripts/README.md`](scripts/README.md) |
| Submission checklist | [`docs/SUBMISSION_CHECKLIST.md`](docs/SUBMISSION_CHECKLIST.md) |
| License | [`LICENSE`](LICENSE) |
| Changelog | [`CHANGELOG.md`](CHANGELOG.md) |
| Example project (separate host) | [`example-project/README.md`](example-project/README.md) |
| Plugin source + descriptor | [`WorldBuilderAuditConvert/`](WorldBuilderAuditConvert/) |
| Shared Fab rules | [`../docs/fab-technical-reference.md`](../docs/fab-technical-reference.md) |
| **New to UE?** Smoke testing | [`../docs/unreal-plugin-testing-beginner.md`](../docs/unreal-plugin-testing-beginner.md) |

**Fab listing:** Publisher **Immersive Labs** · **nico.builds@outlook.com** · `SupportURL` in `WorldBuilderAuditConvert.uplugin` is set to **`mailto:nico.builds@outlook.com`**. After Fab publishes your product page, add **`FabURL`** to the `.uplugin` per Fab rules. Optional: set **`DocsURL`** when you host documentation.

**Internal specs (optional for buyers):** [`docs/build-brief.md`](docs/build-brief.md), [`docs/product-package.md`](docs/product-package.md).

## Supported targets (v1)

- **Engine versions:** **UE 5.4 and newer** (Unreal Engine 5.x). Ship **one packaged plugin zip per engine minor line** you support (e.g. 5.4.x, 5.5.x) so binaries match the buyer’s editor.  
- **Editor:** Windows 64-bit (Win64).  
- **Module:** `WorldBuilderAuditConvertEditor`.

## Quick install (customers)

See [`docs/INSTALLATION.md`](docs/INSTALLATION.md): copy `WorldBuilderAuditConvert` into the project `Plugins/` folder, regenerate, build editor.
