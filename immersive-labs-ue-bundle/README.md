# Immersive Labs — Unreal Engine development bundle

**Fab-oriented meta-product** for this monorepo: one **purchaser experience** made of **multiple downloadables**—code plugins (minimum **UE 5.4**) plus the **Unreal Game Dev Starter Kit** (documentation). Nothing in this folder replaces building the individual products; it **assembles and documents** how to ship them together.

| Role | Start here |
|------|----------------|
| **Publisher** (you) | [`docs/PUBLISHER_ASSEMBLY.md`](docs/PUBLISHER_ASSEMBLY.md) and [`scripts/stage-bundle.ps1`](scripts/stage-bundle.ps1) |
| **Testing** (staging & zips) | [`docs/TESTING.md`](docs/TESTING.md) |
| **Buyer** (post on Fab) | [`docs/BUYER_GUIDE.md`](docs/BUYER_GUIDE.md) |
| **Fab listing text** | [`docs/FAB_LISTING_COPY.md`](docs/FAB_LISTING_COPY.md) |

## What’s in the bundle (components)

| Component | Source in repo |
|-----------|----------------|
| **Level Selection Sets** | [`../level-selection-sets/`](../level-selection-sets/) |
| **WorldBuilder Audit & Convert** | [`../worldbuilder-audit-convert/`](../worldbuilder-audit-convert/) |
| **Unreal Game Dev Starter Kit** | [`../unreal-game-dev-starter-kit/`](../unreal-game-dev-starter-kit/) |

## Minimum engine

**Unreal Engine 5.4+** for plugins (one built package per **minor line** you sell, e.g. 5.4.x vs 5.5.x). See [`../docs/fab-bundle-strategy.md`](../docs/fab-bundle-strategy.md).

## License

[`LICENSE`](LICENSE) — per-product licenses still apply inside each downloadable.
