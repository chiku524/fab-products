# User guide — WorldBuilder Audit & Convert

**WorldBuilder Audit & Convert** is an editor-only tool. It helps you find repeated static mesh placement that can be expressed more efficiently with instancing (ISM/HISM), preview changes safely, and export an audit trail for your team or clients.

## Core workflow

1. **Scan** — Analyze the current level or a selection for repeated meshes and grouping opportunities.
2. **Review** — Read the results table: candidate groups, counts, confidence, and suggested action.
3. **Preview** — Use dry-run mode to see which actors would be affected before anything changes.
4. **Convert** — Apply batch conversion to eligible groups (typically toward Instanced Static Mesh or Hierarchical ISM actors).
5. **Export report** — Save a **CSV** or **JSON** summary for documentation or handoff.
6. **Revert (when available)** — Undo the current session’s conversions if you need to step back.

## Scan scope

- **Current level** — Full analysis of loaded level actors (respecting scope rules below).
- **Selected actors** — Limit the scan to your current selection.
- **Exclusions** — Ignore actors by folder, tag, or other filters so critical hand-placed pieces stay untouched.

## Presets

Presets adjust thresholds and conversion aggressiveness for typical scenarios:

| Preset | When to use |
|--------|-------------|
| **Forest Pass** | Lots of repeated foliage-adjacent props and environmental clutter |
| **Modular City Pass** | Repeated urban props, facades, street dressing |
| **Interior Prop Pass** | Dense indoor decorative repeats |
| **Mobile / VR Lite** | Stricter limits and more aggressive simplification for lighter scenes |

Choose a preset before scanning, or use **custom** thresholds if the plugin exposes them.

## Understanding results

- **Repeated groups** — Actors that share mesh (and material signature, where applicable) and qualify for batching.
- **Confidence** — Higher means safer, more obvious instancing wins; review low-confidence rows carefully.
- **Flags** — Warnings for very small meshes with huge instance counts, spatial clustering hints, or organization suggestions.

## Safety

- Prefer **Preview** before **Apply** on large levels.
- Use **Undo** in the editor and session **Revert** (if available) after conversion passes.
- Keep backups or source control commits before bulk conversions on production maps.

## Opening the tool

Use the editor menu or tab registered by the plugin (exact menu path is shown in the editor after install — typically under **Tools** or **Window** for editor utilities). If you do not see it, verify the plugin is enabled under **Edit → Plugins**.
