# Workflow Toolkit

Unreal Engine **code plugin** for [Fab](https://www.fab.com/): a **Workflow Toolkit** editor panel with one-click shortcuts for common level and asset actions, plus a **runtime** `GameInstance` subsystem for PIE and dev utilities (console commands, pause, time dilation, teleport, camera focus).

This folder is one **product** inside the [fab-products monorepo](../README.md). Publisher checklist (all products): [`../docs/fab-listing-index.md`](../docs/fab-listing-index.md).

## Layout

| Path | Purpose |
|------|---------|
| [`DOCUMENTATION.md`](DOCUMENTATION.md) | **Master doc index** (links all publisher + buyer docs) |
| [`WorkflowToolkit/`](WorkflowToolkit/) | Plugin source, `WorkflowToolkit.uplugin`, editor + runtime modules |
| [`WorkflowToolkitDemo/`](WorkflowToolkitDemo/) | Optional **Harbor-style** sample C++ project (`README` inside) |
| [`docs/`](docs/) | Fab listing, packaging, testing, support |
| [`scripts/`](scripts/) | `package-plugin.ps1` (RunUAT), `copy-packaged-plugin-to-test-project.ps1` |

## Quick start (development)

1. Copy `WorkflowToolkit/` into your game under `Plugins/WorkflowToolkit/`.
2. Ensure your game module can link **`WorkflowToolkitRuntime`** if you use runtime APIs (the demo project shows the pattern).
3. Regenerate project files, build **Development Editor**, enable the plugin, open **Window → Level Editor → Workflow Toolkit**.

## Fab (publisher)

| Resource | Link |
|----------|------|
| Master doc index | [`DOCUMENTATION.md`](DOCUMENTATION.md) |
| Listing copy (paste into Fab) | [`docs/FAB_LISTING_COPY.md`](docs/FAB_LISTING_COPY.md) |
| Support | [`docs/SUPPORT.md`](docs/SUPPORT.md) |
| Packaging / RunUAT | [`docs/PACKAGING_FOR_FAB.md`](docs/PACKAGING_FOR_FAB.md) |
| Testing (detailed) | [`docs/TESTING.md`](docs/TESTING.md) |
| QA on packaged build | [`docs/VERIFICATION.md`](docs/VERIFICATION.md) |
| Listing media | [`docs/MEDIA.md`](docs/MEDIA.md) |
| Changelog | [`CHANGELOG.md`](CHANGELOG.md) |
| License | [`LICENSE`](LICENSE) |

**Publisher:** Immersive Labs · **Support:** `mailto:nico.builds@outlook.com` (must match `SupportURL` in `WorkflowToolkit.uplugin`).

Monorepo bulk build (**five** code plugins, UE 5.7 Win64): `fab-products/scripts/build-fab-marketplace-drops-ue57.ps1` (see `docs/PACKAGING_FOR_FAB.md`).
