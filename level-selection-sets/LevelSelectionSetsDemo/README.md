# Level Selection Sets — demo (sample project)

This is the **Level Selection Sets** **C++** sample project, matching the **Harbor Suite** layout. The **plugin** lives at **`Plugins/LevelSelectionSets/`** (mirrors `../LevelSelectionSets/`; after you edit the canonical plugin, run **`fab-products/scripts/sync-fab-demo-plugins.ps1`** to refresh the embedded copy).

## Open

Double-click **`LevelSelectionSetsDemo.uproject`** (Unreal **5.7** recommended; plugin supports **5.4+**).

## Build

1. **Generate Visual Studio project files** for `LevelSelectionSetsDemo.uproject` (or `..\scripts\generate-ue-project-files.ps1` from the Level Selection Sets product folder, pointing at this `.uproject`).
2. Build **LevelSelectionSetsDemoEditor** | **Development Editor**.

## Map content

The sample game project has **no** committed `.umap` here. Create levels under **`Content/Maps/`** or use a starter map. See **`Content/Maps/README.md`**.

## Docs

- Plugin testing: `../LevelSelectionSets/docs/TESTING.md`  
- Installation: `../LevelSelectionSets/docs/INSTALLATION.md`
