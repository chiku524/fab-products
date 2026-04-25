# Harbor Suite — Fab listing notes

**Publisher:** Immersive Labs  
**Product type:** Unreal Engine **code plugin** + **sample C++ project**  
**Primary buyer:** Solo indie / small team (1–5 people) shipping on Unreal.

---

## Positioning (one paragraph)

Harbor Suite is a **small-team control room inside Unreal**—four pillars that reduce tab-hunting and shipping anxiety: **Charts** (guided passes with saved progress), **Stowage** (Outliner hygiene), **Shakedown** (faster PIE iteration), and **Clearance** (lightweight level signals for triage). It is **not** a gameplay template; it is **editor workflow** with an optional runtime helper subsystem.

---

## Feature bullets (short)

- **Charts:** Vertical Slice Gate checklist; save progress per project; one-click **save dirty packages**.
- **Stowage:** Prefix actor labels on the current selection with undo-friendly transactions.
- **Shakedown:** While **PIE** is running—reset to first **PlayerStart**, set global time dilation presets.
- **Clearance:** Summarize actor / mesh / point-light counts in the editor level; select actors whose labels contain **Problem** (demo-friendly triage).
- **Runtime:** `UHarborSuiteRuntimeSubsystem` exposes the same reset / dilation / pause / camera helpers for Blueprints.

---

## Technical facts

- **Engine:** 5.7+ for the primary artifact in this repo (verify against your packaged build; ship separate zips per minor line if you support more).
- **Host platform (editor module):** **Win64** (`PlatformAllowList` in `.uplugin`).
- **Network:** None. **Online services:** None.
- **Project code:** Sample project `Harbor` is **C++** (minimal game module).

---

## Deliverables

1. **Plugin zip** — `RunUAT BuildPlugin` output (see [PACKAGING_FOR_FAB.md](PACKAGING_FOR_FAB.md)).
2. **Sample project zip** — `Harbor` without `Binaries/`, `Intermediate/`, `Saved/`, `DerivedDataCache/`; include README pointer to plugin install location if you omit `Plugins/HarborSuite` from the zip.

---

## What to say “no” to (reduces bad reviews)

- Not a full game framework, multiplayer stack, or production-ready CI validator.
- **Clearance** is a **signal** scan, not a certified performance or compliance audit.
- **Shakedown** editor actions operate on the **PIE** world; they are inert when not playing in editor.

---

## Support blurb (short)

Support contact: see `docs/SUPPORT.md` and the Fab listing **Support** field (email).

---

## Fab portal — full listing form (all Fab UI fields)

Use this as a **checklist** when filling the [Fab](https://www.fab.com/) **create / edit listing** form. For expanded notes and legal details, see **[`../../docs/fab-portal-listing-fields.md`](../../docs/fab-portal-listing-fields.md)**.

### Product information


| Field              | Notes                                                                                                                                |
| ------------------ | ------------------------------------------------------------------------------------------------------------------------------------ |
| **Title** *        | Shown in search; use **Harbor Suite** (or the exact name you will ship). Character cap in portal (e.g. 0 / 80).                      |
| **Description** *  | Paste from **Positioning** + **Feature bullets** + **Deliverables** above, or a trimmed **Long description** you maintain elsewhere. |
| **Product type** * | e.g. **Tools & Plugins**.                                                                                                            |
| **Category** *     | e.g. **Engine Tools** (choose closest in portal).                                                                                    |


### License type & price


| Field                             | Notes                                                             |
| --------------------------------- | ----------------------------------------------------------------- |
| **License type** *                | e.g. **Standard License (Free or Paid)** or **CC BY 4.0 (Free)**. |
| **UEFN - Reference only price** * | If shown, set or reset per portal.                                |
| **Personal price** *              | USD.                                                              |
| **Professional price** *          | USD.                                                              |


*Discounts may only apply after the listing has been live **30 days** (confirm in portal).*

### Tags


| Field      | Notes                                              |
| ---------- | -------------------------------------------------- |
| **Tags** * | Discoverability tags; cap in portal (e.g. 0 / 25). |


### Thumbnail image


| Constraint     | Portal guidance         |
| -------------- | ----------------------- |
| Formats        | `.jpeg`, `.jpg`, `.png` |
| Min resolution | e.g. **1920×1080**      |
| Max size       | e.g. **3 MB**           |


### Media gallery

- At least **1** image or 3D asset where the portal requires it. **Maximum 24** files. See [MEDIA](MEDIA.md) and [fab-listing-media](../../docs/fab-listing-media/harbor-suite/) in the monorepo.

### Epic Developer Community forum post

- **No, do not create a forum post** *or* **Yes, create a forum post** (per portal; links Epic + Fab + EDC as required).

### Mature content

- **No, this listing does not contain mature content** *or* **Yes, this listing contains mature content** (see portal guidelines).

### Disallow use by Generative AI Programs

- Choose whether the listing should disallow use by generative AI programs (portal **NoAI**-style options).

### Use of generative artificial intelligence (AI) tools

- **No, it was not partly or fully created with generative AI** *or* **Yes, it was partly or fully created with generative AI** (per portal definitions).

### Promotional content

- **Includes promotional content** (checkbox) if the listing includes placement, logos, slogans, or other promotional material as defined in the portal.

### FAQs

- Add Q&A with **+** in the **FAQs** section.

### Unreal Engine version (one block per line you support)


| Field                            | Notes                                                                    |
| -------------------------------- | ------------------------------------------------------------------------ |
| **Version title** *              | Short line; cap in portal (e.g. 0 / 30).                                 |
| **Project file link** *          | `https://` to the project file or marketplace download.                  |
| **Supported engine version** *   | e.g. **5.7** to match the packaged build.                                |
| **Supported target platforms** * | e.g. **Editor Win64** (as in **Technical facts**).                       |
| **Version notes**                | Build ID, `CHANGELOG`, or “use the zip for the exact engine minor line.” |
