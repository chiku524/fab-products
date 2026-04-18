# FAB plugin product package — Level Selection Sets

**Form:** Unreal Engine **code plugin** (editor-focused)  
**Category:** Tools & Plugins → Engine Tools  
**One-line pitch:** Save and recall named actor selections so large-level iteration stays fast and organized.

## Naming

| Element | Recommendation |
|---------|----------------|
| Product title | **Level Selection Sets** |
| Subtitle | Named selection bookmarks for faster level iteration |
| Shorthand | LSS |
| Internal plugin folder | `LevelSelectionSets` |

## Pricing (guidance)

| Scenario | Price |
|----------|-------|
| Soft launch (modest feature set / minimal media) | $14.99–$19.99 |
| Regular launch | **$24.99** |
| Bundled with a larger workflow suite | Per bundle strategy |

## Core feature set (V1)

| Group | What it does |
|-------|--------------|
| **Save** | Capture current selection under a user-defined name |
| **Recall** | Re-select stored actors (skip missing) |
| **Manage** | Rename, delete, reorder sets |
| **Persist** | Survive editor restart for the same level |

## Architecture (recommended)

| Layer | Choice |
|-------|--------|
| Plugin type | Code plugin |
| Main module | `LevelSelectionSetsEditor` |
| UI | Slate dockable tab |
| Storage | World subsystem + config or level-bound data (see `build-brief.md`) |

## Build / support matrix

| Item | Spec |
|------|------|
| Engine versions at launch | UE **5.4+** (5.x); separate Fab packages per minor line as needed |
| Dev platform | Windows first; Mac/Linux if validated |
| Code | Full source for Unreal-dependent code |
| Example project | Strongly recommended (hosted link) |
| Docs | Setup, quick-start, FAQ, changelog |
| QA | Clean package build; test `Package` / `BuildPlugin` |

## Listing copy (short)

**Short description:** Save named actor selections and recall them with one click—built for lighting passes, prop sweeps, and batch edits on large levels.

**Keywords:** Unreal Engine, plugin, level design, selection, outliner, editor productivity, environment art.

**Selling angles:** less repetitive clicking, faster iteration, clearer handoff between teammates.

## Required seller deliverables (Fab)

| Deliverable | Notes |
|-------------|-------|
| Zipped plugin per engine version | Required |
| `.uplugin` with `EngineVersion` | Required |
| `PlatformAllowList` / `PlatformDenyList` per module | Required |
| Documentation index | Required |
