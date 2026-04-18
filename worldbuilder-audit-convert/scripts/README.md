# Scripts — WorldBuilder Audit & Convert

## `package-plugin.ps1`

Runs **`RunUAT BuildPlugin`** for this product. Minimum supported engine: **UE 5.4**; use the install that matches the minor line you are packaging.

```powershell
cd path\to\fab-products\worldbuilder-audit-convert\scripts
.\package-plugin.ps1 -EngineRoot "C:\Program Files\Epic Games\UE_5.4" -UeVersionLabel "5.4"
```

Output defaults to `worldbuilder-audit-convert/dist/WorldBuilderAuditConvert-UE5.4-Win64/`.

Repeat with each engine version root you support (5.5, 5.6, …).
