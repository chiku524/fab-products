# Fab listing copy — Workflow Toolkit (paste-ready)

Use with [PACKAGING_FOR_FAB.md](PACKAGING_FOR_FAB.md) and [MEDIA.md](MEDIA.md) (add screenshots/video when you have them).

## Product identity

| Field | Text |
|------|------|
| **Product title** | Workflow Toolkit |
| **Subtitle / tagline** | One editor panel for level shortcuts, plus a PIE runtime toolkit |
| **Primary category** | Tools & Plugins → Engine Tools (or closest Fab equivalent) |

## Short description

Editor shortcuts grouped by task—selection, meshes, content saving, settings, and validation—plus a **runtime Game Instance** subsystem for PIE: console commands, pause, time dilation, teleport, and camera focus. Full C++ source for editor and runtime modules.

## Long description

**Workflow Toolkit** is an Unreal Engine **code plugin** for **technical artists**, **level designers**, and **indie teams** who want **faster round-trips** in the editor and cleaner **play-in-editor** tests without hunting through menus.

**What you get**

- **Editor panel** — **Window → Level Editor → Workflow Toolkit** groups actions for **viewport & selection**, **meshes & placement**, **saving & assets**, **editor & windows**, and **diagnostics** (e.g. validation). Keyboard shortcuts are assignable in **Editor Preferences** where the engine exposes them for this context.  
- **Runtime (PIE)** — **`WorkflowToolkitRuntime`** on the **Game Instance** exposes helpers for **console**, **pause**, **time dilation**, **teleport**, and **view focus** so you can script quick iteration from Blueprints or C++.  
- **Source** — Full **editor** and **runtime** module source is included, suitable for Fab’s code-plugin rules and team customization.

**Who it’s for**

Studios that want a **practical** layer on top of stock editor workflows—not a new asset pipeline. Complements your existing project structure, source control, and level organization.

**Important**

- **Win64** editor in v1 per `.uplugin` **PlatformAllowList** unless you extend and test other targets.  
- After **C++ or Slate** changes, do a full **rebuild** and often a full **editor restart** before the panel or shortcuts reflect updates.  
- Match the **packaged** plugin to your buyers’ **Unreal Engine minor line** (e.g. 5.7.x package for 5.7.x editors).

## Keywords

Unreal Engine, editor tools, level design, PIE, workflow, productivity, shortcuts, Game Instance, runtime, Slate, level iteration

## Feature bullets (listing)

- Grouped **editor** actions: viewport, meshes, save/browse, settings, validation  
- **Runtime** subsystem for **PIE**: console, pause, time dilation, teleport, view focus  
- **Win64** editor support as shipped  
- **Full C++** source (editor + runtime modules)

## Version / compatibility (listing text)

- **Stated engine range:** 5.4+ (align with the package you build and test, e.g. 5.7).  
- **Platform:** Windows **64-bit** editor for the published build unless you add and verify others.

## Legal / support line (footer)

**Publisher: Immersive Labs** · **Support: nico.builds@outlook.com** (see [SUPPORT.md](SUPPORT.md)).  
See **LICENSE** in the product download. Epic Fab terms apply to purchases.

---

## Fab portal — full listing form (all Fab UI fields)

**Checklist** for the Fab listing editor. Full field notes: **[`../../docs/fab-portal-listing-fields.md`](../../docs/fab-portal-listing-fields.md)**. [MEDIA.md](MEDIA.md) · [art](../../docs/fab-listing-media/workflow-toolkit/).

### Product information

| Field | Notes |
|--------|--------|
| **Title** * | **Product title** in **Product identity** (0 / 80 or current cap). |
| **Description** * | **Short** + **Long description**. |
| **Product type** * | **Tools & Plugins**. |
| **Category** * | **Primary category**; pick closest. |

### License & price

- **License type** * · **UEFN - Reference only price** * · **Personal** * · **Professional** * (USD) — *discount rules per portal (often 30 days live).*

### Tags

- **Tags** * — e.g. 0 / 25; use **Keywords**.

### Thumbnail

- **.jpeg / .jpg / .png** · min e.g. **1920×1080** · max e.g. **3 MB**

### Media gallery

- At least **1** asset; max **24**.

### Forum post / mature content / NoAI / gen-AI / promotional

- **Epic forum post:** **No** *or* **Yes, create a forum post**  
- **Mature content:** **No** *or* **Yes**  
- **Disallow use by Generative AI Programs** — per portal  
- **Was this product created with generative AI?** **No** *or* **Yes** (partly or fully)  
- **Promotional content** — checkbox

### FAQs

- **+** to add.

### Unreal Engine version

| Field | Notes |
|--------|--------|
| **Version title** * | e.g. 0 / 30 chars |
| **Project file link** * | `https://` |
| **Supported engine version** * | e.g. **5.4+** / **5.7** to match the zip |
| **Supported target platforms** * | e.g. **Editor Win64** |
| **Version notes** | Rebuild + restart after Slate changes, etc. |
