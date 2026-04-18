# Build brief: Level Selection Sets

**Product:** Level Selection Sets  
**Type:** Unreal Engine **code plugin** (Fab)  
**Goal:** Let level designers and environment artists **save named actor selections** in the editor and **recall** them quickly for repeated passes (lighting, materials, collision, QA).

Fab compliance: at least one **C++ editor module**, full **Unreal-dependent source** included.

## Version 1 goal

Focused and dependable: **Select → Save set → Recall** with a simple dockable UI. Not a replacement for layers, folders, or filtering—**a recall accelerator** for hands-on iteration.

| Field | Specification |
|-------|----------------|
| Primary function | Persist named selection sets per level; restore selection on demand |
| Target user | Level designer, environment artist, lighting artist, indie team |
| Engine targets | UE **5.4 and newer** (5.x); ship builds per minor line you support |
| Platform (V1) | Windows editor |
| Time-to-value | First useful set saved within ~2 minutes of opening the plugin |

## Required feature scope

| Feature | Requirement |
|---------|---------------|
| Dockable editor panel | Implemented (`SLevelSelectionSetsPanel`, nomad tab under Level Editor) |
| Save current selection as named set | Implemented |
| Recall set (select actors in editor) | Implemented |
| Rename / delete set | Implemented |
| Persist across editor sessions | Implemented via editor-only `ALevelSelectionSetsData` in the persistent level (saves with the map) |
| Skip invalid / deleted actors on recall | Implemented (missing GUIDs increment a “missing” count in the notification) |

### Non-goals (V1)

- Runtime selection APIs for packaged games  
- Networked multiplayer selection sync  
- Full graph of dependencies between actors  
- Replacing Unreal’s outliner or layer systems  

## UI sections

| Section | Content |
|---------|---------|
| Set list | Named sets, recall button, delete, rename |
| Actions | Save from current selection, optional “replace set” |
| Status | Count of resolved vs missing actors on last recall |

## Implementation notes (for engineers)

- v1 stores **`FGuid`** actor ids (`AActor::GetActorGuid()`), validated on recall by scanning the loaded world.  
- Data lives on **`ALevelSelectionSetsData`** (editor-only actor spawned into the **persistent level** on first save; listed sets can be read without creating the actor).  
- Nomad tab registered in `LevelSelectionSetsEditor` via `FGlobalTabmanager` + `WorkspaceMenu::GetMenuStructure().GetLevelEditorCategory()`.  
- Undo wraps data edits with **`FScopedTransaction`** for save / delete / rename.
