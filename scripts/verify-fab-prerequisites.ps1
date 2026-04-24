#Requires -Version 5.1
# Static checks: LICENSE, uplugin, key docs, and (optional) RunUAT output for Fab listings.
#   .\verify-fab-prerequisites.ps1
#   .\verify-fab-prerequisites.ps1 -CheckBuildOutput
#   .\verify-fab-prerequisites.ps1 -CheckBuildOutput -MonorepoBuildRoot "C:\ilfab-ue57"
[CmdletBinding()]
param(
	[switch] $CheckBuildOutput,
	[string] $MonorepoBuildRoot = "C:\ilfab-ue57"
)
$ErrorActionPreference = "Stop"
# $PSScriptRoot = ...\fab-products\scripts
$root = Split-Path -Parent $PSScriptRoot
$ok = 0; $bad = 0; $warn = 0
function Test-One {
	param([string]$Path, [string]$What)
	$p = Join-Path $root $Path
	if (Test-Path -LiteralPath $p) {
		$script:ok++
		Write-Host "  OK: $Path" -ForegroundColor Green
	} else {
		$script:bad++
		Write-Host "  MISSING: $What -> $Path" -ForegroundColor Red
	}
}
function Test-BuildPath {
	param([string]$Path)
	$p = if ([System.IO.Path]::IsPathRooted($Path)) { $Path } else { Join-Path $root $Path }
	if (Test-Path -LiteralPath $p) {
		Write-Host "  OK: $p" -ForegroundColor Green
	} else {
		$script:warn++
		Write-Host "  (not built yet) $p" -ForegroundColor Yellow
	}
}
Write-Host "fab-products: $root" -ForegroundColor Cyan
Write-Host ""
Write-Host "== Required files (per product) =="
$prods = @(
	@{ Name = "Harbor Suite"; Base = "harbor-suite" }
	@{ Name = "Level Selection Sets"; Base = "level-selection-sets" }
	@{ Name = "World Builder Templates"; Base = "worldbuilder-templates" }
	@{ Name = "WorldBuilder Audit & Convert"; Base = "worldbuilder-audit-convert" }
	@{ Name = "Workflow Toolkit"; Base = "workflow-toolkit" }
	@{ Name = "Unreal Game Dev Starter Kit"; Base = "unreal-game-dev-starter-kit" }
	@{ Name = "Immersive Labs UE bundle"; Base = "immersive-labs-ue-bundle" }
)
foreach ($pr in $prods) {
	Write-Host "[$($pr.Name)]" -ForegroundColor Yellow
	Test-One -Path "$($pr.Base)\LICENSE" -What "License"
}
Test-One "harbor-suite\Harbor\Plugins\HarborSuite\HarborSuite.uplugin" "Harbor uplugin"
Test-One "level-selection-sets\LevelSelectionSets\LevelSelectionSets.uplugin" "LSS uplugin"
Test-One "worldbuilder-templates\WorldBuilderTemplates\WorldBuilderTemplates.uplugin" "WBT uplugin"
Test-One "worldbuilder-audit-convert\WorldBuilderAuditConvert\WorldBuilderAuditConvert.uplugin" "WBA uplugin"
Test-One "workflow-toolkit\WorkflowToolkit\WorkflowToolkit.uplugin" "WTK uplugin"
Test-One "unreal-game-dev-starter-kit\docs\PACKAGING_FOR_FAB.md" "Starter kit packaging doc"
Test-One "unreal-game-dev-starter-kit\docs\FAB_LISTING_COPY.md" "Starter kit listing"
Test-One "immersive-labs-ue-bundle\docs\FAB_LISTING_COPY.md" "Bundle listing"
Test-One "docs\fab-listing-index.md" "fab-listing-index"

if ($CheckBuildOutput) {
	Write-Host ""
	Write-Host "== Monorepo RunUAT output (UE 5.7 Win64) ==" -ForegroundColor Cyan
	$M = $MonorepoBuildRoot
	$u = "5.7"
	@(
		"1-hs\HarborSuite-UE$u-Win64"
		"2-lss\LevelSelectionSets-UE$u-Win64"
		"3-wbt\WorldBuilderTemplates-UE$u-Win64"
		"4-wtk\WorkflowToolkit-UE$u-Win64"
		"5-wbac\WorldBuilderAuditConvert-UE$u-Win64"
	) | ForEach-Object {
		Test-BuildPath (Join-Path $M $_)
	}
}
Write-Host ""
if ($bad -gt 0) {
	Write-Host "Summary: $ok found, $bad required file(s) missing" -ForegroundColor Red
	exit 1
}
$msg = "Summary: $ok path checks passed"
if ($CheckBuildOutput -and $warn -gt 0) { $msg += "; $warn build folder(s) not present (run build-fab-marketplace-drops-ue57.ps1)" }
Write-Host $msg -ForegroundColor Cyan
exit 0
