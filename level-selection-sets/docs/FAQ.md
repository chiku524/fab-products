# FAQ

## General

**What does this plugin do?**  
It lets you **save named actor selections** in the level editor and **recall** them with one action—so you spend less time re-selecting the same groups of actors in large levels.

**Who is it for?**  
Level designers, environment artists, lighting artists, and anyone who iterates on the same groups of actors repeatedly.

**Which engine versions are supported?**  
Unreal Engine **5.4**, **5.5**, and **5.6**. Use the download package that matches your engine version exactly.

**Mac or Linux editor?**  
Version 1 targets **Windows (Win64)** editor only unless the listing states otherwise.

## Installation and build

**The plugin will not load.**  
Confirm you copied `LevelSelectionSets` under `YourProject/Plugins/`, regenerated project files, and built the **Editor** target successfully. Check **Output Log** for module load errors.

**Compile errors after update.**  
Ensure your engine version matches the plugin package. Rebuild the editor; if you use a custom engine, verify compatibility with the supported versions listed on Fab.

## Usage

**A recalled selection is missing actors.**  
Actors may have been deleted, moved to another level, or duplicated in a way that breaks stored references. Re-save the set after your level structure stabilizes.

**I want the same sets in every sublevel.**  
Behavior may depend on how sets are stored (per persistent level vs. streamed layers). See the shipped build notes and `USER_GUIDE.md`.

**Does this replace Unreal’s built-in layers or folders?**  
No—it complements them. Folders organize content; **selection sets** are a fast **recall** workflow for the actors you already care about.

## Licensing and support

**Where is the license?**  
See `LICENSE` next to this documentation in the product package.

**How do I get support?**  
See [SUPPORT.md](SUPPORT.md) for contact information and what to include in a report.
