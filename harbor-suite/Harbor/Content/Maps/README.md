# Maps — Harbor Annex

## Why this folder is empty

Unreal **`.umap`** files are binary. This repository documents the demo level instead of committing the asset, so you keep the repo small and avoid merge pain.

## Create `HarborAnnex`

1. Open **`Harbor.uproject`**.
2. In **Content Browser**, right-click → **Level** (or **New Level**) under this folder.
3. Save as **`HarborAnnex`** → `/Game/Maps/HarborAnnex`.
4. Add geometry, lighting, and a **Player Start** for **Shakedown** demos.
5. Follow **`../../docs/DEMO_MAP_BEAT_SHEET.md`** for wing-by-wing staging.

## Set as default map (optional)

**Edit → Project Settings → Maps & Modes**

- Set **Editor Startup Map** and **Game Default Map** to `/Game/Maps/HarborAnnex`.

Or edit `Config/DefaultEngine.ini` accordingly after the asset exists.

## Clearance demo actors

For **Clearance → Select labels containing "Problem"**, rename a few actor labels to include the substring **`Problem`** (case-insensitive).
