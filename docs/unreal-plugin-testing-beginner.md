# Testing Fab code plugins in Unreal (beginner-friendly)

You do **not** need to know C++ to **smoke-test** these plugins. You do need the **Unreal Editor** and (for **source** plugins) **Visual Studio** so the plugin can compile once into your test project.

There is **no special “Fab API”** inside Unreal. Testing is: create a small project → add the plugin → build → open the editor → confirm things work.

---

## 1. Install the tools (one time)

| What | Why |
|------|-----|
| **Epic Games Launcher** | Install Unreal Engine **5.4 or newer** (match the **same minor** line you built the plugin for, e.g. 5.4.x). |
| **Visual Studio 2022** (Windows) with **“Game development with C++”** workload | Compiles the plugin’s C++ into your project. |
| This repo’s plugin folder | e.g. `level-selection-sets/LevelSelectionSets/` or `worldbuilder-audit-convert/WorldBuilderAuditConvert/`. |

Use the engine version that matches your **packaged plugin** or the source you’re building from. Mixing 5.4 plugin with 5.5 editor usually fails.

---

## 2. Create a tiny **C++** test project

**Why C++?** These products ship **source**. The editor must **compile** that source into your project. A **Blueprint-only** project has no C++ toolchain until you add it.

1. Open **Epic Games Launcher** → **Unreal Engine** → **Launch** your version (e.g. 5.4).  
2. **Games** → pick a template, e.g. **Third Person**.  
3. Choose **C++** (not Blueprint only).  
4. Pick a folder and project name, e.g. `FabPluginSmokeTest`.  
5. Create project and let the editor generate **Visual Studio** files when asked.

You now have `FabPluginSmokeTest.uproject` and a `Source/` folder.

---

## 3. Add the plugin to the project

1. Close the Unreal Editor.  
2. In File Explorer, under your project folder, create **`Plugins`** if it doesn’t exist:  
   `FabPluginSmokeTest/Plugins/`  
3. Copy the **whole plugin folder** (the one that contains the `.uplugin` file) into `Plugins/`, for example:  
   - `FabPluginSmokeTest/Plugins/LevelSelectionSets/`  
   - and inside it: `LevelSelectionSets.uplugin`, `Source/`, etc.

**Rule:** The folder next to `.uproject` should be `Plugins/<PluginFolderName>/`.

---

## 4. Generate project files and build (Windows)

1. Right‑click **`FabPluginSmokeTest.uproject`** → **Generate Visual Studio project files**.  
2. Open **`FabPluginSmokeTest.sln`** in Visual Studio.  
3. In the configuration dropdown, choose **Development Editor** and your game as startup project if needed.  
4. **Build** → **Build Solution** (or F7).  
5. Wait until it finishes with **no errors**.

If build fails, open **Output** in Visual Studio and read the first error (often wrong engine version or missing VS workload).

---

## 5. Run the editor and enable the plugin

1. Launch the editor (from Visual Studio **Debug → Start Debugging**, or double‑click the `.uproject`).  
2. **Edit → Plugins**.  
3. Search for the product name (e.g. **Level Selection Sets**).  
4. Enable it → **Restart** when prompted.

---

## 6. Check success (everyone can do this)

1. Open **Window → Developer Tools → Output Log**.  
2. Clear or scroll to the bottom.  
3. **Success baseline:** no **red Error** lines mentioning the plugin module name when the level loads.

If the editor opens and the plugin shows as enabled, you’ve passed the **hardest** part.

---

## 7. Minimal functional checks (product-specific)

### Level Selection Sets

1. Open or create any **level**.  
2. Place or select a few actors.  
3. **Window → Level Editor → Level Selection Sets** (nomad tab).  
4. Type a name → **Save** → clear selection → **Recall**.  

Full publisher QA: [`level-selection-sets/docs/TESTING.md`](../level-selection-sets/docs/TESTING.md) (short checklist: [`VERIFICATION.md`](../level-selection-sets/docs/VERIFICATION.md)).

### WorldBuilder Audit & Convert

1. Confirm the plugin **loads** (Output Log clean, plugin enabled).  
2. When the product’s editor UI is fully implemented, follow [`worldbuilder-audit-convert/docs/USER_GUIDE.md`](../worldbuilder-audit-convert/docs/USER_GUIDE.md) for scans and previews.

Step-by-step tests: [`worldbuilder-audit-convert/docs/TESTING.md`](../worldbuilder-audit-convert/docs/TESTING.md).

### Unreal Game Dev Starter Kit

**No Unreal install required.** Unzip the product and open `DOCUMENTATION.md`. Integrity and apply tests: [`unreal-game-dev-starter-kit/docs/TESTING.md`](../unreal-game-dev-starter-kit/docs/TESTING.md). Installation walkthrough: [`unreal-game-dev-starter-kit/docs/INSTALLATION.md`](../unreal-game-dev-starter-kit/docs/INSTALLATION.md).

### Bundle (all products)

If you ship the combined bundle, see [`immersive-labs-ue-bundle/docs/TESTING.md`](../immersive-labs-ue-bundle/docs/TESTING.md).

---

## 8. Packaging builds (publishers / CI)

To produce a **prebuilt** plugin zip for buyers, use Epic’s **`RunUAT BuildPlugin`** (see each product’s `docs/PACKAGING_FOR_FAB.md` and `scripts/package-plugin.ps1`). That’s **build automation**, not something you run inside the game.

---

## 9. Common problems

| Symptom | Likely cause |
|---------|----------------|
| Build errors about missing modules | Wrong engine version vs. plugin, or VS workload incomplete. |
| Plugin missing in Plugins list | Folder not under `YourProject/Plugins/`, or `.uplugin` path wrong. |
| Editor crashes on enable | Get **Callstack** / log; often binary mismatch between engine builds. |
| “Nothing in the menu yet” | Feature still on roadmap; still validate **load + no errors**. |

---

## 10. What counts as “good enough” for a smoke test

| Goal | Pass criteria |
|------|----------------|
| **Buyer experience** | Clean project + plugin enables + no load errors + one documented workflow works. |
| **Fab submission** | Repeat on a **second PC** or VM if you can—catches “works on my machine.” |

You can test everything important **without** writing C++; building the project is clicking **Build** in Visual Studio after the one-time setup above.
