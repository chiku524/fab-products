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
4. **Regenerate** project files (see **note** below if you do not see this menu):
   - Open **Windows File Explorer** and go to the folder that contains **`YourProject.uproject`** (the real path on disk, e.g. under **Documents/Unreal Projects/**).
   - **Right‑click the `.uproject` file** (the file icon, not the folder) → **Generate Visual Studio project files**.
   - On **Windows 11**, if that line is missing, open the **full** context menu (**Show more options** / Shift+F10, or Shift+right‑click) and look again—shell extensions sometimes only appear on the classic menu.
   - **Alternative (command line):** from PowerShell or CMD, run **`UnrealVersionSelector.exe`** with your engine and project path (replace the engine folder with yours):

     `"C:\Program Files\Epic Games\UE_5.7\Engine\Binaries\Win64\UnrealVersionSelector.exe" /projectfiles "C:\full\path\to\YourProject.uproject"`

   Using **VS Code / Cursor’s** file tree to right‑click often **does not** show Epic’s entry; use Explorer or the command above.
5. **Build** the editor target (Development Editor) so the plugin module compiles.
6. **Launch** the Unreal Editor and open your project.
7. Confirm the plugin is enabled: **Edit → Plugins → Level Selection Sets** (enable if prompted) and restart the editor if asked.

## Source access

Fab code plugins ship with **full source** for Unreal-dependent code. You may browse and build from source under `Plugins/LevelSelectionSets/Source/`.

## Fab URL in the descriptor

After your listing is live, the `.uplugin` file may include a **`FabURL`** pointing to this product on Fab. That field is added by the publisher for compliance; it does not change how you install locally.