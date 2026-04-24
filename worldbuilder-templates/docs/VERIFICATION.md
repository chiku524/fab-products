# Verification (publisher QA)

For detailed steps, see **[TESTING.md](TESTING.md)** and **[SAMPLE_MAPS.md](SAMPLE_MAPS.md)**.

Run once per **packaged** `RunUAT` build you intend to sell, in a **clean** project, using the **packaged** plugin folder (not an unmirrored dev junction).

## Setup

1. Test project on the **same engine minor line** as the package (e.g. 5.7.x for a 5.7 build).  
2. Copy the packaged **`WorldBuilderTemplates`** folder to `YourProject/Plugins/WorldBuilderTemplates/`.  
3. **Generate** project files, build **Development Editor**, enable the plugin, restart if needed.

## Checks

| Step | Action | Pass |
|------|--------|------|
| 1 | **Window → Level Editor → World Builder Templates** — panel lists **WBT_** sample maps (see [TESTING.md](TESTING.md)) | ☐ |
| 2 | **Open** a row — level loads; no critical errors in **Output Log** | ☐ |
| 3 | **Template** path (if used in UI) — untitled or template behavior matches your listing text | ☐ |
| 4 | **Project Settings → Plugins → World Builder Templates** — settings save | ☐ |
| 5 | **Content** from the plugin (`.umap` under plugin Content) is present in **Content Browser** | ☐ |

## Output log

No sustained **red** errors from `WorldBuilderTemplatesEditor` during the session.

## Record

Log engine build, package zip name, and pass/fail before Fab upload.
