# Workflow Toolkit — product documentation

Primary **documentation index** for the Fab product (use with [`README.md`](README.md)).

| Document | Audience | Description |
|----------|----------|-------------|
| [README.md](README.md) | All | Product overview, layout, Fab table |
| [docs/FAB_LISTING_COPY.md](docs/FAB_LISTING_COPY.md) | Publisher | Copy for Fab listing fields |
| [docs/SUPPORT.md](docs/SUPPORT.md) | Customers | Support and scope |
| [docs/PACKAGING_FOR_FAB.md](docs/PACKAGING_FOR_FAB.md) | Publisher | RunUAT, zips |
| [docs/TESTING.md](docs/TESTING.md) | Publisher / QA | Editor + runtime tests |
| [docs/VERIFICATION.md](docs/VERIFICATION.md) | Publisher | Packaged build smoke test |
| [docs/MEDIA.md](docs/MEDIA.md) | Publisher | Listing art checklist |
| [scripts/README.md](scripts/README.md) | Publisher | `package-plugin.ps1` |
| [scripts/copy-packaged-plugin-to-test-project.ps1](scripts/copy-packaged-plugin-to-test-project.ps1) | Publisher / dev | Copy `dist/WorkflowToolkit-UE*-Win64` to a test project |
| [CHANGELOG.md](CHANGELOG.md) | All | Version history |
| [LICENSE](LICENSE) | All | License terms |

**Layout:** `WorkflowToolkit/` = canonical plugin; `WorkflowToolkitDemo/` = optional sample project. **Packaged output** goes to `dist/` (see `.gitignore`); the monorepo script `fab-products/scripts/build-fab-marketplace-drops-ue57.ps1` packages **all five** code plugins in one go (Win64 UE 5.7 by default).

**Monorepo:** [Publisher index (all products)](../docs/fab-listing-index.md) · [listing art placeholders](../docs/fab-listing-media/workflow-toolkit/) (see [docs/MEDIA.md](docs/MEDIA.md)).
