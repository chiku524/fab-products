# Testing — Workflow Toolkit

## Compile

Add the plugin under `Plugins/WorkflowToolkit/`, generate project files, build **Development Editor**. If your game uses runtime APIs, ensure your game module lists **`WorkflowToolkitRuntime`** as a dependency (see `WorkflowToolkitDemo`).

## Editor

1. **Edit → Plugins** — enable **Workflow Toolkit**; restart if prompted.  
2. **Window → Level Editor → Workflow Toolkit** — panel opens without script errors.  
3. Exercise a few actions from **Selection & viewport**, **Meshes**, **Save / assets**, and **Editor** sections (exact labels follow the live build).  
4. **Editor Preferences → Keyboard Shortcuts** — search **Workflow Toolkit**; assign a shortcut to a command if exposed and confirm it runs.

## Runtime (PIE)

1. From a map with a **GameInstance** that can access the subsystem (default game flow is enough for smoke test).  
2. **Play** — in **Output Log**, confirm no red errors from `WorkflowToolkitRuntime` on init.  
3. If your project calls documented Blueprint or C++ APIs, run your project’s minimal test.

## Packaged plugin (Fab)

Use the **RunUAT** output folder (not a raw monorepo copy) in a **clean** test project, then repeat the steps above. See [VERIFICATION.md](VERIFICATION.md) for a publisher checklist.
