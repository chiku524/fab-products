# Packaging for Fab (publisher)

This product ships as a **zip of Markdown, templates, and license files**—no build step.

## Pre-flight

1. Confirm **`LICENSE`** and **`docs/SUPPORT.md`** match the Fab listing (publisher **Immersive Labs**, **nico.builds@outlook.com**).  
2. Set the **Fab listing** description from [FAB_LISTING_COPY.md](FAB_LISTING_COPY.md).  
3. Proofread links between files (relative paths).

## Create the buyer zip

From the product root `unreal-game-dev-starter-kit/`:

- Include at minimum:
  - `README.md`, `DOCUMENTATION.md`, `CHANGELOG.md`, `LICENSE`  
  - Entire `docs/` folder  
  - Entire `templates/` folder  
  - `example-project/README.md` if present  

**Exclude:** publisher-only notes you do not want shipped (keep them out of the folder or use a `publisher-only/` folder not zipped).

### Example (PowerShell)

```powershell
Compress-Archive -Path README.md,DOCUMENTATION.md,CHANGELOG.md,LICENSE,docs,templates,example-project `
  -DestinationPath UnrealGameDevStarterKit-v1.0.0.zip
```

Adjust paths to your staging directory layout.

## Upload

- One **primary downloadable** per major kit version (or follow Fab’s versioning UI).  
- File type: **zip** (no `.exe` installers inside per typical Fab rules).

## QA before publish

- [ ] Unzip to a clean folder; open `DOCUMENTATION.md`; follow three random links—each resolves.  
- [ ] Templates are **plain text** and open in Notepad/VS Code without garbled encoding (UTF-8).  
- [ ] License matches what the listing promises.
