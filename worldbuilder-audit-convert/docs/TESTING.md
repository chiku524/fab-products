# Testing — WorldBuilder Audit & Convert

This guide covers how to **validate** the product in Unreal. General Unreal smoke-test steps (C++ project, Plugins folder, first compile) are in `[../../docs/unreal-plugin-testing-beginner.md](../../docs/unreal-plugin-testing-beginner.md)`.

---

## 1. Product state vs. test depth

The **intended** end-to-end workflow (scan → review → preview → convert → export) is described in `[USER_GUIDE.md](USER_GUIDE.md)`. The editor module may still be **mid-implementation** (menus, tabs, and audit UI are not guaranteed complete until shipped).


| Phase                              | What to test                                                                                                            |
| ---------------------------------- | ----------------------------------------------------------------------------------------------------------------------- |
| **Current / pre-feature-complete** | Plugin **compiles**, **loads**, **no startup errors** in Output Log.                                                    |
| **Feature-complete**               | Full workflow in `[USER_GUIDE.md](USER_GUIDE.md)`: scan scope, presets, preview, conversion, export, revert if offered. |


Until the UI is fully wired, treat **Section 3** as mandatory and **Section 4** as the target checklist when features land.

---

## 2. Prerequisites

- **Unreal Editor** matching the **packaged** plugin minor line (e.g. 5.7.x editor for `WorldBuilderAuditConvert-UE5.7-Win64`).
- **Windows 64-bit** editor (v1 target).
- **Visual Studio 2022** (or Build Tools) able to build **Development Editor**.
- Test using the **RunUAT output** or the **Fab zip**, not only an unbuilt source tree, when validating what buyers receive.

---

## 3. Smoke test (always run before release)

### 3.1 Install into a clean C++ project

1. Create a **C++** project (any game template).
2. Close the editor.
3. Copy `**WorldBuilderAuditConvert`** (folder with `WorldBuilderAuditConvert.uplugin` and `Source/`) to:
  - `YourProject/Plugins/WorldBuilderAuditConvert/`
4. **Generate Visual Studio project files** from the `.uproject`.
5. Build **Development Editor** from the solution.
6. Launch editor; **Edit → Plugins** → enable **WorldBuilder Audit & Convert** → **Restart** if required.

**Pass:** Solution builds with **0 errors**; editor starts; plugin can be enabled.

### 3.2 Output Log

1. **Window → Developer Tools → Output Log**.
2. Load a level; watch log during startup.

**Pass:** No **Error** lines clearly tied to **WorldBuilderAuditConvertEditor** or the plugin’s module name.

### 3.3 Menu / entry point (when implemented)

When the module registers a **menu**, **nomad tab**, or **toolbar** entry:

1. Open the documented path (see release notes or **Window / Tools** menus).
2. Open the UI once.

**Pass:** Panel or window appears without assert/crash.

If **no UI** is registered yet, **Section 3.1–3.2** still count as the release gate; document “UI pending” in internal notes.

---

## 4. Functional test (when audit UI is available)

Run these in a level with **many repeated static mesh** actors (or a test map built for instancing tests).


| Step | Action                                                       | Pass criteria                                                         |
| ---- | ------------------------------------------------------------ | --------------------------------------------------------------------- |
| 1    | **Scan** current level (or selection per UI)                 | Results table populates; no crash on large levels.                    |
| 2    | **Review** rows                                              | Counts and grouping look plausible; low-confidence rows identifiable. |
| 3    | Change **preset** (e.g. Forest / City / Interior) and rescan | Results change in a explainable way or thresholds apply.              |
| 4    | **Preview / dry-run**                                        | Shows affected actors without destructive apply (if implemented).     |
| 5    | **Convert** a small group                                    | Level updates; ISM/HISM or intended actors created per design.        |
| 6    | **Export** CSV or JSON                                       | File writes; opens in text editor or spreadsheet.                     |
| 7    | **Undo** or **Revert**                                       | Level returns to prior state without orphan data (if supported).      |
| 8    | **Save level**; restart editor                               | No corruption; plugin loads again cleanly.                            |


Use large levels only after a small-level pass. Prefer **source control** or a duplicated map before bulk conversion.

---

## 5. Performance and safety (recommended)

- Time a **full-level scan** on a representative map; note rough duration in internal QA notes.
- Run **Preview** before **Apply** on production-sized content.
- Confirm **exclusions** (folders/tags) work if exposed in UI.

---

## 6. Record results

For each engine line you ship, record build id, date, and pass/fail for Sections **3** and **4** in your release tracker. Optionally mirror the matrix style used by Level Selection Sets in `[../level-selection-sets/docs/ENGINE_TEST_MATRIX.md](../../level-selection-sets/docs/ENGINE_TEST_MATRIX.md)` for consistency.

---

## 7. If something fails

- **Build fails:** Wrong engine vs. package, or missing VS components—see `[INSTALLATION.md](INSTALLATION.md)`.
- **Plugin does not appear:** Verify `Plugins/WorldBuilderAuditConvert/` layout and `.uplugin` at the correct depth.
- **Crash on scan:** Capture **Output Log** and **Crash Reporter** call stack; note mesh count and engine version.

Support: `[SUPPORT.md](SUPPORT.md)`.