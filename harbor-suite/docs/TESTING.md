# Harbor Suite — testing

This guide is for **publishers** and **QA** validating the plugin and sample project before a Fab release. For a short checklist, see [VERIFICATION.md](VERIFICATION.md).

### Where is the plugin?

- Unreal expects: **`YourProject/Plugins/HarborSuite/`** with `HarborSuite.uplugin` and `Source/`.
- In this monorepo, that folder lives at: **`harbor-suite/Harbor/Plugins/HarborSuite/`** (embedded in the sample project).
- In the editor: **Edit → Plugins** → search **Harbor Suite**. UI: **Window → Level Editor → Harbor Suite**.

---

## 1. What “passing” means

| Layer | Goal |
|-------|------|
| **Compile** | `HarborEditor` (**Development Editor**) builds with no errors. |
| **Load** | Editor opens with the plugin enabled; **Output Log** has no red errors from `HarborSuiteEditor` / `HarborSuiteRuntime`. |
| **Function** | All four pillars behave as described in section 5. |

Test the **same engine minor line** you ship against (for example **5.7.x** for this repo’s default association).

---

## 2. Prerequisites

- **Unreal Editor** (5.7+ for the checked-in `EngineAssociation`; older lines require separate packaging and QA).
- **Windows 64-bit** editor (v1 `PlatformAllowList` on the editor module).
- **Visual Studio 2022** with C++ game development workload.
- Prefer testing a **RunUAT-packaged** plugin folder when validating Fab deliverables (see [PACKAGING_FOR_FAB.md](PACKAGING_FOR_FAB.md)).

---

## 3. Prepare the demo project

1. Open **`harbor-suite/Harbor/Harbor.uproject`** (or copy the project elsewhere first).
2. If modules are out of date, **right-click → Generate Visual Studio project files** or run:
   ```powershell
   cd path\to\fab-products\harbor-suite\scripts
   .\generate-ue-project-files.ps1 -UProjectPath "C:\full\path\to\Harbor\Harbor.uproject"
   ```
3. Build **HarborEditor** from Visual Studio.
4. Launch the editor; enable **Harbor Suite** under **Edit → Plugins** if needed; restart when prompted.

**Pass:** Project builds; editor starts; plugin enabled.

---

## 4. Output Log baseline

1. **Window → Developer Tools → Output Log**.
2. Load a simple level (or the default engine entry map).

**Pass:** No **Error** lines attributing failures to **HarborSuite** during load.

---

## 5. Functional tests

### 5.1 Open the tool

1. **Window → Level Editor → Harbor Suite**.

**Pass:** Nomad tab opens; intro text and four pillar buttons are visible.

### 5.2 Charts — persistence

1. Open **Charts**.
2. Toggle several checklist checkboxes.
3. Close the editor; reopen the same project.

**Pass:** Checkmarks match the previous session. File exists under `Saved/HarborSuite/ChartsState.json`.

### 5.3 Charts — save dirty

1. Make a trivial edit (move an actor) so the map is dirty.
2. Click **Save all dirty packages**.

**Pass:** No crash; map dirty flag clears (typical case). If nothing was dirty, behavior is still valid (no error).

### 5.4 Charts — reset runbook

1. Click **Reset runbook**.

**Pass:** All checkboxes clear; JSON on disk updates.

### 5.5 Stowage — prefix

1. Select two or more actors.
2. Set prefix to `Test_` (or keep default).
3. Click **Apply prefix to selection**.

**Pass:** Labels gain the prefix once (re-running does not double-prefix the same string). **Ctrl+Z** undoes.

### 5.6 Shakedown — PIE

1. Ensure the level has at least one **Player Start**.
2. Start **PIE**.
3. Move the player away from the Player Start.
4. Click **Move player to first PlayerStart**.

**Pass:** Player returns to the first `PlayerStart` found in the PIE world.
5. Click **Time dilation 0.5x** then **1.0x**.

**Pass:** Obvious speed change while PIE is running.

### 5.8 Clearance — scan and select

1. Stop PIE; return to editor mode.
2. Rename one actor label to include **`Problem`** (case-insensitive substring).
3. Open **Clearance** → **Run scan**.

**Pass:** Summary counts look plausible; “Problem” row increments.
4. Click **Select labels containing "Problem"**.

**Pass:** Those actors become selected.

---

## 6. Runtime subsystem (optional)

`UHarborSuiteRuntimeSubsystem` is a **Game Instance** subsystem for Blueprint or game-code use.

**Pass (optional):** In PIE, from Blueprint, call **Reset Player To First Player Start** and observe the same behavior as the editor panel.

---

## 7. Known limitations (document for buyers)

- **Shakedown** actions require an active **PIE** world (except subsystem calls from game code).
- **Clearance** scans the **editor** world, not a PIE world.
- **Stowage** edits **actor labels**, not source asset names.
- Editor module is **Win64**-listed in the plugin descriptor; other host platforms require Build.cs / uplugin updates.

---

## 8. After C++ changes

Perform a **full editor restart** after rebuilding the plugin; do not rely on hot reload for Slate panel refreshes.

---

## 9. UE 5.7 project settings (this repo)

- **`Harbor.Target.cs`** / **`HarborEditor.Target.cs`** use **`DefaultBuildSettings = BuildSettingsVersion.V6`** and **`IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_7`** so the editor target matches Unreal 5.7’s shared build environment.
- Plugin code uses **`#include "EditorSubsystem.h"`** (with the **EditorSubsystem** module), **`#include "FileHelpers.h"`** for `UEditorLoadingAndSavingUtils::SaveDirtyPackages`, **`FPlatformFileManager::Get().GetPlatformFile()`** for directory creation, and **`IPluginManager::FindPlugin(TEXT("HarborSuite"))`** for the icon style (5.7 `FindPlugin` overloads). If you backport to an older engine, revisit these APIs.
