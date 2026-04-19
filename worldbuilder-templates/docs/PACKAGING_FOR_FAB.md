# Packaging for Fab — World Builder Templates

1. Confirm **`CreatedBy`**, **`SupportURL`**, and optional **`DocsURL`** in `WorldBuilderTemplates.uplugin` match the Fab listing.
2. Ensure **`CanContainContent`** remains **true** so shipped sample maps under `Content/` are included in the zip.
3. From `scripts/`, run **`package-plugin.ps1`** (see `scripts/README.md`) to produce `dist/WorldBuilderTemplates-UE<ver>-Win64/`.
4. Smoke-test the packaged folder on a clean project: copy the plugin into `Plugins/`, regenerate, build editor, enable the plugin, open **Window → Level Editor → World Builder Templates** and verify sample maps appear.

Regenerating sample maps from source (maintainers): see [SAMPLE_MAPS.md](SAMPLE_MAPS.md).
