# Installation

## Requirements

- **Unreal Engine:** **5.4 or newer** within Unreal Engine 5.x. Use the plugin package **built for your exact engine version** (same major.minor line as your editor, e.g. 5.4.x with 5.4.x).
- **Editor OS:** Windows 64-bit (Win64 editor). Mac/Linux editors are not validated for v1.
- **Project:** Any game or tool project that uses the Unreal Editor.

## Install steps

1. **Download** the plugin zip for your engine version from Fab (do not mix engine versions).
2. **Extract** the archive. You should see a folder named `LevelSelectionSets` containing `LevelSelectionSets.uplugin` and a `Source` directory.
3. **Copy** `LevelSelectionSets` into your project’s `Plugins` folder:
  - `YourProject/Plugins/LevelSelectionSets/`
  - Create `Plugins` at the project root if it does not exist.
4. **Regenerate** project files (pick one):
   - **Recommended (CLI):** from PowerShell:

     ```powershell
     cd path\to\fab-products\level-selection-sets\scripts
     .\generate-ue-project-files.ps1 -UProjectPath "C:\full\path\to\YourProject.uproject"
     ```

     Optional: `-EngineRoot "C:\Program Files\Epic Games\UE_5.7"` if you have several engines. See [`scripts/README.md`](../scripts/README.md).

   - **Or — File Explorer:** **right‑click the `.uproject` file** → **Generate Visual Studio project files** (on Windows 11, try **Show more options** / Shift+right‑click if missing).

   - **Or — one-liner:**

     `"C:\Program Files\Epic Games\UE_5.7\Engine\Binaries\Win64\UnrealVersionSelector.exe" /projectfiles "C:\full\path\to\YourProject.uproject"`

   Cursor/VS Code’s sidebar usually **does not** show Epic’s menu; use PowerShell or Explorer.

   **Restore the Explorer right‑click:** set **default app for `.uproject`** to Unreal ( **Settings → Apps → Default apps → Choose defaults by file type** ), or **Verify** the engine in **Epic Games Launcher → Library**. Reinstalling Epic Launcher or the engine sometimes restores shell extensions.
5. **Build** the editor target (Development Editor) so the plugin module compiles.
6. **Launch** the Unreal Editor and open your project.
7. Confirm the plugin is enabled: **Edit → Plugins → Level Selection Sets** (enable if prompted) and restart the editor if asked.

## Source access

Fab code plugins ship with **full source** for Unreal-dependent code. You may browse and build from source under `Plugins/LevelSelectionSets/Source/`.

## Fab URL in the descriptor

After your listing is live, the `.uplugin` file may include a **`FabURL`** pointing to this product on Fab. That field is added by the publisher for compliance; it does not change how you install locally.