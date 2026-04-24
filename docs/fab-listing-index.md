# Fab listing readiness — product index

Use this as a **publisher checklist** before you submit or update a [Fab](https://www.fab.com/) listing. Each product folder should have **License**, **Support**, **packaging** instructions, **paste-ready listing** text, and **test/verification** steps. A **`DOCUMENTATION.md` master index** at the product root links the same material in one place (naming matches products that ship a doc pack to buyers).

| Product | Folder | License | Listing copy | Support | Pack for Fab | Test | Verify pack |
|--------|--------|---------|-------------|---------|-------------|------|------------|
| Harbor Suite | [`harbor-suite/`](../harbor-suite/) | [`LICENSE`](../harbor-suite/LICENSE) | [`docs/FAB_LISTING.md`](../harbor-suite/docs/FAB_LISTING.md) | [`docs/SUPPORT.md`](../harbor-suite/docs/SUPPORT.md) | [`docs/PACKAGING_FOR_FAB.md`](../harbor-suite/docs/PACKAGING_FOR_FAB.md) | [`docs/TESTING.md`](../harbor-suite/docs/TESTING.md) | [`docs/VERIFICATION.md`](../harbor-suite/docs/VERIFICATION.md) |
| Level Selection Sets | [`level-selection-sets/`](../level-selection-sets/) | [`LICENSE`](../level-selection-sets/LICENSE) | [`docs/FAB_LISTING_COPY.md`](../level-selection-sets/docs/FAB_LISTING_COPY.md) | [`docs/SUPPORT.md`](../level-selection-sets/docs/SUPPORT.md) | [`docs/PACKAGING_FOR_FAB.md`](../level-selection-sets/docs/PACKAGING_FOR_FAB.md) | [`docs/TESTING.md`](../level-selection-sets/docs/TESTING.md) | [`docs/VERIFICATION.md`](../level-selection-sets/docs/VERIFICATION.md) |
| World Builder Templates | [`worldbuilder-templates/`](../worldbuilder-templates/) | [`LICENSE`](../worldbuilder-templates/LICENSE) | [`docs/FAB_LISTING_COPY.md`](../worldbuilder-templates/docs/FAB_LISTING_COPY.md) | [`docs/SUPPORT.md`](../worldbuilder-templates/docs/SUPPORT.md) | [`docs/PACKAGING_FOR_FAB.md`](../worldbuilder-templates/docs/PACKAGING_FOR_FAB.md) | [`docs/TESTING.md`](../worldbuilder-templates/docs/TESTING.md) | [`docs/VERIFICATION.md`](../worldbuilder-templates/docs/VERIFICATION.md) |
| WorldBuilder Audit & Convert | [`worldbuilder-audit-convert/`](../worldbuilder-audit-convert/) | [`LICENSE`](../worldbuilder-audit-convert/LICENSE) | [`docs/FAB_LISTING_COPY.md`](../worldbuilder-audit-convert/docs/FAB_LISTING_COPY.md) | [`docs/SUPPORT.md`](../worldbuilder-audit-convert/docs/SUPPORT.md) | [`docs/PACKAGING_FOR_FAB.md`](../worldbuilder-audit-convert/docs/PACKAGING_FOR_FAB.md) | [`docs/TESTING.md`](../worldbuilder-audit-convert/docs/TESTING.md) | [`docs/SUBMISSION_CHECKLIST.md`](../worldbuilder-audit-convert/docs/SUBMISSION_CHECKLIST.md) |
| Workflow Toolkit | [`workflow-toolkit/`](../workflow-toolkit/) | [`LICENSE`](../workflow-toolkit/LICENSE) | [`docs/FAB_LISTING_COPY.md`](../workflow-toolkit/docs/FAB_LISTING_COPY.md) | [`docs/SUPPORT.md`](../workflow-toolkit/docs/SUPPORT.md) | [`docs/PACKAGING_FOR_FAB.md`](../workflow-toolkit/docs/PACKAGING_FOR_FAB.md) | [`docs/TESTING.md`](../workflow-toolkit/docs/TESTING.md) | [`docs/VERIFICATION.md`](../workflow-toolkit/docs/VERIFICATION.md) |
| Unreal Game Dev Starter Kit | [`unreal-game-dev-starter-kit/`](../unreal-game-dev-starter-kit/) | [`LICENSE`](../unreal-game-dev-starter-kit/LICENSE) | [`docs/FAB_LISTING_COPY.md`](../unreal-game-dev-starter-kit/docs/FAB_LISTING_COPY.md) | [`docs/SUPPORT.md`](../unreal-game-dev-starter-kit/docs/SUPPORT.md) | [`docs/PACKAGING_FOR_FAB.md`](../unreal-game-dev-starter-kit/docs/PACKAGING_FOR_FAB.md) | [`docs/TESTING.md`](../unreal-game-dev-starter-kit/docs/TESTING.md) | [`docs/SUBMISSION_CHECKLIST.md`](../unreal-game-dev-starter-kit/docs/SUBMISSION_CHECKLIST.md) |
| Immersive Labs UE Bundle | [`immersive-labs-ue-bundle/`](../immersive-labs-ue-bundle/) | [`LICENSE`](../immersive-labs-ue-bundle/LICENSE) | [`docs/FAB_LISTING_COPY.md`](../immersive-labs-ue-bundle/docs/FAB_LISTING_COPY.md) | [`docs/SUPPORT.md`](../immersive-labs-ue-bundle/docs/SUPPORT.md) | [`docs/PUBLISHER_ASSEMBLY.md`](../immersive-labs-ue-bundle/docs/PUBLISHER_ASSEMBLY.md) | [`docs/TESTING.md`](../immersive-labs-ue-bundle/docs/TESTING.md) | [`docs/SUBMISSION_CHECKLIST.md`](../immersive-labs-ue-bundle/docs/SUBMISSION_CHECKLIST.md) |

| Product | Master doc index |
|--------|------------------|
| Harbor Suite | [`DOCUMENTATION.md`](../harbor-suite/DOCUMENTATION.md) |
| Level Selection Sets | [`DOCUMENTATION.md`](../level-selection-sets/DOCUMENTATION.md) |
| World Builder Templates | [`DOCUMENTATION.md`](../worldbuilder-templates/DOCUMENTATION.md) |
| WorldBuilder Audit & Convert | [`DOCUMENTATION.md`](../worldbuilder-audit-convert/DOCUMENTATION.md) |
| Workflow Toolkit | [`DOCUMENTATION.md`](../workflow-toolkit/DOCUMENTATION.md) |
| Unreal Game Dev Starter Kit | [`DOCUMENTATION.md`](../unreal-game-dev-starter-kit/DOCUMENTATION.md) |
| Immersive Labs UE Bundle | [`DOCUMENTATION.md`](../immersive-labs-ue-bundle/DOCUMENTATION.md) |

**Shared (all code plugins):** [fab-technical-reference.md](fab-technical-reference.md) · [unreal-plugin-testing-beginner.md](unreal-plugin-testing-beginner.md)  
**Fab listing editor (all portal fields, checklist):** [fab-portal-listing-fields.md](fab-portal-listing-fields.md) — also appended as **“Fab portal — full listing form”** at the end of each product’s `docs/FAB_LISTING.md` or `docs/FAB_LISTING_COPY.md`.

**Pre-flight:** [`scripts/verify-fab-prerequisites.ps1`](../scripts/verify-fab-prerequisites.ps1) (add **`-CheckBuildOutput`** after a local build) · **Multi-plugin RunUAT zip (Win64 UE 5.7, five code plugins + zips):** [`scripts/build-fab-marketplace-drops-ue57.ps1`](../scripts/build-fab-marketplace-drops-ue57.ps1)  
**Immersive Labs site sample zips (optional second downloadable):** `immersive.labs` repo `scripts/package-fab-product-zips.ps1` (separate from Fab plugin binaries).  
**Listing thumbnails & gallery (24 AI placeholders):** [fab-listing-media/README.md](fab-listing-media/README.md) — each product’s `docs/MEDIA.md` links the folder for that product.

## repo-only / not a Fab product

| Path | Note |
|------|------|
| [`docs/`](../docs/) (this index) | Meta documentation only. |
| [`scripts/`](../scripts/) | Build helpers; not a listing. |
| `fab-marketplace-drops/` | **Gitignored** local output from the bulk build script. |
