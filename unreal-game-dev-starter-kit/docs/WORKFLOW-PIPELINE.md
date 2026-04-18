# Workflow — from idea to vertical slice

A **lightweight milestone model** for Unreal projects. Adjust dates and gates to your team size; keep the **order** unless you enjoy rework.

## Phase 0 — Concept (days to weeks)

- **Goal:** One-page vision: genre, camera, core loop, target platform, non-goals.  
- **Exit:** Greenlight to spend engineering time on a **playable stub**, not full production.

## Phase 1 — Playable stub (prototype)

- **Goal:** One map, placeholder art, **one fun action** you can repeat (movement + interaction + fail/win stub).  
- **Technical:** Minimal module layout; no premature plugin explosion.  
- **Exit:** Video capture or build someone else can play without you in the room.

## Phase 2 — Vertical slice

- **Goal:** **Short** experience that looks like your target quality bar in **one** representative environment (not the whole game).  
- **Content:** Lock naming conventions for `Content/` (see templates).  
- **Code:** Identify replicated vs. local-only systems if multiplayer.  
- **Exit:** List of “known debt” vs. “must fix before scaling content.”

## Phase 3 — Production readiness (ongoing)

- **Build:** CI or scripted builds; repeatable packaging command.  
- **QA:** Smoke test checklist per milestone (define your own or extend [`templates/new-project-checklist.md`](../templates/new-project-checklist.md)).  
- **Performance:** Budget headers for frame time, memory, and load times **before** content explosion.

## Rituals that save months

| Ritual | Why |
|--------|-----|
| **Weekly playtest** with outsiders | Kills denial early |
| **Decision log** (ADRs or simple markdown) | Stops re-litigating |
| **Definition of Done** per task | Reduces “almost done” |
| **Cut list** when scope slips | Protects ship date |

## Handoff to production art

- Freeze **folder structure** and **naming** before outsourcing.  
- Provide a **single** import guide (units, pivot expectations, LOD policy in plain language).

This pipeline pairs with [SOURCE-CONTROL.md](SOURCE-CONTROL.md) so branches and merges do not collapse under binary growth.
