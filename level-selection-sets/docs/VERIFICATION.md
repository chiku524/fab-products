# Verification (publisher QA)

Repeat this checklist **once per packaged plugin build** (each engine minor line you support), using a **clean** C++ or Blank project and the **packaged** plugin from `RunUAT` (not only your dev copy), unless you are debugging source.

## Setup

1. Create or use a **test project** for that exact engine version (e.g. 5.4.x project for a 5.4.x package).  
2. Copy the **packaged** `LevelSelectionSets` folder into `YourProject/Plugins/LevelSelectionSets/`.  
3. Generate project files and **build Development Editor**.  
4. Open the editor, enable **Level Selection Sets** under **Edit → Plugins**, restart if prompted.

## Functional checks

| Step | Action | Pass |
|------|--------|------|
| 1 | **Window → Level Editor → Level Selection Sets** opens without errors | ☐ |
| 2 | Place or select several actors; enter a set name; **Save** | ☐ |
| 3 | Clear selection; **Recall**; selection matches saved actors | ☐ |
| 4 | **Rename** a set (Apply / Cancel) | ☐ |
| 5 | **Delete** a set | ☐ |
| 6 | **File → Save Current** (or save level); close editor; reopen project; open same level; confirm sets persist | ☐ |
| 7 | Optional: **Undo** after save/delete/rename if you rely on transaction history | ☐ |

## Output log

- Open **Window → Developer Tools → Output Log** during the session.  
- There should be **no red errors** attributable to `LevelSelectionSetsEditor` on load or when using the panel.

## Record results

Enter a row in [`ENGINE_TEST_MATRIX.md`](ENGINE_TEST_MATRIX.md) for this engine build and attach the package name you will upload to Fab.
