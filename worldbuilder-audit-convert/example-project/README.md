# Example project (separate download)

Fab **strongly encourages** a separate example project for code plugins. The plugin itself should **not** be duplicated inside this project in the copy you host; customers install the plugin from Fab into `Plugins/` per [../docs/INSTALLATION.md](../docs/INSTALLATION.md).

## Purpose

- One **messy** map: many repeated static meshes suitable for audit + conversion demos.  
- Optional second layout or sequence showing **after** cleanup for trailers and screenshots.  
- Small download size; only assets needed for the demo.

## Suggested contents

| Piece | Notes |
|-------|--------|
| Map A | Outdoor clutter (Forest / open world preset demo) |
| Map B | Alley or interior corridor (Modular City / Interior presets) |
| Readme | Engine version, how to enable the plugin, link back to the Fab listing |

## Hosting

- Zip the project **without** embedding `WorldBuilderAuditConvert` in `Plugins/` **or** include a readme telling users to copy the plugin from their Fab purchase.  
- Upload to cloud storage or Epic-approved hosting; paste the URL in the Fab listing **technical information** / description as required by the portal.

## Relationship to this repository

This folder is documentation only. Add your `.uproject` and content in your art pipeline; keep the repo lightweight unless you choose to version the example here.
