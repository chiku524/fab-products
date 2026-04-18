# Installation

## Requirements

- **Unreal Engine:** **5.4 or newer** within Unreal Engine 5.x. Use the plugin package **built for your exact engine version** (same major.minor line as your editor, e.g. 5.4.x with 5.4.x).
- **Editor OS:** Windows 64-bit (Win64 editor). Mac/Linux editors are not validated for v1.
- **Project:** Any game or tool project that uses the Unreal Editor.

## Install steps

1. **Download** the plugin zip for your engine version from Fab (do not mix engine versions).
2. **Extract** the archive. You should see a folder named `WorldBuilderAuditConvert` containing `WorldBuilderAuditConvert.uplugin` and a `Source` directory.
3. **Copy** `WorldBuilderAuditConvert` into your project’s `Plugins` folder:
   - `YourProject/Plugins/WorldBuilderAuditConvert/`
   - Create `Plugins` at the project root if it does not exist.
4. **Regenerate** project files:
   - Right-click `YourProject.uproject` → **Generate Visual Studio project files** (Windows), or use your usual workflow.
5. **Build** the editor target (Development Editor) so the plugin module compiles.
6. **Launch** the Unreal Editor and open your project.
7. Confirm the plugin is enabled: **Edit → Plugins → WorldBuilder Audit & Convert** (enable if prompted) and restart the editor if asked.

## Source access

Fab code plugins ship with **full source** for Unreal-dependent code. You may browse and build from source under `Plugins/WorldBuilderAuditConvert/Source/`.

## Fab URL in the descriptor

After your listing is live, the `.uplugin` file may include a **`FabURL`** pointing to this product on Fab. That field is added by the publisher for compliance; it does not change how you install locally.
