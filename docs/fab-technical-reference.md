# Fab technical reference (shared)

This document applies to **all** Fab code-plugin products in this repository. Product-specific specs live under each product directory (for example [`worldbuilder-audit-convert/docs/`](../worldbuilder-audit-convert/docs/)).

Primary sources and requirements for a Fab-compliant Unreal Engine code plugin:

## Source 1: Fab Technical Requirements

- **URL:** [FAB-TECHNICAL-REQUIREMENTS](https://support.fab.com/s/article/FAB-TECHNICAL-REQUIREMENTS)

Summary:

- Code plugins must include **`EngineVersion`** in the `.uplugin` file.
- Each module must define **`PlatformAllowList`** or **`PlatformDenyList`**.
- Code plugins must include **`FabURL`** in the `.uplugin` **after** submission for approval (when the product URL is known).
- Plugins may depend on built-in Unreal Engine plugins, **not** on other user-made plugins.
- Plugins must **not** be closed-source for any code that depends on Unreal Engine source; that code must be included in the packaged plugin.
- All source and header files must include a **publisher copyright notice**.
- Plugins must contain **at least one C++ module**.
- Plugins may include content, but the **majority** of the submission must add editor functionality, integrate with third-party systems, or expose complex gameplay logic to Blueprints.
- Plugins must **not** distribute `.exe` or `.msi` files.
- Publishers should test packaging with the Unreal Editor **Package** function or **`RunUAT BuildPlugin`** before submission.
- Epic builds plugins against the **three latest major engine versions** by default.
- **Example projects** are strongly encouraged and should be **linked separately** rather than embedding the plugin itself.

## Source 2: Publishing assets for sale or free download in Fab

- **URL:** [Publishing assets for sale or free download in Fab](https://dev.epicgames.com/documentation/fab/publishing-assets-for-sale-or-free-download-in-fab?lang=en-US)

Summary:

- Workflow stages: **prepare** → **create listing and upload assets** → **send for review** → **publish**.
- Fab distinguishes between assets, products, packs, and listings.
- Listing statuses include Draft, Pending approval, Changes needed, Approved.
- Listings must follow technical requirements and content guidelines.

**Implication for this project:** Define a code plugin with clear editor-facing value, modest technical scope, strong example-project support, and documentation that reduces setup friction.

## Source 3: Optimization tools (Fab listing signal)

- Practical **editor-side** optimization tasks; measurable cleanup or performance wins.
- Broad supported engine versions increase perceived value.
- Feature-dense, technical listings leave room for a **more beginner-friendly, workflow-focused** alternative.

## Source 4: Placement tool (Fab listing signal)

- Level-design **convenience** and time savings resonate.
- Straightforward use cases sell well.

**Market implication:** Opportunity for a **mid-priced** Unreal code plugin between basic placement helpers and deeply technical optimization utilities — clear editor productivity for environment work and cleaner scenes without requiring low-level optimization theory.
