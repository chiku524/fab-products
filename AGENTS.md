## Learned User Preferences

- Target Unreal Engine 5.4 and newer for plugin work and Fab-related packaging in this workspace.
- Prefer new Fab products as Unreal Engine plugins.
- When wrapping tasks, appreciates explicit next steps (including validation and git workflow) rather than open-ended handoffs.
- Prefers simple, step-by-step Unreal testing and setup guidance; is not deeply familiar with day-to-day UE editor workflows.
- Expects the agent to run concrete terminal or CLI commands (not only describe them) when they unblock local or Unreal work on Windows; Epic’s “Generate Visual Studio project files” on `.uproject` may be missing from Explorer or IDE sidebars—use `UnrealVersionSelector.exe /projectfiles` or `level-selection-sets/scripts/generate-ue-project-files.ps1` instead of assuming a working right-click menu.

## Learned Workspace Facts

- Fab-oriented Unreal products in this repo use per-product folders with documentation (including `docs/TESTING.md` for editor verification), license, and packaging-oriented docs (for example listing copy and support notes).
- For Fab listing and product metadata in this workspace, use the publisher name Immersive Labs.
- Unreal plugin layout for test projects is `YourProject/Plugins/<ProductFolder>/` (for example `LevelSelectionSets` from `level-selection-sets/LevelSelectionSets/`); there is no generic folder named `plugin`, which often confuses first-time setup.
- `level-selection-sets/scripts/generate-ue-project-files.ps1` regenerates Visual Studio project files for a `.uproject` via Epic’s `UnrealVersionSelector.exe`, useful when Windows shell integration for `.uproject` is broken or absent.
