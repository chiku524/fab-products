# Publisher assembly — bundle on Fab

## Prerequisites

- Each component built at least once so you know **`RunUAT`** works (see each product’s `docs/PACKAGING_FOR_FAB.md`).
- **Immersive Labs** metadata and **nico.builds@outlook.com** already applied in per-product files (this repo).

## Build matrix (per engine minor line you sell)

**Primary in this monorepo (UE 5.7 Win64):** run [`../../scripts/build-fab-marketplace-drops-ue57.ps1`](../../scripts/build-fab-marketplace-drops-ue57.ps1) from `fab-products` once. It builds **Harbor Suite**, **Level Selection Sets**, **World Builder Templates**, **Workflow Toolkit**, and **WorldBuilder Audit & Convert** to a **short** path (default `C:\ilfab-ue57\...`) to avoid Windows **MAX_PATH** issues, then zips to `fab-marketplace-drops/UE5.7-Win64/`.

**Bundle** downloadables: after that build, run **`immersive-labs-ue-bundle/scripts/stage-bundle.ps1`** with **`-MonorepoBuildRoot "C:\ilfab-ue57"`** and **`-UeVersionLabel "5.7"`** (see [scripts README](../scripts/README.md)). It picks **2-lss** and **5-wbac** and zips the starter kit.

**Other engine lines** (e.g. 5.4 only): for each line, run each product’s `package-plugin.ps1` with that engine. Then either copy outputs into the paths `stage-bundle.ps1` expects or run it **without** `-MonorepoBuildRoot` so it uses each product’s **`dist/`** folder.

3. **`unreal-game-dev-starter-kit`** — no engine build; it is included automatically by `stage-bundle.ps1`.

Do **not** merge different engine binaries into **one** plugin zip.

## Fab listing structure

- Attach **one zip per plugin per engine line** (e.g. `LevelSelectionSets-UE5.4-Win64.zip`).
- Attach **starter kit** as its own zip.
- Repeat **5.5** (etc.) as separate files when you support more lines.

## Staging locally

From `immersive-labs-ue-bundle/scripts/` run **`stage-bundle.ps1`** to collect outputs under `staging/` (see script README). Use that folder as a **sanity check** before upload; Fab upload itself is manual in the portal.

## Listing copy

Paste from [`FAB_LISTING_COPY.md`](FAB_LISTING_COPY.md) and adjust version numbers/dates.
