# Harbor Suite — verification checklist (short)

Use before tagging a release or uploading to Fab.

- [ ] **Compile:** `HarborEditor` target builds with no errors.
- [ ] **Load:** Editor starts; **Harbor Suite** appears under **Edit → Plugins** and loads without red errors in **Output Log**.
- [ ] **UI:** **Window → Level Editor → Harbor Suite** opens; all four pillar tabs switch correctly.
- [ ] **Charts:** Checkboxes persist after editor restart (same project).
- [ ] **Stowage:** Prefix applies to selected actors; transaction undo works (**Ctrl+Z**).
- [ ] **Shakedown:** With PIE running, player resets to first `PlayerStart`; time dilation changes apply.
- [ ] **Clearance:** Scan produces summary text; “Problem” selection finds labeled actors.
- [ ] **Docs:** `docs/QUICKSTART.md` steps match the built product.

For detailed steps, see [TESTING.md](TESTING.md).
