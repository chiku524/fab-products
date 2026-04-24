#Requires -Version 5.1
# RunUAT BuildPlugin for Immersive Labs Fab products (one engine install), then zips outputs for upload.
# Uses a *short* -OutputParent under the drive (default C:\ilfab-ue57\...) to avoid Windows MAX_PATH failures
# when the plugin ID or project path is long (e.g. LevelSelectionSets in a deep repo tree).
#
# Usage (from fab-products):
#   .\scripts\build-fab-marketplace-drops-ue57.ps1
# Optional: -EngineRoot "C:\Program Files\Epic Games\UE_5.7" -PackageRootShort "C:\ilfab-ue57"
[CmdletBinding()]
param(
	[string] $EngineRoot = "C:\Program Files\Epic Games\UE_5.7",
	[string] $PackageRootShort = "C:\ilfab-ue57"
)
$ErrorActionPreference = "Stop"
$RunUAT = Join-Path $EngineRoot "Engine\Build\BatchFiles\RunUAT.bat"
if (-not (Test-Path -LiteralPath $RunUAT)) {
	Write-Error "Unreal not found. Install UE or pass -EngineRoot. Expected: $RunUAT"
}
$Root = Split-Path -Parent $PSScriptRoot
$Ue = "5.7"
$null = New-Item -ItemType Directory -Force -Path $PackageRootShort
$items = @(
	@{ Rel = "harbor-suite\scripts\package-plugin.ps1"; Name = "Harbor Suite"; Sub = "1-hs" }
	@{ Rel = "level-selection-sets\scripts\package-plugin.ps1"; Name = "Level Selection Sets"; Sub = "2-lss" }
	@{ Rel = "worldbuilder-templates\scripts\package-plugin.ps1"; Name = "World Builder Templates"; Sub = "3-wbt" }
	@{ Rel = "workflow-toolkit\scripts\package-plugin.ps1"; Name = "Workflow Toolkit"; Sub = "4-wtk" }
	@{ Rel = "worldbuilder-audit-convert\scripts\package-plugin.ps1"; Name = "WorldBuilder Audit & Convert"; Sub = "5-wbac" }
)
$zipped = @()
foreach ($it in $items) {
	$ps1 = Join-Path $Root $it.Rel
	$outParent = Join-Path $PackageRootShort $it.Sub
	Write-Host ""
	Write-Host "========== $($it.Name) ==========" -ForegroundColor Cyan
	& $ps1 -EngineRoot $EngineRoot -UeVersionLabel $Ue -OutputParent $outParent
	if ($LASTEXITCODE -ne 0) { throw "Package failed: $($it.Name) (exit $LASTEXITCODE)" }
}
$map = @(
	@{ OutParent = (Join-Path $PackageRootShort "1-hs"); Leaf = "HarborSuite-UE$Ue-Win64" }
	@{ OutParent = (Join-Path $PackageRootShort "2-lss"); Leaf = "LevelSelectionSets-UE$Ue-Win64" }
	@{ OutParent = (Join-Path $PackageRootShort "3-wbt"); Leaf = "WorldBuilderTemplates-UE$Ue-Win64" }
	@{ OutParent = (Join-Path $PackageRootShort "4-wtk"); Leaf = "WorkflowToolkit-UE$Ue-Win64" }
	@{ OutParent = (Join-Path $PackageRootShort "5-wbac"); Leaf = "WorldBuilderAuditConvert-UE$Ue-Win64" }
)
$dropRoot = Join-Path $Root "fab-marketplace-drops\UE$Ue-Win64"
if (Test-Path -LiteralPath $dropRoot) {
	Remove-Item -LiteralPath $dropRoot -Recurse -Force
}
$null = New-Item -ItemType Directory -Force -Path $dropRoot
foreach ($m in $map) {
	$src = Join-Path $m.OutParent $m.Leaf
	if (-not (Test-Path -LiteralPath $src)) {
		Write-Warning "Expected package folder missing: $src"
		continue
	}
	$zip = Join-Path $dropRoot "$($m.Leaf).zip"
	if (Test-Path -LiteralPath $zip) { Remove-Item -LiteralPath $zip -Force }
	Write-Host "Zipping: $($m.Leaf) -> $zip" -ForegroundColor Green
	Compress-Archive -Path $src -DestinationPath $zip -CompressionLevel Optimal
}
Write-Host ""
Write-Host "Plugin package folders: under $PackageRootShort\<1-hs|2-lss|3-wbt|4-wtk|5-wbac>\" -ForegroundColor Cyan
Write-Host "Fab upload zips: $dropRoot" -ForegroundColor Cyan
Write-Host "Next: follow each product docs (TESTING/VERIFICATION), then upload in Fab portal."
