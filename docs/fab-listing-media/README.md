# Fab listing media (generated)

**Marketing renders** for publisher workflow: one **thumbnail** (square-friendly composition) and **gallery** (16:9-friendly) per product, plus a shared style. **Replace with real in-editor captures** at submission time if Fab review or your QA requires authentic screenshots; these are **placeholders** that read well at small sizes.

**Epic’s Fab portal** may specify exact pixel dimensions—resize/crop in an image tool before upload.

| # | File | Use |
|---|------|-----|
| 1–7 | `*/thumbnail.png` | Listing thumbnail / cover |
| 8–24 | `*/gallery-*.png` | Gallery (see manifest below) |

## Manifest (24 files)

| Slug | Thumbnail | Gallery |
|------|-------------|--------|
| `harbor-suite` | `thumbnail.png` | `gallery-01-charts.png`, `gallery-02-stowage.png`, `gallery-03-shakedown-pie.png` |
| `level-selection-sets` | `thumbnail.png` | `gallery-01-saved-sets.png`, `gallery-02-recall.png`, `gallery-03-outliner.png` |
| `worldbuilder-templates` | `thumbnail.png` | `gallery-01-template-maps.png`, `gallery-02-world-grid.png` |
| `worldbuilder-audit-convert` | `thumbnail.png` | `gallery-01-audit.png`, `gallery-02-instancing.png` |
| `workflow-toolkit` | `thumbnail.png` | `gallery-01-panel.png`, `gallery-02-shortcuts.png` |
| `unreal-game-dev-starter-kit` | `thumbnail.png` | `gallery-01-docs.png`, `gallery-02-pipeline.png` |
| `immersive-labs-ue-bundle` | `thumbnail.png` | `gallery-01-bundle.png`, `gallery-02-plugins.png`, `gallery-03-starter.png` |

**Regenerate zips** (keeps `fab-marketplace-drops` and site `public/fab-products` in sync with source; run on a machine with UE 5.7 + RunUAT):  
`.\scripts\build-fab-marketplace-drops-ue57.ps1` then `immersive.labs\scripts\package-fab-product-zips.ps1` and, for the bundle, `immersive-labs-ue-bundle\scripts\stage-bundle.ps1` with the same UE version and monorepo build root you used for the plugin build — see `../fab-listing-index.md`.

**Source files (generated in Cursor):** the tool wrote unique names under `.cursor/.../assets/fab-mk-*.png`; the repo only contains the **copies** in each product subfolder here (7 thumbnails + 17 gallery = **24** PNG files).
