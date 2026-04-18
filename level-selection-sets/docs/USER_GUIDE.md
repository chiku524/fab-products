# User guide — Level Selection Sets

**Level Selection Sets** is an editor-only tool. It stores **named snapshots** of which actors you had selected in the current level so you can **recall that selection** later—ideal for lighting passes, material sweeps, collision fixes, or batch transforms without rebuilding selections from memory.

## Core workflow

1. **Select** — In the level viewport or **World Outliner**, select the actors you care about (e.g. every streetlight in one district).
2. **Save set** — Give the set a clear name (e.g. `DistrictA_Lights`).
3. **Recall** — Click the set in the plugin panel to **re-select** those actors (actors that were deleted or invalid are skipped when possible).
4. **Organize** — Rename, reorder, or delete sets as the level evolves.
5. **Per-level** — Sets are scoped to the **current persistent level** (or as documented in the shipped build) so different maps keep their own lists.

## When to use it

| Scenario | How it helps |
|----------|----------------|
| **Lighting pass** | Save “all fill lights in this courtyard,” tweak, come back tomorrow. |
| **Prop polish** | Tag clusters of dressing meshes for repeated batch edits. |
| **QA sweeps** | Jump between known problem groups without manual multi-select. |
| **Handoff** | Named sets act as lightweight “notes” for teammates reviewing the map. |

## Safety

- Recalling a set **selects** actors; it does not move or delete them unless you run other editor commands afterward.
- If actors were renamed, moved to another level, or deleted, the plugin may skip missing entries—verify important selections after major structural changes.
- Keep source control commits before large batch operations on recalled selections.

## Opening the tool

After the plugin is enabled, open **Window** and look under the **Level Editor** category for **Level Selection Sets** (nomad tab). You can also summon it from the global tab menu in the editor’s main window. If you do not see it, verify the plugin is enabled under **Edit → Plugins**.
