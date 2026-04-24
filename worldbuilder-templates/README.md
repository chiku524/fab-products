# World Builder Templates

Unreal Engine **editor plugin** for [Fab](https://www.fab.com/): browse **ready-made world maps** that ship with the plugin and open one as a starting point—**Start from template** loads an untitled copy (see Unreal’s map template behavior), or **Open** loads the asset directly.

This folder is one **product** inside the [fab-products monorepo](../README.md). Publisher checklist (all products): [`../docs/fab-listing-index.md`](../docs/fab-listing-index.md).

## Layout

| Path | Purpose |
|------|---------|
| [`DOCUMENTATION.md`](DOCUMENTATION.md) | **Master doc index** (Fab download / listing links) |
| [`WorldBuilderTemplates/`](WorldBuilderTemplates/) | Plugin source, `WorldBuilderTemplates.uplugin`, `Content/`, `Resources/` |
| [`docs/`](docs/) | Fab listing, packaging, testing, support, sample maps |

## Dedicated dev project (optional)

A minimal UE project can mount the plugin via a **directory junction** so `Plugins/WorldBuilderTemplates` points at this repo’s `WorldBuilderTemplates/` folder (single copy of the source). Example: `Documents/Unreal Projects/WorldBuilder` with `WorldBuilderTemplates` enabled in the `.uproject` and junction + workflow notes in that project’s `DEV_SETUP.txt`.

## Quick start

1. Copy the `WorldBuilderTemplates` folder into your game project under `Plugins/`.
2. Regenerate project files and build the **Editor** target.
3. Enable **World Builder Templates** under **Edit → Plugins** (restart if prompted).
4. Open **Window → Level Editor → World Builder Templates**.

The plugin ships two starter maps under `Content/Maps/` (see `Content/Maps/README.txt`).  
**Project Settings → Plugins → World Builder Templates** adds extra asset-registry search roots (defaults include `/Engine/Maps/Templates`).  
Fab packaging: use `scripts/package-plugin.ps1` (see `docs/PACKAGING_FOR_FAB.md`).

## Fab (publisher)

| Resource | Link |
|----------|------|
| Master doc index | [`DOCUMENTATION.md`](DOCUMENTATION.md) |
| License | [`LICENSE`](LICENSE) |
| Listing copy (paste into Fab) | [`docs/FAB_LISTING_COPY.md`](docs/FAB_LISTING_COPY.md) |
| Support | [`docs/SUPPORT.md`](docs/SUPPORT.md) |
| Packaging / RunUAT | [`docs/PACKAGING_FOR_FAB.md`](docs/PACKAGING_FOR_FAB.md) |
| Testing | [`docs/TESTING.md`](docs/TESTING.md) |
| QA on packaged build | [`docs/VERIFICATION.md`](docs/VERIFICATION.md) |
| Listing media | [`docs/MEDIA.md`](docs/MEDIA.md) |
| Changelog | [`CHANGELOG.md`](CHANGELOG.md) |

**Publisher** **Immersive Labs** — **Support** in `WorldBuilderTemplates.uplugin` (`SupportURL`) and [`docs/SUPPORT.md`](docs/SUPPORT.md).
