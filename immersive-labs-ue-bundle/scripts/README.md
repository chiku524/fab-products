# Scripts — Immersive Labs UE bundle

## `stage-bundle.ps1`

Collects the **Level Selection Sets** and **WorldBuilder Audit & Convert** plugin folders plus the **Unreal Game Dev Starter Kit** doc zip for Fab upload. Two ways to get plugin **built** trees:

### A) From monorepo bulk build (recommended, UE 5.7)

1. From `fab-products`, run (uses short paths to avoid `MAX_PATH` on Windows):

   `.\scripts\build-fab-marketplace-drops-ue57.ps1`

2. Then stage the bundle (paths match `2-lss` and `5-wbac` under the build root):

```powershell
cd immersive-labs-ue-bundle\scripts
.\stage-bundle.ps1 -UeVersionLabel "5.7" -MonorepoBuildRoot "C:\ilfab-ue57"
```

### B) From each product’s `dist/` (any engine line)

1. Build both plugins with each product’s `package-plugin.ps1` and the same `-UeVersionLabel` (e.g. `5.4`).

2. Do **not** set `-MonorepoBuildRoot`:

```powershell
.\stage-bundle.ps1 -UeVersionLabel "5.4"
```

**Output:** `immersive-labs-ue-bundle/staging/UE5-7/` (label reflects version) with:

- `LevelSelectionSets-UE<ver>-Win64.zip`  
- `WorldBuilderAuditConvert-UE<ver>-Win64.zip`  
- `UnrealGameDevStarterKit-docs.zip`  

Missing plugin folders are **warned** and skipped.

**Default** `-UeVersionLabel` is **5.7** to match the current monorepo primary engine line; override when you only ship an older line.
