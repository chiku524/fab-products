# FAQ

## General

**What does this plugin do?**  
It scans your level for patterns common in manual world building—especially many copies of the same static mesh—and helps you convert eligible sets into instanced setups (ISM/HISM) with preview and reporting. It is an **editor** tool; it does not replace Unreal’s full profiling stack.

**Who is it for?**  
Environment artists, level designers, technical artists, and small teams polishing large environments.

**Which engine versions are supported?**  
Unreal Engine **5.4**, **5.5**, and **5.6**. Use the download package that matches your engine version exactly.

**Mac or Linux editor?**  
Version 1 targets **Windows (Win64)** editor only unless the listing states otherwise.

## Installation and build

**The plugin will not load.**  
Confirm you copied `WorldBuilderAuditConvert` under `YourProject/Plugins/`, regenerated project files, and built the **Editor** target successfully. Check **Output Log** for module load errors.

**Compile errors after update.**  
Ensure your engine version matches the plugin package. Rebuild the editor; if you use a custom engine, verify compatibility with the supported versions listed on Fab.

## Usage

**Nothing shows up after scan.**  
Your level may have no qualifying repeats, thresholds may be too strict, or exclusions may filter everything. Widen the scan scope, adjust the preset, or lower thresholds if the UI allows.

**I only want part of the level processed.**  
Select actors or folders first (per the tool’s scope options), or add exclusions for areas that must stay manual.

**Will this change my art style?**  
Conversion targets **placement and instancing**, not automatic material overhauls. Always use preview on representative shots; keep backups.

## Licensing and support

**Where is the license?**  
See `LICENSE` next to this documentation in the product package.

**How do I get support?**  
See [SUPPORT.md](SUPPORT.md) for contact information and what to include in a report.
