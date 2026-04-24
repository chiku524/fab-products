# Fab listing copy — World Builder Templates (paste-ready)

Use with [PACKAGING_FOR_FAB.md](PACKAGING_FOR_FAB.md), [MEDIA.md](MEDIA.md) (add when you have assets), and [SAMPLE_MAPS.md](SAMPLE_MAPS.md).

## Product identity

| Field | Text |
|------|------|
| **Product title** | World Builder Templates |
| **Subtitle / tagline** | Open shipped world maps as a template or a direct level—fast starts for new environments |
| **Primary category** | Tools & Plugins → Engine Tools (or closest Fab equivalent) |

## Short description

Browse **ready-made world maps** that ship in the plugin: open as an **untitled template** (Unreal’s template flow) or **load** the map directly. Great for **greybox**, **biome tests**, and **prototyping** when you do not want to start from an empty level.

## Long description

**World Builder Templates** is an Unreal Engine **editor plugin** for **indies and small teams** who want **credible starting geography** without building every blockout from zero.

**What you get**

- **Template gallery** under **Window → Level Editor → World Builder Templates** — pick from **Outdoor**, **Indoor blockout**, **Ocean**, and **City** style starter maps (see plugin **Content/Maps**).  
- **Open as template** — starts from an **untitled** copy so your project’s canonical levels stay clean.  
- **Open** — load the map asset in place for quick iteration.  
- **Config** — **Project Settings → Plugins → World Builder Templates** can add **Extra package path roots** (defaults include **Engine** template maps) so the list can include project-specific worlds.

**Who it’s for**

Environment artists and designers who need a **faster first hour** in a new project or a **visual anchor** for art direction. Not a full game template: it is a **level and layout** head start.

**Important**

- **UE 5.7+** for the build in this repo unless you retarget the `.uplugin` and re-test.  
- **CanContainContent** is **true**; the Fab zip **must** include the plugin **Content** folder (see [PACKAGING_FOR_FAB.md](PACKAGING_FOR_FAB.md)).  
- **Win64** editor in v1 per `.uplugin` unless you expand platforms.

## Keywords

Unreal Engine, world, template, level design, blockout, greybox, environment, maps, editor plugin, Fab, productivity

## Feature bullets

- Dockable **World Builder Templates** window with shippable sample maps  
- **Template** vs **open** behavior for the same assets  
- **Settings** to extend the browser with more package roots  
- **Full source** for the editor module  

## Version / compatibility

- Match **package build** to your stated **Unreal** minor line on the listing.  
- See **Support** in [SUPPORT.md](SUPPORT.md) and `SupportURL` in `WorldBuilderTemplates.uplugin`.

## Legal / footer

**Publisher: Immersive Labs** — **Support: nico.builds@outlook.com**  
License: [LICENSE](../LICENSE) at product root. Epic Fab terms apply to purchases.

---

## Fab portal — full listing form (all Fab UI fields)

**Checklist** for the Fab listing editor. Long reference: **[`../../docs/fab-portal-listing-fields.md`](../../docs/fab-portal-listing-fields.md)**. Thumbnails: [fab-listing-media](../../docs/fab-listing-media/worldbuilder-templates/), [MEDIA.md](MEDIA.md).

### Product information

| Field | Notes |
|--------|--------|
| **Title** * | **Product title** in **Product identity** (e.g. 0 / 80). |
| **Description** * | **Short** + **Long description** as required by portal. |
| **Product type** * | **Tools & Plugins** (or portal equivalent). |
| **Category** * | **Primary category**; pick closest. |

### License type & price

| Field | Notes |
|--------|--------|
| **License type** * | **Standard (Free or Paid)** or **CC BY 4.0 (Free)**. |
| **UEFN - Reference only price** * | If shown. |
| **Personal price** * / **Professional price** * | USD. |

*Discounts: often after **30 days** live (portal).*

### Tags

- **Tags** * — from **Keywords**; cap in portal (e.g. 0 / 25).

### Thumbnail / media

- **Thumbnail:** `.jpeg` / `.jpg` / `.png`, min e.g. **1920×1080**, max e.g. **3 MB**.  
- **Media gallery:** ≥ **1** file, max **24**.

### Forum post

- **No** *or* **Yes, create a forum post**.

### Mature content

- **No** *or* **Yes**.

### Generative AI — disallow use (NoAI)

- Per portal options.

### Generative AI — was this product created with AI?

- **No** *or* **Yes** (partly or fully).

### Promotional content

- **Includes promotional content** (checkbox) if required.

### FAQs

- **+** to add.

### Unreal Engine version

| Field | Notes |
|--------|--------|
| **Version title** * | e.g. 0 / 30. |
| **Project file link** * | `https://` to downloadable. |
| **Supported engine version** * | e.g. **5.7+** per this repo. |
| **Supported target platforms** * | e.g. **Editor Win64** (v1). |
| **Version notes** | Compatibility, **SAMPLE_MAPS** link. |
