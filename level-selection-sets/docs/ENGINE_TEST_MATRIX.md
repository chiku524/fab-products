# Engine test matrix (publisher)

Use this table to record **which Unreal Engine builds** you have **packaged and smoke-tested** before listing them on Fab.  
**Rule:** one **RunUAT**-built package per **minor line** (5.4.x, 5.5.x, …), each built with that line’s installed engine.

| UE version (exact build) | Built (date) | Package output name | RunUAT / script OK | Editor load + tab | Save / recall / rename / delete | Map save + reopen | Notes |
|--------------------------|--------------|---------------------|----------------------|-------------------|----------------------------------|-------------------|-------|
| e.g. 5.4.4 | | LevelSelectionSets-UE5.4-Win64 | ☐ | ☐ | ☐ | ☐ | |
| e.g. 5.5.3 | | LevelSelectionSets-UE5.5-Win64 | ☐ | ☐ | ☐ | ☐ | |
| | | | ☐ | ☐ | ☐ | ☐ | |

**Minimum engine:** UE **5.4**. Add a row for every **minor line** you ship.

**Sign-off:** When all required rows pass, copy the matrix (or a summary) into your internal release notes and attach build identifiers to the Fab downloadable(s).
