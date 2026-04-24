# Copies each Fab product’s plugin (excluding build folders) into its Harbor-style demo under Plugins/<PluginName>/.
# Run from fab-products (or any cwd):
#   .\scripts\sync-fab-demo-plugins.ps1
# Use after you change the canonical plugin under e.g. level-selection-sets/LevelSelectionSets/ and want the demo copy updated.
$ErrorActionPreference = "Stop"
$root = Split-Path $PSScriptRoot -Parent
function Sync-Plugin {
	param([string]$From, [string]$To)
	$args = @(
		$From, $To, "/E", "/NFL", "/NDL", "/NJH", "/NJS", "/NS", "/NC",
		"/XD", "Binaries", "/XD", "Intermediate", "/XD", "Saved", "/XD", "DerivedDataCache", "/XD", ".vs"
	)
	$rc = & robocopy @args
	if ($rc -ge 8) { throw "robocopy failed $rc $From -> $To" }
}
Sync-Plugin (Join-Path $root "level-selection-sets\LevelSelectionSets") (Join-Path $root "level-selection-sets\LevelSelectionSetsDemo\Plugins\LevelSelectionSets")
Sync-Plugin (Join-Path $root "worldbuilder-templates\WorldBuilderTemplates") (Join-Path $root "worldbuilder-templates\WorldBuilderTemplatesDemo\Plugins\WorldBuilderTemplates")
Sync-Plugin (Join-Path $root "workflow-toolkit\WorkflowToolkit") (Join-Path $root "workflow-toolkit\WorkflowToolkitDemo\Plugins\WorkflowToolkit")
Write-Host "Synced plugins into sample projects (LevelSelectionSetsDemo, WorldBuilderTemplatesDemo, WorkflowToolkitDemo)."
