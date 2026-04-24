# World Builder Templates — demo (sample project)

This is the **World Builder Templates** **C++** sample project, matching the **Harbor Suite** layout. The **plugin** (including **Content** with template **`.umap`** files) lives at **`Plugins/WorldBuilderTemplates/`**. After changing the canonical plugin in `../WorldBuilderTemplates/`, run **`fab-products/scripts/sync-fab-demo-plugins.ps1`** to refresh the embedded copy.

## Open

Double-click **`WorldBuilderTemplatesDemo.uproject`** (Unreal **5.7+**; see `.uplugin` for version notes).

## Build

1. **Generate Visual Studio project files** for `WorldBuilderTemplatesDemo.uproject` (or your usual UnrealVersionSelector / project file script).
2. Build **WorldBuilderTemplatesDemoEditor** | **Development Editor**.

## Map content

**Template maps** ship **inside the plugin** under **`Plugins/WorldBuilderTemplates/Content/Maps/`** (e.g. `WBT_Template_*.umap`). This game project’s **`Content/Maps/`** is for your own work if you add maps here.

## Docs

- `../docs/SAMPLE_MAPS.md`, `../docs/TESTING.md`  
- Installation: `../docs/INSTALLATION.md`
