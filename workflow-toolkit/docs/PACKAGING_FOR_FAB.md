# Packaging for Fab — Workflow Toolkit

1. Match **`SupportURL`**, **`CreatedBy`**, and **`EngineVersion`** in `WorkflowToolkit/WorkflowToolkit.uplugin` to your listing.
2. **RunUAT** from a machine with the **target engine** installed (example **UE 5.7**):

```powershell
cd path\to\fab-products\workflow-toolkit\scripts
.\package-plugin.ps1 -EngineRoot "C:\Program Files\Epic Games\UE_5.7" -UeVersionLabel "5.7"
```

Output defaults to **`workflow-toolkit/dist/WorkflowToolkit-UE5.7-Win64/`** (folder name follows `-UeVersionLabel`).

3. If **`RunUAT` fails** with **path length / MAX_PATH** errors under a deep git clone, pass a **short** `-OutputParent` (see `package-plugin.ps1` header) or use the monorepo script that builds all **five** code plugins to a short path:

`fab-products/scripts/build-fab-marketplace-drops-ue57.ps1`

4. **Zip** the final plugin folder (or use the zips it writes under `fab-marketplace-drops/UE5.7-Win64/`) and upload to Fab.
5. Run **[VERIFICATION.md](VERIFICATION.md)** on the **packaged** plugin in a **clean** project before publishing.

Optional: copy a packaged build into a local test project with `scripts/copy-packaged-plugin-to-test-project.ps1` (set `-PackageRoot` to your `dist/...` folder).
