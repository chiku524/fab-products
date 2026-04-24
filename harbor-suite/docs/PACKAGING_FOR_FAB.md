# Harbor Suite — packaging for Fab

## Plugin package (RunUAT)

From a machine with the **target engine** installed (example **UE 5.7**):

```powershell
cd path\to\fab-products\harbor-suite\scripts
.\package-plugin.ps1 -EngineRoot "C:\Program Files\Epic Games\UE_5.7" -UeVersionLabel "5.7"
```

Output defaults to **`harbor-suite/dist/`** as a folder named like **`HarborSuite-UE5.7-Win64`**.

Zip that folder for Fab’s plugin upload.

### Preconditions

- `RunUAT.bat` exists under `Engine\Build\BatchFiles\`.
- Plugin descriptor path matches the script (see `scripts/package-plugin.ps1`).

---

## Sample project zip

1. Clean artifacts from **`Harbor/`**:
   - Delete `Binaries/`, `Intermediate/`, `Saved/`, `DerivedDataCache/`, `.vs/` if present.
2. Decide whether the zip **includes** `Plugins/HarborSuite` (easiest for buyers) or expects them to copy the Fab plugin into `Plugins/` (smaller zip, more friction).
3. Add a short **`Harbor/README.md`** in the zip if not already present: engine version, how to build, link to Fab page.

---

## Engine version matrix

Ship **one Fab item per engine minor line** you truly test (for example 5.7 and 5.8 as separate builds). Update `EngineVersion` in `HarborSuite.uplugin` and your listing text together.

---

## QA after packaging

Run [VERIFICATION.md](VERIFICATION.md) against the **packaged** plugin dropped into a clean Third Person C++ project, not only against the monorepo path.
