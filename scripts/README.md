# Monorepo scripts (Fab)

| Script | Purpose |
|--------|--------|
| [`verify-fab-prerequisites.ps1`](verify-fab-prerequisites.ps1) | **Static checks:** `LICENSE`, `.uplugin`, key docs. Optional **`-CheckBuildOutput`** to see if `C:\ilfab-ue57\...` has fresh RunUAT folders. |
| [`sync-fab-demo-plugins.ps1`](sync-fab-demo-plugins.ps1) | Robocopy canonical plugins into `*Demo/Plugins/` sample projects (excludes `Binaries` / `Intermediate`). |
| [`build-fab-marketplace-drops-ue57.ps1`](build-fab-marketplace-drops-ue57.ps1) | **RunUAT BuildPlugin** for **five** code plugins: Harbor, LSS, WBT, Workflow Toolkit, **WorldBuilder Audit & Convert** — **UE 5.7**; output on a **short** path (`C:\ilfab-ue57\...`); zips to `fab-marketplace-drops/UE5.7-Win64/`. |
| [`Junction-UE-Project-To-Documents.ps1`](Junction-UE-Project-To-Documents.ps1) | **Windows:** create `%USERPROFILE%\Documents\Unreal Projects\<name>\` as a **junction** to a repo folder (e.g. `harbor-suite/Harbor`), optional **`-OpenAfter`** to launch the `.uproject` with the normal shell handler. Does **not** change global `.uproject` file associations. |

**Harbor shortcut:** `harbor-suite/Open-Harbor-From-Documents.cmd` calls this for `Harbor\Harbor.uproject` (see `harbor-suite/docs/QUICKSTART.md`).

Product-specific `package-plugin.ps1` files live under each product’s `scripts/` folder. See `docs/fab-listing-index.md` for the full publisher checklist per product.
