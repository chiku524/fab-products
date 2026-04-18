# Architecture primer — Unreal Engine

A **practical mental model** for structuring gameplay code and content in UE5. Use it to agree on vocabulary across engineering, design, and art.

## 1. Modules

- **Runtime module** (e.g. `YourGame`): ships with the game; gameplay classes, subsystems you register here.  
- **Editor module** (optional): tools, custom asset actions, editor-only utilities.  
- **Plugin modules**: isolate features (audio middleware, platform SDKs) so dependencies stay clear.

**Habit:** One **primary game module** owns core types (`GameMode`, `GameState`, `PlayerController`, `Pawn`, `HUD`/`UI` entry). Avoid spreading “core” logic across many tiny modules until you have a reason (compile times, licensing boundaries).

## 2. Game Instance vs. Game Mode vs. Game State

| Type | Lifetime | Typical use |
|------|----------|-------------|
| **GameInstance** | Persists across travel within a running session | Online subsystem hooks, save-game meta, app-level settings |
| **GameMode** | Exists on server / authority for a map | Rules, spawning, win conditions |
| **GameState** | Replicated snapshot of match state | Scores, timers, replicated match flags |

**Habit:** If you debate where something lives for more than ten minutes, default to **GameState** for replicated match facts and **PlayerState** for per-player replicated facts.

## 3. Subsystems

**World**, **GameInstance**, and **Engine** subsystems give you **lazy, scoped singletons** without abusing `GetGameInstance()->...` globals everywhere.

**Habit:** Prefer a **WorldSubsystem** for level-scoped services (spawn pools keyed to a map) and **GameInstanceSubsystem** for session-scoped services (achievement facade, analytics session).

## 4. Data: assets vs. runtime instances

- **Primary assets** (DataAssets, curves, tables) define *data*.  
- **Actors / components** define *instances* in a level.

**Habit:** Push tunable balance and configuration into **assets** or **tables** early so designers iterate without recompiling C++.

## 5. Blueprint vs. C++

Reasonable default for small teams:

- **C++:** core loops, networking boundaries, performance-sensitive systems, plugin boundaries.  
- **Blueprint:** UI flow, designer-tunable behaviors, rapid prototyping.

**Habit:** Expose **clear, narrow** C++ functions to Blueprint rather than mirroring entire class hierarchies in both languages.

## 6. Networking (if multiplayer)

Assume **server authority** for gameplay-affecting state. Document which classes replicate and **why**. The kit does not teach replication from zero—pair this section with Epic’s networking docs for your milestone.

## 7. Where this connects to the workflow doc

When [WORKFLOW-PIPELINE.md](WORKFLOW-PIPELINE.md) says “lock an architecture decision,” use the vocabulary above so the decision is **one paragraph** everyone understands.
