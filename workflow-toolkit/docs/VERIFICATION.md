# Verification (publisher QA)

For **step-by-step** detail, see **[TESTING.md](TESTING.md)**.

Run this **once per** packaged `RunUAT` build (each engine line you sell), in a **clean** project, using the **packaged** plugin folder.

## Setup

1. New or spare **C++** or **Blank** project matching the engine used to build the package (e.g. 5.7.x).  
2. Copy the packaged **`WorkflowToolkit`** folder into `YourProject/Plugins/WorkflowToolkit/`.  
3. If you use **runtime** features, add **`WorkflowToolkitRuntime`** to your game module (see `WorkflowToolkitDemo`).  
4. Generate project files, build **Development Editor**, enable the plugin, restart if required.

## Checks

| Step | Action | Pass |
|------|--------|------|
| 1 | **Window → Level Editor → Workflow Toolkit** opens; no red errors in **Output Log** on load | ☐ |
| 2 | Run at least one action under **Selection & viewport** (e.g. frame / group) | ☐ |
| 3 | Run one **Save / content** or **Editor** action appropriate to your test map | ☐ |
| 4 | **PIE** starts; no `WorkflowToolkitRuntime` init errors in log | ☐ |
| 5 | Optional: exercise a **runtime** helper your listing promises (e.g. pause, time dilation) | ☐ |

## Record

Note engine build, package filename, and result in your internal release log before Fab upload.
