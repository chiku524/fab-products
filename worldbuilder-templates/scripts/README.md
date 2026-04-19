# Scripts — World Builder Templates

## `package-plugin.ps1`

Packages the plugin with Epic's **RunUAT BuildPlugin** (same pattern as other products in this monorepo).

Example (adjust engine root and UE label):

```powershell
cd path\to\fab-products\worldbuilder-templates\scripts
.\package-plugin.ps1 -EngineRoot "C:\Program Files\Epic Games\UE_5.7" -UeVersionLabel "5.7"
```

Output defaults to `worldbuilder-templates/dist/WorldBuilderTemplates-UE<ver>-Win64/`.

## `create-sample-maps.ps1`

Runs the editor in commandlet mode to generate the checked-in sample `.umap` files under `WorldBuilderTemplates/Content/Maps/`. Requires a **C++ project** with this plugin enabled.

See [`../docs/SAMPLE_MAPS.md`](../docs/SAMPLE_MAPS.md).
