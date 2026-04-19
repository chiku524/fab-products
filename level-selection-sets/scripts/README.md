# Scripts — Level Selection Sets

## `generate-ue-project-files.ps1` (Windows — no Explorer right‑click needed)

Regenerates **Visual Studio** `.sln` / project files for **any** Unreal `.uproject` — same as **Generate Visual Studio project files** when that item is missing from File Explorer.

**Prerequisites:** Unreal Engine installed (Epic Launcher). The script uses `Engine\Binaries\Win64\UnrealVersionSelector.exe`.

From **PowerShell** (replace paths with yours):

```powershell
cd path\to\fab-products\level-selection-sets\scripts
.\generate-ue-project-files.ps1 -UProjectPath "C:\Users\You\Documents\Unreal Projects\MyGame\MyGame.uproject"
```

Optional: pin the engine install explicitly (if you have several versions):

```powershell
.\generate-ue-project-files.ps1 -UProjectPath "C:\path\to\MyGame.uproject" -EngineRoot "C:\Program Files\Epic Games\UE_5.7"
```

Then open the generated `.sln` in Visual Studio and build **Development Editor**.

---

## `package-plugin.ps1` (recommended on Windows)

Packages the plugin with Epic’s **RunUAT BuildPlugin** so you get a clean output folder per engine line (Fab upload after QA).

**Prerequisites:** Unreal Engine **5.4+** installed; use the **same** engine install for the minor line you are building (e.g. build 5.5 packages with your 5.5 editor install).

From PowerShell:

```powershell
cd path\to\fab-products\level-selection-sets\scripts
.\package-plugin.ps1 -EngineRoot "C:\Program Files\Epic Games\UE_5.4"
```

Optional parameters:

| Parameter | Default | Purpose |
|-----------|---------|---------|
| `-UeVersionLabel` | `5.4` | Suffix for output folder name only (`LevelSelectionSets-UE5.4-Win64`) |
| `-OutputParent` | `..\dist` | Where the packaged folder is written |

**Repeat** with a different `-EngineRoot` (and matching `-UeVersionLabel`) for each engine minor line you sell.

## `package-plugin.sh` (Git Bash / WSL)

Same idea; calls `RunUAT.bat` via `cmd.exe`:

```bash
cd level-selection-sets/scripts
chmod +x package-plugin.sh
./package-plugin.sh "/c/Program Files/Epic Games/UE_5.4" 5.4
```

## After packaging

1. Follow [`../docs/VERIFICATION.md`](../docs/VERIFICATION.md) in a **clean** test project using the packaged output.  
2. Record results in [`../docs/ENGINE_TEST_MATRIX.md`](../docs/ENGINE_TEST_MATRIX.md).  
3. Zip the package folder for Fab when checks pass.
