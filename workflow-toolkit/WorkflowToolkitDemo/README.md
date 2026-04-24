# Workflow Toolkit — demo (sample project)

This is the **Workflow Toolkit** **C++** sample project, matching the **Harbor Suite** layout. The **plugin** (editor + **WorkflowToolkitRuntime**) lives at **`Plugins/WorkflowToolkit/`**. After changing the canonical plugin in `../WorkflowToolkit/`, run **`fab-products/scripts/sync-fab-demo-plugins.ps1`** to refresh the embedded copy.

## Open

Double-click **`WorkflowToolkitDemo.uproject`** (Unreal **5.7** recommended; plugin lists **5.4+**).

## Build

1. **Generate Visual Studio project files** for `WorkflowToolkitDemo.uproject`.
2. Build **WorkflowToolkitDemoEditor** | **Development Editor**.

## PIE and runtime

The game module links **`WorkflowToolkitRuntime`**. After plugin **C++** or **Slate** changes, do a full **rebuild** and often a **full editor restart** before the panel or shortcuts update.

## Map content

No committed `.umap` here. See **`Content/Maps/README.md`**.

## Docs

Use the `workflow-toolkit` product docs in the monorepo (e.g. testing notes under the plugin tree when present).
