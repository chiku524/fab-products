# Fab submission checklist — Level Selection Sets

Use this when moving from **draft** → **review** → **publish** in the Fab portal.

## Technical

- [ ] One plugin package per supported **engine version** (5.4 / 5.5 / 5.6) built and smoke-tested  
- [ ] `.uplugin` includes **`EngineVersion`** aligned with the package  
- [ ] Each module has **`PlatformAllowList`** (or deny list) — Win64 for v1 editor  
- [ ] **Full source** for Unreal-dependent code included in the download  
- [ ] **Copyright** notices in headers/sources (publisher name filled in)  
- [ ] No **`.exe` / `.msi`** inside the plugin deliverable  
- [ ] Packaging tested (**RunUAT BuildPlugin** or editor **Package**)  
- [ ] **`FabURL`** added to `.uplugin` **after** you have the live product URL (post-approval workflow per Fab)

## Documentation

- [ ] `DOCUMENTATION.md` and `docs/` included or linked as promised on the listing  
- [ ] `CHANGELOG.md` matches the version you are shipping  
- [ ] `LICENSE` matches your seller terms  
- [ ] `SUPPORT.md` has real contact details  

## Listing content

- [ ] Title, short and long descriptions (see [FAB_LISTING_COPY.md](FAB_LISTING_COPY.md))  
- [ ] Keywords / categories / audience tags  
- [ ] Supported engine versions and **Windows editor** scope stated clearly  
- [ ] Thumbnail + gallery + trailer per [MEDIA.md](MEDIA.md)  
- [ ] Example project link (hosted separately) if advertised  

## Legal / policy

- [ ] Content complies with Fab content and technical guidelines  
- [ ] You have rights to all demo assets shown in media  
