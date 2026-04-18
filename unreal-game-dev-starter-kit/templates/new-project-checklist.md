# New Unreal project — starter checklist

Copy this file into your repo as `docs/PROJECT_CHECKLIST.md` or track tasks in your issue tracker. Check boxes as you complete items.

## Repository & tooling

- [ ] Root `.gitignore` merged with [`gitignore-additions.unreal.txt`](gitignore-additions.unreal.txt) (trim what you do not need).  
- [ ] If using Git LFS: `.gitattributes` configured (see [`gitattributes-lfs-sample.txt`](gitattributes-lfs-sample.txt)); LFS quotas understood.  
- [ ] **One** canonical `.uproject` path agreed by the team.  
- [ ] README in repo with how to generate IDE project files and build the editor target.

## Unreal project settings (high level)

- [ ] Target platforms chosen (desktop / console / mobile) and documented.  
- [ ] Default map for **Play** and packaging entry map set intentionally.  
- [ ] Naming convention for `Content/` top-level folders (e.g. `Core`, `Characters`, `Levels`, `UI`, `Audio`, `VFX`).  
- [ ] Decision: Blueprint-only vs. C++ module—document in one paragraph.

## Team habits

- [ ] **Owner** for `Content/` areas (who approves moves/renames).  
- [ ] **Branch** strategy one page (see [SOURCE-CONTROL.md](../docs/SOURCE-CONTROL.md)).  
- [ ] **Weekly playtest** slot on the calendar.  
- [ ] **Decision log** location (`DECISIONS.md`, wiki, or Notion).

## Milestones (from the kit)

- [ ] Phase 1 “playable stub” exit criteria agreed ([WORKFLOW-PIPELINE.md](../docs/WORKFLOW-PIPELINE.md)).  
- [ ] Phase 2 “vertical slice” scope bounded (timebox + cut list).
