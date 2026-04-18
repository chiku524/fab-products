# Packaging for Fab (publisher)

Fab expects a **working plugin** per **engine minor line** you sell (e.g. 5.4.x vs 5.5.x), validated packaging, and compliant descriptors. This product’s **minimum** engine is **UE 5.4**; newer **5.x** lines need their own built package.

## Pre-flight

1. Confirm **`CreatedBy`**, **`SupportURL`**, and optional **`DocsURL`** in `WorldBuilderAuditConvert.uplugin` match what you list on Fab (publisher: **Immersive Labs**).  
2. Set **`DocsURL`** when you publish public documentation (optional).  
3. After Fab approves the listing, add **`FabURL`** to the `.uplugin` file (string URL to your Fab product page).  
4. Confirm each module lists **`PlatformAllowList`** or **`PlatformDenyList`** (Win64 editor for v1).

## Automated packaging (optional)

From PowerShell:

```powershell
cd worldbuilder-audit-convert\scripts
.\package-plugin.ps1 -EngineRoot "C:\Program Files\Epic Games\UE_5.4" -UeVersionLabel "5.4"
```

See [`scripts/README.md`](../scripts/README.md). Output defaults to `worldbuilder-audit-convert/dist/`.

## Build a plugin zip (per engine version)

On a machine with the correct Unreal Engine installed:

```bat
RunUAT.bat BuildPlugin -Plugin="C:\Path\To\WorldBuilderAuditConvert\WorldBuilderAuditConvert.uplugin" -Package="C:\Out\WorldBuilderAuditConvert-UE5.4-Win64" -Rocket
```

- Run **once per engine minor line** you support on Fab (e.g. a package built with **5.4.x** for 5.4 customers). Minimum engine version for this plugin is **5.4**.  
- Use Epic’s **Package** workflow from the editor as an alternative if that is your standard QA path.  
- **Test** the output zip on a clean project before upload.

## Upload structure

- One **Fab downloadable** (or one per engine version, per Fab’s product setup) containing:
  - `WorldBuilderAuditConvert/` plugin folder with **source** and compiled binaries for the target.  
  - **`DOCUMENTATION.md`** at package root (or clearly linked path in listing).  
  - **`LICENSE`**, **`CHANGELOG.md`**, and `docs/` as shipped in this repository.

Do **not** ship `.exe` or `.msi` installers inside the plugin package (Fab restriction).

## Example project

Host the example project **separately** (zip, cloud link). Do **not** embed a second copy of the plugin inside it; customers copy the Fab plugin into `Plugins/` per `INSTALLATION.md`.

## QA matrix (minimum)

| Check | Pass criteria |
|-------|----------------|
| Clean project + enable plugin | Loads without blocking errors |
| Scan | Finds candidates on demo content |
| Preview / convert / export | Matches product description |
| Undo / revert | Restores prior state when feature is present |
| Package project | Your usual shipping test succeeds with plugin enabled |
