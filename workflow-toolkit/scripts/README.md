# Scripts — Workflow Toolkit

## `package-plugin.ps1`

Runs **Epic RunUAT BuildPlugin** for `WorkflowToolkit/WorkflowToolkit.uplugin`.

```powershell
cd path\to\fab-products\workflow-toolkit\scripts
.\package-plugin.ps1 -EngineRoot "C:\Program Files\Epic Games\UE_5.7" -UeVersionLabel "5.7"
```

Default output: `workflow-toolkit/dist/WorkflowToolkit-UE<ver>-Win64/`.

If **MAX_PATH** errors appear under a deep clone, pass a short **`-OutputParent`** (see script comments).

## `copy-packaged-plugin-to-test-project.ps1`

Copies a **finished** package folder into `Documents\Unreal Projects\WorkflowToolkit\Plugins\WorkflowToolkit` (override with `-Destination`). If **`-PackageRoot`** is omitted, uses the **newest** `dist/WorkflowToolkit-UE*-Win64` from `package-plugin.ps1` (run that first).

## Monorepo

Bulk **UE 5.7 Win64** zips (all **five** code plugins in this repo): `fab-products/scripts/build-fab-marketplace-drops-ue57.ps1` (see `../docs/PACKAGING_FOR_FAB.md`).
