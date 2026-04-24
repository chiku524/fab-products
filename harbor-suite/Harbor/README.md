# Harbor (sample C++ project)

This is the **Harbor Suite** sample **C++** project (not a separate “game”—it exists to build and use the **Harbor Suite** editor plugin at **`Plugins/HarborSuite/`**).

## Open

- Double-click **`Harbor.uproject`**, *or* from the Unreal **File** menu, **Open** and browse to it. If Windows does not launch the editor, see **[`../docs/QUICKSTART.md`](../docs/QUICKSTART.md#opening-harboruproject)** (file association, engine version, first compile).

- Engine: Unreal **5.7** (`.uproject` **EngineAssociation**; **5.7+** may work with retarget prompts).

## Build

1. **Generate Visual Studio project files** for `Harbor.uproject` (or run `../scripts/generate-ue-project-files.ps1`).
2. Build **HarborEditor** | **Development Editor**.

## Editor UI

**Window → Level Editor → Harbor Suite**

## Map content

The **Harbor Annex** level is documented in **`Content/Maps/README.md`** and `../docs/DEMO_MAP_BEAT_SHEET.md` — author it in the Content Browser (`.umap` is not committed here).

## Docs

Product documentation: **`../docs/`** (start with `QUICKSTART.md`).
