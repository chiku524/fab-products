# Buyer guide — Immersive Labs UE Development Bundle

You receive **several files** (Fab may show them as multiple downloadables on one listing). **Minimum Unreal Engine: 5.4** for the plugins; use the zip that matches **your editor’s minor version** (e.g. 5.4.x plugins with a 5.4.x editor).

## What to download

| File (typical name) | What it is |
|---------------------|------------|
| `LevelSelectionSets-UE5.4-Win64.zip` | Editor plugin — **Level Selection Sets** |
| `WorldBuilderAuditConvert-UE5.4-Win64.zip` | Editor plugin — **WorldBuilder Audit & Convert** |
| `UnrealGameDevStarterKit-docs-v*.zip` | **Documentation + templates** (no plugin) |

If your listing includes **5.5** (or other lines), you will see parallel names like `UE5.5`—pick **one** line that matches your installed engine.

## Install order

1. **Unreal Game Dev Starter Kit** — Unzip anywhere; read `DOCUMENTATION.md` first (workflow and Git habits). No install into `Plugins/`.
2. **Each plugin** — Unzip so you get a single folder (e.g. `LevelSelectionSets`) containing the `.uplugin` file. Copy that folder into your project’s **`Plugins/`** directory. See each product’s `docs/INSTALLATION.md` inside the zip.
3. Regenerate Visual Studio project files, **build Development Editor**, enable plugins under **Edit → Plugins**.

## Help

- **nico.builds@outlook.com** — include your **exact** engine version (e.g. 5.4.4) and which file you downloaded.
