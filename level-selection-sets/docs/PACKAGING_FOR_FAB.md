# Packaging for Fab (publisher)

Fab expects a **working plugin** per supported engine version, validated packaging, and compliant descriptors.

## Pre-flight

1. Replace all **`[PUBLISHER_NAME]`** / **`[SUPPORT_EMAIL]`** placeholders in docs and source copyright lines.  
2. Set **`CreatedBy`**, **`SupportURL`**, and **`DocsURL`** in `LevelSelectionSets.uplugin` to your real values when you publish.  
3. After Fab approves the listing, add **`FabURL`** to the `.uplugin` file (string URL to your Fab product page).  
4. Confirm each module lists **`PlatformAllowList`** or **`PlatformDenyList`** (Win64 editor for v1).

## Build a plugin zip (per engine version)

On a machine with the correct Unreal Engine installed:

```bat
RunUAT.bat BuildPlugin -Plugin="C:\Path\To\LevelSelectionSets\LevelSelectionSets.uplugin" -Package="C:\Out\LevelSelectionSets-UE5.4-Win64" -Rocket
```

- Run once per **major.minor** engine line you support (e.g. 5.4.x package for 5.4 customers).  
- Use Epic’s **Package** workflow from the editor as an alternative if that is your standard QA path.  
- **Test** the output zip on a clean project before upload.

## Upload structure

- One **Fab downloadable** (or one per engine version, per Fab’s product setup) containing:
  - `LevelSelectionSets/` plugin folder with **source** and compiled binaries for the target.  
  - **`DOCUMENTATION.md`** at package root (or clearly linked path in listing).  
  - **`LICENSE`**, **`CHANGELOG.md`**, and `docs/` as shipped in this repository.

Do **not** ship `.exe` or `.msi` installers inside the plugin package (Fab restriction).

## Example project

Host the example project **separately** (zip, cloud link). Do **not** embed a second copy of the plugin inside it; customers copy the Fab plugin into `Plugins/` per `INSTALLATION.md`.

## QA matrix (minimum)

| Check | Pass criteria |
|-------|----------------|
| Clean project + enable plugin | Loads without blocking errors |
| Save set | Stores current selection under a name |
| Recall set | Re-selects actors that still exist |
| Delete / rename | List updates as expected |
| Package project | Your usual shipping test succeeds with plugin enabled |
