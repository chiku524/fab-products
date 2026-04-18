# Fab listing copy — paste-ready

Replace bracketed placeholders. Use with [MEDIA.md](MEDIA.md) and [PACKAGING_FOR_FAB.md](PACKAGING_FOR_FAB.md) when submitting.

## Product identity

| Field | Text |
|-------|------|
| **Product title** | Level Selection Sets |
| **Subtitle / tagline** | Named selection bookmarks for faster level iteration |
| **Primary category** | Tools & Plugins → Engine Tools (or closest Fab equivalent) |

## Short description (Fab short field)

Save named actor selections in the level editor and recall them with one click—lighting passes, prop sweeps, and batch edits without rebuilding selections from the outliner.

## Long description (listing body)

**Level Selection Sets** is an Unreal Engine **editor plugin** for level designers and environment artists who work on **large maps** and keep returning to the **same groups of actors**.

**What you get**

- **Named selection sets** — Capture your current selection under a memorable name (e.g. courtyard lights, rooftop dressing, collision pass batch).  
- **One-click recall** — Re-select that group when you are ready for the next pass.  
- **Level-friendly workflow** — Built for iteration: polish, lighting, material sweeps, and QA without losing your place in the outliner.  
- **Team handoff** — Sets act as lightweight “bookmarks” so collaborators know what you were working on.

**Who it’s for**

Builders who want **speed and clarity** in the editor—not another heavy optimization system. Pairs well with folder organization, layers, and your existing level structure habits.

**Important**

- Editor-only workflow; selections refer to level actors in the editor.  
- Use the plugin package that matches your **exact** Unreal Engine **5.4+** editor version.  
- **Windows 64-bit editor** supported for v1 unless your listing states broader support.

## Keywords / search tags

Unreal Engine, plugin, level design, selection, outliner, editor tools, workflow, environment art, lighting, batch edit, productivity

## Feature bullets (bullet list for listing)

- Save the current actor selection under a custom name per level  
- Recall a saved set to re-select those actors in one action  
- Rename, reorder, and delete sets as the map evolves  
- Streamlined workflow for lighting, materials, collision, and QA passes  
- Full source included for the editor module (Fab code-plugin rules)

## Technical summary (technical details / description)

- **Type:** Code plugin (C++ editor module)  
- **Module:** `LevelSelectionSetsEditor`  
- **Platforms:** Editor **Win64** (v1)  
- **Engine compatibility:** UE **5.4 and newer** (5.x) — **separate downloadable packages per engine minor line** you publish (Fab buyers use the zip that matches their editor)  
- **Dependencies:** Engine-only; does not require other marketplace plugins  
- **Documentation:** Included (`DOCUMENTATION.md` and `docs/` in product package)  
- **Example project:** Linked separately from the listing (not embedded in the plugin zip) — see `example-project/README.md`  

## Support blurb (listing support field)

Support: `[SUPPORT_EMAIL]` — include engine version, plugin version, and steps to reproduce. See included `docs/SUPPORT.md`.

## Version line for store

**Current version:** 1.0.0 — see `CHANGELOG.md`.
