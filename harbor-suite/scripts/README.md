# Harbor Suite scripts

## `generate-ue-project-files.ps1`

Regenerates the Visual Studio `.sln` for the demo project when Explorer integration is missing.

```powershell
.\generate-ue-project-files.ps1 -UProjectPath "C:\full\path\to\harbor-suite\Harbor\Harbor.uproject"
```

Optional: `-EngineRoot "C:\Program Files\Epic Games\UE_5.7"` to pin the engine.

## `package-plugin.ps1`

Runs **`RunUAT BuildPlugin`** to produce a Fab-ready plugin folder under **`harbor-suite/dist/`**.

```powershell
.\package-plugin.ps1 -EngineRoot "C:\Program Files\Epic Games\UE_5.7" -UeVersionLabel "5.7"
```

See **`../docs/PACKAGING_FOR_FAB.md`** for full guidance.
