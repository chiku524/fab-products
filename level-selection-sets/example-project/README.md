# Example project (separate download)

Fab **strongly encourages** a separate example project for code plugins. The plugin itself should **not** be duplicated inside this project in the copy you host; customers install the plugin from Fab into `Plugins/` per [../docs/INSTALLATION.md](../docs/INSTALLATION.md).

## Purpose

- One **medium-to-large** map with many discrete actors (props, lights, splines) so **named selection sets** are obviously useful.  
- Optional labels or zones (text actors or simple meshes) so trailer viewers understand “District A / B.”  
- Small download size; only assets needed for the demo.

## Suggested contents

| Piece | Notes |
|-------|-------|
| Map A | Town square or modular street with repeatable props + several light groups |
| Map B | Interior with clusters of meshes (furniture, trim) for recall demos |
| Readme | Engine version, how to enable the plugin, link back to the Fab listing |

## Hosting

- Zip the project **without** embedding `LevelSelectionSets` in `Plugins/` **or** include a readme telling users to copy the plugin from their Fab purchase.  
- Upload to cloud storage or Epic-approved hosting; paste the URL in the Fab listing **technical information** / description as required by the portal.

## Relationship to this repository

This folder is documentation only. Add your `.uproject` and content in your art pipeline; keep the repo lightweight unless you choose to version the example here.
