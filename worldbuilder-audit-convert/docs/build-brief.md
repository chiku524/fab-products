# Build brief: WorldBuilder Audit & Convert

**Product:** WorldBuilder Audit & Convert  
**Type:** Unreal Engine **code plugin** (Fab)  
**Goal:** Help environment artists and teams detect inefficient world-building patterns and convert eligible repeated scene content into cleaner, more scalable setups.

Fab compliance: at least one **C++ editor module**, full **Unreal-dependent source** included.

## Version 1 goal

Narrow and dependable. **Not** a replacement for Unreal’s full profiling stack — a **guided editor workflow**: Scan → Review → Preview → Convert → Export Report.

| Field | Specification |
|-------|----------------|
| Primary function | Audit levels and batch-convert eligible repeated actors to more efficient structures |
| Target user | Environment artist, level designer, indie developer, technical artist |
| Engine targets | UE **5.4 and newer** (5.x); ship builds per minor line you support |
| Platform (V1) | Windows editor |
| Time-to-value | Meaningful result within ~5 minutes of opening the plugin |

## Required feature scope

Core loop: **Scan → Review → Preview → Convert → Export Report**.

| Feature | Requirement |
|---------|-------------|
| Scene audit panel | Required |
| Scan selected actors | Required |
| Scan current level | Required |
| Group repeated static mesh actors by mesh + material signature | Required |
| Detect ISM/HISM conversion candidates | Required |
| Dry-run preview of changes | Required |
| Batch conversion to ISM/HISM | Required |
| Preset rulesets | Required (**≥ 4** presets) |
| Export report (CSV or JSON) | Required |
| Simple onboarding wizard | Required |
| Revert current session changes | Strongly preferred |

### Presets (V1)

| Preset | Intended use |
|--------|----------------|
| Forest Pass | Large repeated foliage-adjacent props, environmental clutter |
| Modular City Pass | Repeated urban props, facades, street dressing |
| Interior Prop Pass | Dense indoor repeated decorative assets |
| Mobile/VR Lite | Conservative thresholds, more aggressive simplification |

### Detection rules (practical, not full simulation)

| Rule | Output |
|------|--------|
| Repeated static mesh count exceeds threshold | Recommend ISM/HISM conversion |
| Same mesh repeated within spatial radius | Recommend grouping |
| Excessive actors for small decorative meshes | Flag organization issue |
| Repeated actors with transforms safe for instancing | High-confidence candidates |
| Groups excluded by user tag/folder | Ignore |

### UI sections

| Section | Content |
|---------|---------|
| Scan settings | Scope, thresholds, preset, exclusions |
| Results table | Candidate groups, counts, confidence, estimated value |
| Preview | Summary of objects to convert |
| Actions | Apply, export report, rescan |
| Help | Quick-start, doc link |

### Data objects

- Preset config (thresholds, toggles)  
- Scan result row (one candidate group)  
- Session transaction log (revert / reporting)  
- Export schema (CSV/JSON)

### Non-goals (V1)

- Runtime optimization systems  
- Automatic material graph mutation  
- Automatic foliage system authoring  
- Full PCG replacement  
- Deep GPU profiling integration  

## Packaging and compliance

| Item | Requirement |
|------|-------------|
| `.uplugin` contains `EngineVersion` | Mandatory |
| Each module has `PlatformAllowList` or `PlatformDenyList` | Mandatory |
| `FabURL` after product ID known | Mandatory before release |
| Source for Unreal-dependent code | Mandatory |
| Copyright headers | Mandatory |
| Package test per supported engine | Mandatory |
| One package per engine version | Practical requirement for submission |

## Developer deliverables

| Deliverable | Required |
|-------------|----------|
| Full source for plugin | Yes |
| Packaged plugin zip per engine version | Yes |
| Setup + user documentation | Yes |
| Changelog (e.g. 1.0) | Yes |
| Example project **without** bundled plugin | Yes |
| Demo map assets + screenshot sources | Yes |
| Support FAQ draft | Yes |

## Suggested milestones

| Milestone | Acceptance |
|-----------|------------|
| 1 — UX & technical design | Wireframe, feature list, plan approved |
| 2 — Scan & results | Sample map produces candidate groups |
| 3 — Conversion | Preview + apply works on sample map |
| 4 — Reporting & presets | Export + preset system |
| 5 — Packaging & docs | Builds, docs, example project |

## QA acceptance

Test on **two** representative scenes: clutter-heavy **outdoor** and **modular interior** or urban. Pass if workflow is understandable, stable, and useful — not mathematical perfection.

| Check | Pass |
|-------|------|
| Install | Loads without consequential warnings |
| Scan | Finds opportunities in demo scene |
| Preview | User can inspect before apply |
| Conversion | Eligible actors convert; scene usable |
| Undo/revert | User can recover |
| Export | CSV/JSON matches scan content |
| Documentation | New user completes quick-start unassisted |

## Example project brief

Small download, one map with **intentionally messy** repeated props and/or a cleaned workflow showcase. Link separately per Fab guidance.

## Future roadmap (not V1)

| Version | Ideas |
|---------|--------|
| V1.1 | Better reporting, saved user presets, more filters |
| V1.2 | Foliage-aware recommendations, exclusion rules |
| V1.5 | More scene budget heuristics |
| V2.0 | PCG / World Partition helpers |
