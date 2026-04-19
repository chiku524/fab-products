# Testing — World Builder Templates

## Compile

Build your game project’s **Editor** target with the plugin under `Plugins/WorldBuilderTemplates/` (Development Editor).

## Functional

1. **Edit → Plugins** — enable **World Builder Templates**; restart if prompted.
2. **Window → Level Editor → World Builder Templates** — panel lists:
   - `WBT_Template_Outdoor`, `WBT_Template_IndoorBlockout`, `WBT_Template_Ocean`, `WBT_Template_City` (plugin Content).
   - Worlds under **Project Settings → Plugins → World Builder Templates → Extra package path roots** (default includes `/Engine/Maps/Templates`).
3. **Replace current level** (or double-click a row) — loads the template as the active map; resolve any save prompts for the current level first.

## Regenerate sample maps (maintainers)

See [SAMPLE_MAPS.md](SAMPLE_MAPS.md).

## Package smoke test (Fab)

Run `scripts/package-plugin.ps1`, copy the output `WorldBuilderTemplates-UE*-Win64` folder into a clean project’s `Plugins/`, regenerate, build, and repeat the steps above.
