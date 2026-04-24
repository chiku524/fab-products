# Epic Fab products

Monorepo for [Fab](https://www.fab.com/) listings: specifications, documentation, Unreal Engine plugin sources, and template/knowledge products. Add each product as its **own top-level directory** (kebab-case slug).

**Publisher checklist (license, listing text, support, packaging, QA):** [`docs/fab-listing-index.md`](docs/fab-listing-index.md)

## Products

| Directory | Product | Description |
|-----------|---------|-------------|
| [`harbor-suite/`](harbor-suite/) | **Harbor Suite** | Editor workflow “control room” (Charts, Stowage, Shakedown, Clearance) + runtime helper; includes **Harbor** sample. |
| [`level-selection-sets/`](level-selection-sets/) | **Level Selection Sets** | Editor plugin: save named actor selection sets per level and recall them for lighting passes, prop sweeps, and batch edits. |
| [`worldbuilder-templates/`](worldbuilder-templates/) | **World Builder Templates** | Editor plugin: pick ready-made world maps shipped with the plugin (template or direct open). |
| [`worldbuilder-audit-convert/`](worldbuilder-audit-convert/) | **WorldBuilder Audit & Convert** | Editor plugin: audit levels; batch toward ISM/HISM with presets, preview, and reports. |
| [`workflow-toolkit/`](workflow-toolkit/) | **Workflow Toolkit** | Editor shortcut panel + **WorkflowToolkitRuntime** for PIE / dev iteration. |
| [`unreal-game-dev-starter-kit/`](unreal-game-dev-starter-kit/) | **Unreal Game Dev Starter Kit** | Documentation + templates for UE project structure, workflows, and checklists (no engine plugin in the pack). |
| [`immersive-labs-ue-bundle/`](immersive-labs-ue-bundle/) | **Immersive Labs UE Development Bundle** | Multi-download Fab bundle: [`stage-bundle.ps1`](immersive-labs-ue-bundle/scripts/stage-bundle.ps1) assembles plugin zips + starter kit (**≥ UE 5.4**). |

## Shared documentation

| Path | Description |
|------|-------------|
| [`docs/fab-listing-index.md`](docs/fab-listing-index.md) | **Index** of every product’s license, `FAB_LISTING*`, `SUPPORT`, `PACKAGING`, and test docs. |
| [`docs/fab-technical-reference.md`](docs/fab-technical-reference.md) | Fab technical requirements, publishing workflow, and links (applies to all code plugins here). |
| [`docs/unreal-plugin-testing-beginner.md`](docs/unreal-plugin-testing-beginner.md) | **Start here if you’re new to UE:** simple smoke-test steps for plugin products (no C++ knowledge required for testing). |
| Per-product test guides | Each product has **`docs/TESTING.md`** (detailed steps for that deliverable) where applicable. |
| [`docs/fab-bundle-strategy.md`](docs/fab-bundle-strategy.md) | **Bundles:** multiple Fab downloadables, **minimum UE 5.4**, one plugin zip per engine minor line. |
| [`scripts/README.md`](scripts/README.md) | Monorepo **RunUAT** / demo-sync helpers. |

## Repository layout

```
fab-products/                    # clone folder name can differ
├── README.md
├── docs/
│   ├── fab-listing-index.md     # publisher checklist (all products)
│   ├── fab-technical-reference.md
│   ├── unreal-plugin-testing-beginner.md
│   └── fab-bundle-strategy.md
├── scripts/                     # sync demos + build-fab-marketplace-drops-ue57.ps1
├── harbor-suite/
├── workflow-toolkit/
├── worldbuilder-templates/
├── worldbuilder-audit-convert/
├── level-selection-sets/
├── unreal-game-dev-starter-kit/
├── immersive-labs-ue-bundle/
└── <future-product>/
```

## Adding another Fab product

1. Create a new directory at the repo root (e.g. `my-next-plugin/`).
2. Include that product’s `README.md`, `CHANGELOG.md`, optional `docs/`, and plugin or asset layout.
3. Register it in the **Products** table above.

## License

Per-product licensing may differ; see each product folder. Include publisher copyright notices in source per Fab rules.
