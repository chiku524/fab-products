# Scripts — bundle staging

## `stage-bundle.ps1`

Build **both plugins** first with each product’s `package-plugin.ps1` for your target engine (same `-UeVersionLabel` for all).

Example for **UE 5.4**:

```powershell
# From repo root, after dist/ folders exist:
cd immersive-labs-ue-bundle\scripts
.\stage-bundle.ps1 -UeVersionLabel "5.4"
```

Output: `immersive-labs-ue-bundle/staging/UE5-4/` (folder name sanitizes dots) containing:

- `LevelSelectionSets-UE5.4-Win64.zip` — if `level-selection-sets/dist/...` exists  
- `WorldBuilderAuditConvert-UE5.4-Win64.zip` — if `worldbuilder-audit-convert/dist/...` exists  
- `UnrealGameDevStarterKit-docs.zip` — from `unreal-game-dev-starter-kit/`

If a plugin `dist/` folder is missing, the script **warns** and skips that zip.

Repeat with `-UeVersionLabel "5.5"` (after rebuilding plugins with UE 5.5) for a second engine line.
