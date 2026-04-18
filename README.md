# Epic Fab products

Monorepo for [Fab](https://www.fab.com/) listings: specifications, documentation, Unreal Engine plugin sources, and template/knowledge products. Add each product as its **own top-level directory** (kebab-case slug).

## Products

| Directory | Product | Description |
|-----------|---------|-------------|
| [`worldbuilder-audit-convert/`](worldbuilder-audit-convert/) | **WorldBuilder Audit & Convert** | Editor plugin: audit levels for world-building inefficiencies; batch toward ISM/HISM with presets, preview, and reports. |
| [`level-selection-sets/`](level-selection-sets/) | **Level Selection Sets** | Editor plugin: save named actor selection sets per level and recall them for lighting passes, prop sweeps, and batch edits. |
| [`unreal-game-dev-starter-kit/`](unreal-game-dev-starter-kit/) | **Unreal Game Dev Starter Kit** | Documentation + templates: project structure, workflows, source control, and shipping-minded checklists for UE game projects (no engine plugin). |

## Shared documentation

| Path | Description |
|------|-------------|
| [`docs/fab-technical-reference.md`](docs/fab-technical-reference.md) | Fab technical requirements, publishing workflow, and links (applies to all code plugins here). |
| [`docs/unreal-plugin-testing-beginner.md`](docs/unreal-plugin-testing-beginner.md) | **Start here if you’re new to UE:** simple smoke-test steps for plugin products (no C++ knowledge required for testing). |

## Repository layout

```
fab-products/                    # clone folder name can differ
├── README.md                    # this file
├── docs/
│   ├── fab-technical-reference.md
│   └── unreal-plugin-testing-beginner.md
├── worldbuilder-audit-convert/
│   ├── README.md
│   ├── CHANGELOG.md
│   ├── docs/
│   └── WorldBuilderAuditConvert/
├── level-selection-sets/
│   ├── README.md
│   ├── CHANGELOG.md
│   ├── docs/
│   └── LevelSelectionSets/
├── unreal-game-dev-starter-kit/
│   ├── README.md
│   ├── CHANGELOG.md
│   ├── docs/
│   └── templates/
└── <future-product>/            # add new Fab products as sibling folders
```

## Adding another Fab product

1. Create a new directory at the repo root (e.g. `my-next-plugin/`).
2. Include that product’s `README.md`, `CHANGELOG.md`, optional `docs/`, and plugin or asset layout.
3. Register it in the **Products** table above.

## License

Per-product licensing may differ; see each product folder. Include publisher copyright notices in source per Fab rules.
