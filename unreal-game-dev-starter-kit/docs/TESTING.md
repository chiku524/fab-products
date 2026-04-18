# Testing — Unreal Game Dev Starter Kit

This product is **documentation and templates only**—there is **no Unreal plugin** to compile. “Testing” means **verifying the deliverable is complete**, **readable**, and **usable** the way a buyer would consume it.

---

## 1. Integrity check (every release)

Perform these on the **zipped package** you intend to upload (or the staged folder before zipping).

| Step | Action | Pass |
|------|--------|------|
| 1 | Unzip to a **short path** without spaces if possible (avoids Windows path issues). | Folder extracts with no errors. |
| 2 | Confirm top-level files exist: `DOCUMENTATION.md`, `LICENSE`, `CHANGELOG.md` (per your packaging). | All present. |
| 3 | Open `DOCUMENTATION.md` and click through **every linked** doc in the index table. | No broken relative links; each file opens. |
| 4 | Open [`INSTALLATION.md`](INSTALLATION.md) and follow it literally on a **fresh** machine or folder. | Steps make sense; no missing references. |
| 5 | List `templates/` and spot-check **2–3** templates open in a text editor. | UTF-8 readable; no corruption. |

---

## 2. Content QA (publisher)

| Check | Notes |
|--------|--------|
| **Versioning** | `CHANGELOG.md` entry for this release matches the zip name / version you advertise. |
| **Contact** | `docs/SUPPORT.md` and any email strings match the Fab listing. |
| **Scope** | [`USER_GUIDE.md`](USER_GUIDE.md) chapters align with files you ship (no references to removed sections). |
| **Templates** | Each template has a one-line comment or header saying **where to copy** it (e.g. project root vs. `Config/`). |

---

## 3. Optional: apply-to-project test (recommended once)

This validates that the kit still matches real Unreal workflows.

1. Create or use an existing **Unreal 5.4+** project (C++ or Blueprint).
2. Pick **one** workflow from [`USER_GUIDE.md`](USER_GUIDE.md) (e.g. folder layout or source-control snippet).
3. Apply **one** template or checklist item to a **copy** of the project or a scratch repo.
4. Confirm the project still opens in the editor and your change did not break packaging.

**Pass:** Instructions were sufficient without author knowledge; adjust docs if not.

---

## 4. Optional: link validation

If you maintain many cross-links:

- Search `docs/` for markdown links `](...)` and verify relatives resolve from `DOCUMENTATION.md` and from each subfolder.

---

## 5. What you do *not* need

- **RunUAT**, **Visual Studio**, or **plugin compile** for *this* product alone.
- A Fab-specific runtime test—there is no Fab API in the kit.

---

## 6. Bundle context

When this kit is sold inside the [Immersive Labs UE bundle](../../immersive-labs-ue-bundle/README.md), also run [`../../immersive-labs-ue-bundle/docs/TESTING.md`](../../immersive-labs-ue-bundle/docs/TESTING.md) to validate the **combined** zip set.

Support: [`SUPPORT.md`](SUPPORT.md).
