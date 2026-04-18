# Source control — Git, ignores, and LFS

Unreal projects mix **mergeable text** (`.uproject`, `.uplugin`, `.ini`, `.cpp`, `.h`, `.cs`, `.json`) with **large binaries** (`.uasset`, `.umap`, textures, audio). Your repo stays healthy when you **treat those differently**.

## Baseline

1. Use the **template** [`templates/gitignore-additions.unreal.txt`](../templates/gitignore-additions.unreal.txt) as a starting point—merge into your root `.gitignore`.  
2. **Never** commit `Binaries/`, `Intermediate/`, `DerivedDataCache/`, `Saved/` from local machines to shared branches without a reason (build farms may differ).  
3. Prefer **one authoritative `.uproject`** per game product; avoid duplicate copies drifting apart.

## Git LFS

Enable LFS for asset types you actually version **frequently**:

- Common candidates: `.uasset`, `.umap`, `.png`, `.wav`, `.fbx` (if source art lives in repo).  
- See [`templates/gitattributes-lfs-sample.txt`](../templates/gitattributes-lfs-sample.txt); **tune** to your pipeline.

**Habit:** If artists rarely commit source `.psd`/`.blend`, keep those **outside** Git (Perforce, cloud, or art depot) and only commit exports the engine consumes.

## Branching (small teams)

- **`main`**: always shippable or clearly labeled otherwise.  
- **Short-lived feature branches** merged via PR or review buddy.  
- Avoid long-lived “integration hell” branches; Unreal merge conflicts on maps are painful.

## Blueprint and binary merges

- Expect **non-mergeable** conflicts on shared `.uasset` / `.umap`. Mitigation: **ownership by area**, **task branches**, duplicate levels only when intentional.  
- For critical Blueprints, **export** notes or screenshots of graph changes in PR descriptions.

## Large repos

- **Git partial clone** / sparse checkout where supported.  
- **Split** tools and game into separate repos if tooling teams churn independently.  
- Monitor **LFS bandwidth** costs if your host bills per egress.

## Security

- Use **`.gitignore`** for API keys, certificates, and local machine paths.  
- For shipped secrets (rare), use your engine’s **secure storage** patterns—not plaintext in Git.
