# Publisher assembly — bundle on Fab

## Prerequisites

- Each component built at least once so you know **`RunUAT`** works (see each product’s `docs/PACKAGING_FOR_FAB.md`).
- **Immersive Labs** metadata and **nico.builds@outlook.com** already applied in per-product files (this repo).

## Build matrix (per engine minor line you sell)

For **each** line (e.g. **5.4.x** only at launch):

1. **`level-selection-sets`** — `scripts/package-plugin.ps1` with that line’s `-EngineRoot` and `-UeVersionLabel`.
2. **`worldbuilder-audit-convert`** — same pattern.
3. **`unreal-game-dev-starter-kit`** — zip the **documentation tree** (no engine build). Use `stage-bundle.ps1` or the command in [`scripts/README.md`](../scripts/README.md).

Do **not** merge different engine binaries into **one** plugin zip.

## Fab listing structure

- Attach **one zip per plugin per engine line** (e.g. `LevelSelectionSets-UE5.4-Win64.zip`).
- Attach **starter kit** as its own zip.
- Repeat **5.5** (etc.) as separate files when you support more lines.

## Staging locally

From `immersive-labs-ue-bundle/scripts/` run **`stage-bundle.ps1`** to collect outputs under `staging/` (see script README). Use that folder as a **sanity check** before upload; Fab upload itself is manual in the portal.

## Listing copy

Paste from [`FAB_LISTING_COPY.md`](FAB_LISTING_COPY.md) and adjust version numbers/dates.
