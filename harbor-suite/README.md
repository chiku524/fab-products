# Harbor Suite

**Harbor Suite** is a Fab-oriented **Unreal Engine editor workflow** product for **solo indies and small teams**. It ships as:

- A **plugin** (`HarborSuite`) with four pillars: **Charts**, **Stowage**, **Shakedown**, and **Clearance**.
- A **sample C++ project** (`Harbor`) that embeds the plugin under `Harbor/Plugins/HarborSuite`.

It is one **product** in the [fab-products monorepo](../README.md).

## Quick links

Monorepo **Fab checklist** (all products): [`../docs/fab-listing-index.md`](../docs/fab-listing-index.md)

| Document | Purpose |
|----------|---------|
| [docs/QUICKSTART.md](docs/QUICKSTART.md) | Open the `Harbor` sample project and verify the panel |
| [docs/TESTING.md](docs/TESTING.md) | Publisher / QA verification |
| [docs/DEMO_MAP_BEAT_SHEET.md](docs/DEMO_MAP_BEAT_SHEET.md) | **Harbor Annex** tour script (author the map in-editor) |
| [docs/PACKAGING_FOR_FAB.md](docs/PACKAGING_FOR_FAB.md) | RunUAT and deliverables |
| [docs/FAB_LISTING.md](docs/FAB_LISTING.md) | Listing copy and positioning |
| [docs/TRADEMARK_NOTE.md](docs/TRADEMARK_NOTE.md) | Brand / naming due diligence |
| [DOCUMENTATION.md](DOCUMENTATION.md) | Full index |

## Requirements

- **Unreal Engine 5.7+** (`.uproject` **`EngineAssociation`** and plugin **`EngineVersion`** are pinned to **5.7**).
- **Windows 64-bit** editor for the editor module (matches `PlatformAllowList` on the plugin).
- **Visual Studio 2022** with the C++ game development workload (or equivalent build tools).

**Compile:** From the engine tree,  
`Engine\Build\BatchFiles\Build.bat HarborEditor Win64 Development -Project="...\Harbor\Harbor.uproject" -WaitMutex`  
validates the full editor target (used for CI-style checks on this repo).

## Repository layout

```
harbor-suite/
  Harbor/                 # Sample project (open this .uproject)
    Harbor.uproject
    Plugins/HarborSuite/      # Plugin source (Fab artifact)
    Source/Harbor/          # Minimal game module
    Content/Maps/README.md      # How to create Harbor Annex
  docs/                       # Product documentation
  scripts/                    # Project files + packaging helpers
  LICENSE
```

## Support

See [docs/SUPPORT.md](docs/SUPPORT.md).
