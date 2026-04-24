# Harbor Annex — demo map beat sheet

**Purpose:** A single playable “tour” map that proves the **Harbor Suite** pillars in **before → after** beats for trailers, screenshots, and buyer onboarding.

**Asset name (recommended):** `HarborAnnex`  
**Suggested path:** `/Game/Maps/HarborAnnex`

Author this map in the **Harbor** project (see `Harbor/Content/Maps/README.md`). This repository does not commit `.umap` binaries.

---

## Design rules

- **One contiguous tour** the player walks in **8–12 minutes**.
- Each **wing** maps to exactly **one pillar** (Charts, Stowage, Shakedown, Clearance).
- **Before** states should look like believable indie entropy (messy labels, a few exaggerated “bad” examples).
- **After** states should be achievable **live** using Harbor Suite (no fake UI).

---

## Hub — Dock Office (~2 min)

**Player experience:** Small reception space with four labeled corridors (decals or mesh text).

**Before beat:** Props suggest chaos (sticky notes, scattered paper meshes).

**After beat:** Open **Harbor Suite**; narrator/tooltip text explains the four pillars in one screen.

**Capture:** Wide shot of UI + environment.

---

## Wing A — Charts (“Chart Table Room”)

**Before:** Corkboard / sticky props implying an informal checklist that does not persist.

**After:** Open **Charts**; run **Save all dirty packages** after a deliberate dirty edit; show checkmarks persisting across restart (`Saved/HarborSuite/ChartsState.json`).

**Hero line:** “A checklist that saves with the project.”

---

## Wing B — Stowage (“Cargo Bay”)

**Before:** Many actors with vague labels (`Prop_`, `SM_thing`, duplicates).

**After:** Select a cluster; apply **Stowage** prefix; Outliner reads cleaner in one pass.

**Hero line:** “Readable Outliner hygiene without a tools programmer.”

---

## Wing C — Shakedown (“Trial Course”)

**Before:** Short gameplay loop (jumps, triggers) where iteration friction is obvious if you explain it in voiceover.

**After:** **PIE**; use **Move player to first PlayerStart** and **time dilation** buttons to show a shorter loop.

**Hero line:** “Shorter PIE loops for solo devs.”

---

## Wing D — Clearance (“Quarantine Strip”)

**Before:** Actors with labels containing **`Problem`**; optional placards calling out “too many point lights” or large static meshes (educational, not a full profiler).

**After:** **Clearance → Run scan**; then **Select labels containing "Problem"** to jump straight to triage targets.

**Hero line:** “Know what will hurt before it hurts morale.”

---

## Exit — Departure Board

Closing sign or decal: **“From chaos to a repeatable ship cadence.”**

---

## Audio / VO (optional)

- 60–90 second voiceover following hub → wings → exit.
- Keep tool audio clicks subtle; prioritize clarity over hype.
