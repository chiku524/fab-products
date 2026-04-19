# World Builder Templates

Unreal Engine **editor plugin** for [Fab](https://www.fab.com/): browse **ready-made world maps** that ship with the plugin and open one as a starting point—**Start from template** loads an untitled copy (see Unreal’s map template behavior), or **Open** loads the asset directly.

## Layout

| Path | Purpose |
|------|---------|
| [`WorldBuilderTemplates/`](WorldBuilderTemplates/) | Plugin source, `WorldBuilderTemplates.uplugin`, `Content/`, `Resources/` |
| [`docs/`](docs/) | Installation and testing notes |

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

## Fab

Publisher **Immersive Labs** · support contact in `WorldBuilderTemplates.uplugin` (`SupportURL`).
