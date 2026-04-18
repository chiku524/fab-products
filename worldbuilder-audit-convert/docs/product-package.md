# FAB plugin product package — WorldBuilder Audit & Convert

**Form:** Unreal Engine **code plugin** (editor-focused)  
**Category:** Tools & Plugins → Engine Tools  
**One-line pitch:** Scan environments for expensive world-building patterns and help convert them into cleaner, faster scene setups.

## Naming

| Element | Recommendation |
|---------|----------------|
| Product title | **WorldBuilder Audit & Convert** |
| Subtitle | Batch scene cleanup and smart instancing for faster environment workflows |
| Shorthand | WBAC |
| Internal plugin folder | `WorldBuilderAuditConvert` |

## Pricing (guidance)

| Scenario | Price |
|----------|--------|
| Soft launch (modest feature set / weak media) | $29.99 |
| Regular launch | **$34.99** |
| Introductory sale target | ~$27.99 |
| Post–1.5 major presets + reporting | Up to $39.99 |

## Core feature set (V1)

| Group | What it does |
|-------|----------------|
| **Scene audit panel** | Scan level / selection / folders for repeated meshes, collision-heavy setups, instancing opportunities, shadow-cost patterns |
| **Convert repeated actors** | Eligible groups → ISM/HISM |
| **World-build presets** | e.g. Forest, Modular City, Interior Prop Pass, Mobile/VR Lite |
| **Safety preview** | Dry-run before commit |
| **Audit report export** | CSV or JSON |
| **Beginner wizard** | Scan → Review → Convert → Validate |

### Avoid in V1

- Runtime auto-optimization as core scope  
- Full replacement for Unreal profiling UIs  
- Aggressive automatic material rewrites  
- Massive PCG scope  

## Architecture (recommended)

| Layer | Choice |
|-------|--------|
| Plugin type | Code plugin |
| Main module | `WorldBuilderAuditConvertEditor` |
| Optional | `WorldBuilderAuditConvertCore` for shared scan logic |
| UI | Editor utility window or Slate dockable panel |
| Primary actions | Scan, preview, convert, export report, revert session |
| Presets | Data assets or config structs |
| Example | Small demo maps / separate example project link |

## Build / support matrix

| Item | Spec |
|------|------|
| Engine versions at launch | UE **5.4+** (5.x); separate Fab packages per minor line as needed |
| Dev platform | Windows first; Mac/Linux if validated |
| Code | Full source for Unreal-dependent code |
| Example project | Strongly recommended (hosted link) |
| Docs | Setup, quick-start, rules, FAQ, changelog |
| QA | Clean package build; test `Package` / `BuildPlugin` |

## Listing copy (short)

**Short description:** Scan levels, find expensive world-building patterns, and batch-convert repeated actors into cleaner, faster scene setups.

**Keywords:** Unreal Engine, plugin, world building, optimization, level design, instancing, HISM, scene cleanup, environment art.

**Selling angles:** workflow speed, optimization for non-specialists, safe preview, scalability via instancing, professional audit exports.

## Required seller deliverables (Fab)

| Deliverable | Notes |
|-------------|--------|
| Zipped plugin per engine version | Required |
| `.uplugin` with `EngineVersion` | Required |
| `PlatformAllowList` / `PlatformDenyList` per module | Required |
| Source for UE-dependent code | Required |
| Copyright in sources | Required |
| Documentation | Required |
| Changelog | Required |
| Example project link | Strongly recommended |
| Thumbnail, gallery, cover, trailer | Essential for conversion |
| Support contact + FAQ | Reduces refunds / friction |

## Media recommendations

- **Hero:** Plugin UI + obvious before/after.  
- **Gallery:** Audit panel, preview, before/after, preset selector.  
- **Trailer:** 45–75s workflow with captions.

## Launch checklist

1. Finalize feature scope (no overpromising).  
2. Package plugin per engine version.  
3. Example project hosted + linked.  
4. Screenshots + trailer.  
5. Listing copy + technical details.  
6. Submit for Fab review.

## References

1. [Fab Technical Requirements](https://support.fab.com/s/article/FAB-TECHNICAL-REQUIREMENTS)  
2. [Publishing assets for sale or free download in Fab](https://dev.epicgames.com/documentation/fab/publishing-assets-for-sale-or-free-download-in-fab?lang=en-US)  
