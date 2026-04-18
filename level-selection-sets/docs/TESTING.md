# Testing — Level Selection Sets

This guide is for **publishers** and **QA** validating the plugin before (or after) a Fab release. For a short checklist, see [VERIFICATION.md](VERIFICATION.md). For Unreal basics (C++ project, Plugins folder, first build), see [unreal-plugin-testing-beginner.md](../../docs/unreal-plugin-testing-beginner.md).

### Where is the “plugin”? (naming)

- There is **no** folder named `plugin`. Unreal’s convention is:
  - Your **game project** has a folder called `**Plugins`** (plural, capital P is common).
  - Inside that, each product is its **own subfolder** — for this product that folder is named `**LevelSelectionSets`** (not “LevelSelectionSetsPlugin”).
- **In this monorepo**, that folder is here (relative to repo root):
`level-selection-sets/LevelSelectionSets/`
You should see at least `**LevelSelectionSets.uplugin`** and a `**Source/`** directory. That entire `**LevelSelectionSets**` directory is what you copy into a test project.
- **In the Unreal Editor**, you do not browse the disk for “plugin”. Enable it under **Edit → Plugins**, then search for **Level Selection Sets**. The **Window → Level Editor → Level Selection Sets** entry is the tool UI after it is enabled.

---

## 1. What “passing” means


| Layer        | Goal                                                                                                    |
| ------------ | ------------------------------------------------------------------------------------------------------- |
| **Compile**  | The plugin module builds for **Development Editor** with no errors.                                     |
| **Load**     | Editor opens with the plugin enabled; **Output Log** has no red errors from `LevelSelectionSetsEditor`. |
| **Function** | Nomad tab works: save, recall, rename, delete; data survives **level save** and **editor restart**.     |


Always test the **same engine minor line** as the package (e.g. a **5.7.x** editor for `LevelSelectionSets-UE5.7-Win64`). Do not mix 5.4 plugin with 5.7 editor.

---

## 2. Prerequisites

- **Unreal Editor** matching your downloadable (e.g. 5.7.x).
- **Windows 64-bit** editor (v1 target).
- **Visual Studio 2022** with C++ game development workload (or Build Tools that successfully compile editor targets).
- **Test artifact:** Prefer the **RunUAT-packaged** folder or zip you will ship—not only a raw git checkout—unless you are debugging source.

---

## 3. Prepare a test project

1. **Create** a new project from a template (e.g. **Third Person**) as **C++**, not Blueprint-only.
2. **Close** the editor.
3. Under the **game project** folder (next to `YourProject.uproject`), create **`Plugins`** if it does not exist. Copy the entire **`LevelSelectionSets`** folder from this repo (`level-selection-sets/LevelSelectionSets/`) so that you have:
   - `YourProject/Plugins/LevelSelectionSets/LevelSelectionSets.uplugin`
   - `YourProject/Plugins/LevelSelectionSets/Source/`
4. **Regenerate Visual Studio project files:** in **Windows File Explorer**, go to the real folder on disk that contains **`YourProject.uproject`**, then **right‑click the `.uproject` file** → **Generate Visual Studio project files**. (Cursor/VS Code’s sidebar usually does **not** show this; use Explorer or see [INSTALLATION.md](INSTALLATION.md) step 4 for **Windows 11** and **command-line** alternatives.)
5. Open **`YourProject.sln`**, set configuration to **Development Editor**, **Build** the solution.
6. **Launch** the editor (from VS or by opening the `.uproject`).
7. **Edit → Plugins** → search **Level Selection Sets** → **Enable** → **Restart** if prompted.

**Pass:** Project builds; editor starts; plugin shows enabled after restart.

---

## 4. Output Log baseline

1. **Window → Developer Tools → Output Log**.
2. Clear or note the end of the log; load your default map.

**Pass:** No **Error** lines attributing failures to **LevelSelectionSets** or **LevelSelectionSetsEditor** during load.

---

## 5. Functional tests (detailed)

Perform these in order on an open **level** with placeable actors (empty level is fine if you add meshes/lights/actors).

### 5.1 Open the tool

1. **Window → Level Editor → Level Selection Sets** (nomad tab).

**Pass:** Tab opens with no message box errors; UI shows help text, name field, and **Save**.

### 5.2 Save a selection set

1. In the level, **select two or more** actors (Shift+click in viewport or Outliner).
2. In the panel, type a unique name (e.g. `TestSet_A`).
3. Click **Save**.

**Pass:** The set appears in the list (or list refreshes) without errors.

### 5.3 Recall

1. **Deselect all** (Escape or click empty space).
2. In the panel, use **Recall** for `TestSet_A`.

**Pass:** The same actors become selected; count matches what you saved.

### 5.4 Rename

1. Use **Rename** for `TestSet_A` → `TestSet_B` (use **Apply** as your UI provides).

**Pass:** List shows `TestSet_B`; old name gone; recall still works for the new name.

### 5.5 Delete

1. **Delete** `TestSet_B`.

**Pass:** Set disappears from the list; recall is no longer offered for it.

### 5.6 Persistence (critical for Fab QA)

1. Create a **new** set again (e.g. `PersistTest`) with at least one actor saved.
2. **File → Save Current** (or save the level) so the map asset is written.
3. **Close** the editor completely.
4. Reopen the **same project** and **same level**.
5. Open **Level Selection Sets** and confirm `**PersistTest`** is still listed; **Recall** works.

**Pass:** Sets survive restart. **Fail:** If sets vanish, check that the level was saved and that the data actor was not in a transient-only session.

### 5.7 Second level (isolation)

1. **File → New Level** (or add a second map) and save it as e.g. `L_TestSecond`.
2. Open **Level Selection Sets**; confirm sets from the **first** level do not incorrectly appear, or behavior matches design (data is per persistent level).

**Pass:** No cross-level corruption; expectations match [USER_GUIDE.md](USER_GUIDE.md).

### 5.8 Undo (optional)

1. After a **Save** or **Delete**, try **Edit → Undo** if you rely on transactions.

**Pass:** Matches your supported behavior; no crash.

---

## 6. Regression and edge cases (optional)

- **Empty selection:** Save with nothing selected — behavior should be safe (no crash); note whether you allow or block empty sets per product intent.
- **Deleted actors:** Save a set, delete an actor from the level, then **Recall** — should not crash; selection may skip missing actors (confirm intended behavior).
- **PIE:** Start **Play In Editor** once; stop. Editor-only plugin should not require PIE, but a quick PIE cycle catches accidental runtime dependencies.

---

## 7. Record results

- Fill a row in [ENGINE_TEST_MATRIX.md](ENGINE_TEST_MATRIX.md) for this engine build.
- Keep the short checklist in [VERIFICATION.md](VERIFICATION.md) for repeat runs before each upload.

---

## 8. If something fails

- **Compile errors:** Engine version mismatch vs. `.uplugin`, or incomplete VS workload—see [INSTALLATION.md](INSTALLATION.md) and [FAQ.md](FAQ.md).
- **Plugin missing in list:** Wrong `Plugins/` layout or missing `.uplugin`.
- **Crash on enable:** Binary built with a different engine hotfix than the editor—rebuild with **RunUAT** for that exact line.

Support: [SUPPORT.md](SUPPORT.md).