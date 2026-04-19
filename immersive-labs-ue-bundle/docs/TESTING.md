# Testing — Immersive Labs UE Development Bundle

The bundle **assembles** multiple products; it does not replace their individual QA. Use this document to verify **staging**, **archives**, and **buyer experience** before linking downloadables on Fab.

---

## 1. What you are validating


| Goal                | Description                                                                                                                        |
| ------------------- | ---------------------------------------------------------------------------------------------------------------------------------- |
| **Correct zips**    | Each Fab downloadable extracts to the expected layout and is exercised with that component’s `**docs/TESTING.md`** (see §5 below). |
| **Engine labeling** | Folder names / zip names match the **engine minor line** you support (e.g. `UE5-7` staging ↔ 5.7.x editor).                        |
| **Completeness**    | All advertised components are present per `[PUBLISHER_ASSEMBLY.md](PUBLISHER_ASSEMBLY.md)`.                                        |


---

## 2. Prerequisites

- Built `**dist/`** outputs (or equivalent) for each **plugin** for the engine line you are staging—see each product’s `docs/PACKAGING_FOR_FAB.md` and `scripts/package-plugin.ps1`.
- **PowerShell** on Windows to run `[../scripts/stage-bundle.ps1](../scripts/stage-bundle.ps1)`.
- Enough disk space for duplicate zips (staging is under `staging/`; see bundle `[.gitignore](../.gitignore)`).

---

## 3. Stage the bundle (automated check)

1. From the repo root (or as documented in `[../scripts/README.md](../scripts/README.md)`), run:
  - `immersive-labs-ue-bundle/scripts/stage-bundle.ps1`
  - With `**-UeVersionLabel`** matching your packages (e.g. `5.7` if folders are `*-UE5.7-Win64`).
2. Confirm the script completes without errors and prints the **staging directory** (e.g. `immersive-labs-ue-bundle/staging/UE5-7/`).

**Pass:** Three archives exist (or two if starter kit path missing by design):

- `LevelSelectionSets-UE<ver>-Win64.zip`
- `WorldBuilderAuditConvert-UE<ver>-Win64.zip`
- `UnrealGameDevStarterKit-docs.zip`

---

## 4. Manual archive verification

For **each** zip:


| Step | Action                                                                                                        | Pass                                                             |
| ---- | ------------------------------------------------------------------------------------------------------------- | ---------------------------------------------------------------- |
| 1    | Copy zip to a **clean temp folder**; extract.                                                                 | Extract succeeds.                                                |
| 2    | **Plugin zips:** Root contains the plugin folder with `.uplugin` and `Source/` (and `Binaries/` if prebuilt). | Matches `[../docs/BUYER_GUIDE.md](BUYER_GUIDE.md)` expectations. |
| 3    | **Starter kit zip:** `DOCUMENTATION.md` at root or as documented; `templates/` if shipped.                    | Matches listing.                                                 |
| 4    | **Size sanity:** Absurdly small zips (< tens of KB) for plugins usually mean wrong folder was zipped.         | Sizes plausible vs. local `dist/` builds.                        |


---

## 5. Per-component deep test (recommended)


| Component                    | Run                                                                                                                                                                  |
| ---------------------------- | -------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| Level Selection Sets         | `[../../level-selection-sets/docs/TESTING.md](../../level-selection-sets/docs/TESTING.md)` using the **extracted** plugin from the **staged** zip (simulates buyer). |
| WorldBuilder Audit & Convert | `[../../worldbuilder-audit-convert/docs/TESTING.md](../../worldbuilder-audit-convert/docs/TESTING.md)` on extracted plugin.                                          |
| Unreal Game Dev Starter Kit  | `[../../unreal-game-dev-starter-kit/docs/TESTING.md](../../unreal-game-dev-starter-kit/docs/TESTING.md)` on extracted docs zip.                                      |


**Pass:** Each component passes its own criteria when installed from the **bundle-produced** archive, not only from a dev tree.

---

## 6. Fab listing cross-check

- Open `[FAB_LISTING_COPY.md](FAB_LISTING_COPY.md)` and confirm **downloadable count**, **engine version text**, and **file names** match what you uploaded.
- Walk `[SUBMISSION_CHECKLIST.md](SUBMISSION_CHECKLIST.md)` once per release.

---

## 7. If staging fails

- **“Skip (not found)”** for a plugin: `dist/` missing for that engine label—run `package-plugin.ps1` with matching `**-UeVersionLabel`** and `**-EngineRoot`**, or use a short output path on Windows if builds hit **MAX_PATH** (see `[../../level-selection-sets/docs/PACKAGING_FOR_FAB.md](../../level-selection-sets/docs/PACKAGING_FOR_FAB.md)`).
- **Starter kit missing:** Verify path to `unreal-game-dev-starter-kit` from repo root matches `[../scripts/stage-bundle.ps1](../scripts/stage-bundle.ps1)`.

Support contact for published products: see each product’s `docs/SUPPORT.md`.