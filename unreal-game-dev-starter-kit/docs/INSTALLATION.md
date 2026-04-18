# Installation

This product is **documentation and text templates**, not an Unreal plugin. There is nothing to compile or enable in the editor.

## What you receive

- Markdown (`.md`) guides under `docs/`.  
- Copy-paste templates under `templates/`.  
- This file and `DOCUMENTATION.md` at the product root.

## Recommended setup

1. **Unzip** the Fab download to a folder you keep as a **reference library** (e.g. `Documentation/UnrealGameDevStarterKit/`).  
2. **Skim** `DOCUMENTATION.md` and decide which chapters matter for your current milestone (new project vs. mid-production).  
3. **Apply** templates to your game repository:
   - Merge [`templates/gitignore-additions.unreal.txt`](../templates/gitignore-additions.unreal.txt) into your project `.gitignore` as appropriate.  
   - If you use Git LFS, start from [`templates/gitattributes-lfs-sample.txt`](../templates/gitattributes-lfs-sample.txt) and adjust to your asset mix.  
4. **Share** relevant pages with your team (version-controlled wiki, Notion, or printed PDFs exported from Markdown).

## Optional: export to PDF

Use any Markdown-to-PDF tool (VS Code extension, Pandoc, or your CI) to produce a **single PDF** for producers or external partners who will not browse raw files.
