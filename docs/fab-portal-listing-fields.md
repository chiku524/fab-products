# Fab listing editor — all fields (reference)

Use this with each product’s **`docs/FAB_LISTING.md`** or **`docs/FAB_LISTING_COPY.md`**. The Fab portal UI, labels, and limits can change; **verify** required markers (*), character caps, and image rules in the **live** [Fab](https://www.fab.com/) publisher workflow before you submit.

---

## 1. Product information

| Field | Notes |
|--------|--------|
| **Title** * | Shown in search and on the product page. Character limit (e.g. **80**) shown in the portal. |
| **Description** * | Long listing body. Often the same as your **Long description** in the product’s `FAB_LISTING*.md` (trim or split if the portal enforces a cap). |
| **Product type** * | e.g. **Tools & Plugins**; documentation-only products use the type the portal offers (e.g. learning/documentation—pick the closest). |
| **Category** * | Sub-category under the product type; choose the best fit. |

---

## 2. License type & price

| Field | Notes |
|--------|--------|
| **License type** * | e.g. **Standard License (Free or Paid)**, or **Creative Commons Attribution (CC BY 4.0) (Free)** when applicable. Open **View license details** in the portal for the legal text. |
| **UEFN - Reference only price** * | If the portal shows this control for your product, set the reference tier or use **Reset price** as allowed. |
| **Personal price** * | **USD** (or currency shown). |
| **Professional price** * | **USD** (or currency shown). |

*Discounts:* The portal may only allow a discount after the listing has been **live 30 days** (per Fab rules—confirm in the UI).

---

## 3. Tags

| Field | Notes |
|--------|--------|
| **Tags** * | Search/choose tags that describe the product. Counter (e.g. **0 / 25**) may appear in the portal. |

---

## 4. Thumbnail image

| Constraint | Notes |
|-------------|--------|
| **Formats** | **.jpeg**, **.jpg**, **.png** |
| **Minimum resolution** | e.g. **1920×1080** (match the portal) |
| **Max file size** | e.g. **3 MB** (match the portal) |

Use assets per product **`docs/MEDIA.md`** and the monorepo [fab-listing-media](fab-listing-media/README.md) folder when applicable.

---

## 5. Media gallery

| Constraint | Notes |
|-------------|--------|
| **Requirement** | At least **1** image or **3D** asset where the portal allows. |
| **Maximum** | Up to **24** files. |

---

## 6. Epic Developer Community forum post

| Option | When to use |
|--------|-------------|
| **No, do not create a forum post** | You do not want an automatic EDC post from the linked Epic account. |
| **Yes, create a forum post** | Public discussion/support thread; must link **Fab** and **Epic Developer Community** as required. |

---

## 7. Mature content

| Option | When to use |
|--------|-------------|
| **No, this listing does not contain mature content.** | Default for most tools and docs. |
| **Yes, this listing contains mature content.** | Only if it meets **Mature content guidelines** in the portal. |

---

## 8. Disallow use by Generative AI Programs

| Option | Notes |
|--------|--------|
| Whether to set HTML **“NoAI”**-style rules so the product is **not** used by generative AI programs | Choose per product and policy. |

---

## 9. Use of generative artificial intelligence (AI) tools

| Option | Notes |
|--------|--------|
| **No, it was not partly or fully created with generative AI** | You did not use generative AI in the work you ship, or the portal’s definition of “output from Generative AI Programs” does not apply. |
| **Yes, it was partly or fully created with generative AI** | Disclose as required. Includes “output from Generative AI Programs” where the portal says so. |

If you used **AI-generated marketing images** (e.g. listing thumbnails) but code/assets are not AI-generated, check the **exact** portal wording and legal guidance.

---

## 10. Promotional content

| Field | Notes |
|--------|--------|
| **Includes promotional content** (checkbox) | Check if the product includes **product placement, logos, slogans**, or other real-world **brand** promotion. The portal may show a user-facing notice. |

---

## 11. FAQs

| Field | Notes |
|--------|--------|
| **FAQs** | Use **+** to add **Q&A** pairs to help buyers. |

---

## 12. Unreal Engine version (add one block per version line)

| Field | Notes |
|--------|--------|
| **Version title** * | Short label; character limit (e.g. **30**) in the portal. |
| **Project file link** * | **https://** link to the downloadable (marketplace / host URL after the file is available). |
| **Supported engine version** * | Search or select the engine version(s) you support. |
| **Supported target platforms** * | e.g. **Editor Win64** for editor-only tools; add others only if you build and test them. |
| **Version notes** | Changelog, known limits, or “use the zip that matches 5.7.x,” etc. |

**Multi-downloadable listings** (e.g. bundle): you may add **several** version rows or separate listing entries per policy—follow what the portal allows and [PUBLISHER_ASSEMBLY.md](../immersive-labs-ue-bundle/docs/PUBLISHER_ASSEMBLY.md) for the bundle.

---

## Related in this monorepo

- [fab-listing-index.md](fab-listing-index.md) — product list and `DOCUMENTATION.md` links.
- Per-product: `docs/MEDIA.md`, `docs/PACKAGING_FOR_FAB.md`, `docs/TESTING.md`.
