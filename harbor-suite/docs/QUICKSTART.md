# Harbor Suite — quick start

This guide assumes a **Windows** machine with **Unreal 5.7+** and **Visual Studio 2022** installed.

## 1. Open the sample project

1. Clone or copy this repository.
2. Open `**harbor-suite/Harbor/Harbor.uproject`** in the **Unreal Editor** (see [Opening `Harbor.uproject](#opening-harboruproject)` if double-click does nothing).
3. If prompted to **rebuild modules**, accept and let the editor compile `Harbor` and `HarborSuite`.

**Want the project to live under `Documents\Unreal Projects` (like other UE work) without copying?** Run the script below once. It creates a **directory junction** (same files as the repo; no duplicate). After that, opening `Documents\Unreal Projects\Harbor\Harbor.uproject` is the same project. **Harbor Suite** is already **enabled** in `Harbor.uproject`; the editor loads it on startup (use **Edit → Plugins** only if you turned it off).

```powershell
cd path\to\fab-products
.\scripts\Junction-UE-Project-To-Documents.ps1 `
  -UProjectPath ".\harbor-suite\Harbor\Harbor.uproject" -OpenAfter
```

Or double-click `**Open-Harbor-From-Documents.cmd**` in the `**harbor-suite\`** folder (creates/updates the junction, then starts Unreal the same way as double-clicking the `.uproject`).

*Limitation:* A normal **double-click on `.uproject` in Explorer cannot** run a “copy or link, then open” step—that would require changing Windows file types globally. This script (or a shortcut to it) is the supported “create link under Documents, then open” path.

## 2. Regenerate Visual Studio files (if needed)

If you do not see **Generate Visual Studio project files** on the `.uproject` context menu:

```powershell
cd path\to\fab-products\harbor-suite\scripts
.\generate-ue-project-files.ps1 -UProjectPath "C:\full\path\to\Harbor\Harbor.uproject"
```

Then open `**Harbor.sln**`, set **Development Editor**, and build.

## 3. Enable the plugin (if needed)

`HarborSuite` is **Enabled** in `Harbor.uproject` by default. If the editor does not load the panel after a first successful compile:

1. **Edit → Plugins**
2. Search **Harbor Suite**
3. Ensure it is **enabled** and restart the editor if prompted.

## 4. Open the Harbor Suite panel

1. **Window → Level Editor → Harbor Suite** (nomad tab).

You should see four pillars: **Charts**, **Stowage**, **Shakedown**, **Clearance**.

## 5. Try each hero action (2 minutes)


| Pillar        | Try this                                                                        |
| ------------- | ------------------------------------------------------------------------------- |
| **Charts**    | Toggle a checklist step; click **Save all dirty packages**                      |
| **Stowage**   | Select actors in the level → **Apply prefix to selection**                      |
| **Shakedown** | Start **PIE** → **Move player to first PlayerStart**; try time dilation buttons |
| **Clearance** | **Run scan** on the open level → **Select labels containing "Problem"**         |


Charts progress is stored at `Harbor/Saved/HarborSuite/ChartsState.json` (per project).

## 6. Author Harbor Annex (optional but recommended for Fab)

The map asset is **not** committed as binary. Follow `**Harbor/Content/Maps/README.md`** and `**docs/DEMO_MAP_BEAT_SHEET.md**` to build the demo level.

## Next

- Full QA: [TESTING.md](TESTING.md)
- Fab packaging: [PACKAGING_FOR_FAB.md](PACKAGING_FOR_FAB.md)

---

## Opening `Harbor.uproject`

**Double-clicking** a `.uproject` on Windows **should** launch **UnrealVersionSelector** and then the right engine. If nothing happens or the wrong tool opens, that is a **local Windows file association** issue—not a bug in this repo.

1. **Epic Games Launcher → Unreal Engine → Library** — **Launch** your **5.7** editor, then **File → Open** and choose `Harbor.uproject`.
2. **Regenerate project files** (section 2 above), then open `**Harbor.sln`** and build **HarborEditor** before expecting a clean first open.
3. **Engine mismatch** — If a different engine version opens, you may see a **retarget** or **rebuild** dialog; use the engine line that matches `**EngineAssociation`** in `Harbor.uproject` (e.g. **5.7**).
4. **No “Open with Unreal”** — Use Epic’s installer to register file types, or run
  `UnrealVersionSelector.exe /projectfiles` (or this repo’s `generate-ue-project-files.ps1`) from a path under your **Epic Games** install.

See also **AGENTS.md** in the monorepo for the same Windows / `UnrealVersionSelector` note.