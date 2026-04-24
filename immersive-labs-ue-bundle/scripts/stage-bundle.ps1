#Requires -Version 5.1
<#
.SYNOPSIS
  Stages Fab-ready zips for the Immersive Labs UE bundle (one engine line at a time).

.DESCRIPTION
  Produces a staging folder with:
  - LevelSelectionSets-UE<ver>-Win64.zip
  - WorldBuilderAuditConvert-UE<ver>-Win64.zip
  - UnrealGameDevStarterKit-docs.zip

  Source for plugins is either (A) each product’s dist/ folder, or (B) the monorepo short-path
  output from fab-products/scripts/build-fab-marketplace-drops-ue57.ps1 (C:\ilfab-ue57\... by default).

.PARAMETER UeVersionLabel
  Must match the label used when building (e.g. "5.7" for the current monorepo default).

.PARAMETER MonorepoBuildRoot
  If set, zips are taken from e.g. "<MonorepoBuildRoot>\2-lss\LevelSelectionSets-UE5.7-Win64" instead
  of level-selection-sets\dist\... . Use after running build-fab-marketplace-drops-ue57.ps1.

.PARAMETER StagingRoot
  Default: immersive-labs-ue-bundle/staging/<UE label>/
#>

[CmdletBinding()]
param(
	[Parameter(Mandatory = $false)]
	[string] $UeVersionLabel = "5.7",

	[Parameter(Mandatory = $false)]
	[string] $MonorepoBuildRoot = "",

	[Parameter(Mandatory = $false)]
	[string] $StagingRoot = ""
)

$ErrorActionPreference = "Stop"

$ScriptDir = Split-Path -Parent $MyInvocation.MyCommand.Path
$BundleRoot = Split-Path -Parent $ScriptDir
$RepoRoot = Split-Path -Parent $BundleRoot

if ([string]::IsNullOrWhiteSpace($StagingRoot)) {
	$StagingRoot = Join-Path $BundleRoot ("staging\UE" + ($UeVersionLabel -replace '\.', '-') )
}

if (Test-Path -LiteralPath $StagingRoot) {
	Write-Warning "Removing existing staging: $StagingRoot"
	Remove-Item -LiteralPath $StagingRoot -Recurse -Force
}
$null = New-Item -ItemType Directory -Force -Path $StagingRoot

function Zip-IfExists {
	param(
		[string] $SourceDir,
		[string] $ZipPath
	)
	if (-not (Test-Path -LiteralPath $SourceDir)) {
		Write-Warning "Skip (not found): $SourceDir"
		return
	}
	if (Test-Path -LiteralPath $ZipPath) {
		Remove-Item -LiteralPath $ZipPath -Force
	}
	Write-Host "Zipping: $SourceDir -> $ZipPath"
	Compress-Archive -Path $SourceDir -DestinationPath $ZipPath -CompressionLevel Optimal
}

$LeafLss = "LevelSelectionSets-UE$UeVersionLabel-Win64"
$LeafWbac = "WorldBuilderAuditConvert-UE$UeVersionLabel-Win64"

if (-not [string]::IsNullOrWhiteSpace($MonorepoBuildRoot)) {
	$M = $MonorepoBuildRoot.TrimEnd('\', '/')
	$Lss = Join-Path (Join-Path $M "2-lss") $LeafLss
	$Wb = Join-Path (Join-Path $M "5-wbac") $LeafWbac
	Write-Host "Using monorepo build output under: $M" -ForegroundColor Cyan
} else {
	$Lss = Join-Path $RepoRoot "level-selection-sets\dist\$LeafLss"
	$Wb = Join-Path $RepoRoot "worldbuilder-audit-convert\dist\$LeafWbac"
}

Zip-IfExists -SourceDir $Lss -ZipPath (Join-Path $StagingRoot "$LeafLss.zip")
Zip-IfExists -SourceDir $Wb -ZipPath (Join-Path $StagingRoot "$LeafWbac.zip")

$Kit = Join-Path $RepoRoot "unreal-game-dev-starter-kit"
if (-not (Test-Path -LiteralPath $Kit)) {
	Write-Warning "Starter kit folder not found: $Kit"
} else {
	$kitZip = Join-Path $StagingRoot "UnrealGameDevStarterKit-docs.zip"
	if (Test-Path -LiteralPath $kitZip) {
		Remove-Item -LiteralPath $kitZip -Force
	}
	Write-Host "Zipping starter kit: $Kit -> $kitZip"
	Compress-Archive -Path $Kit -DestinationPath $kitZip -CompressionLevel Optimal
}

Write-Host ""
Write-Host "Staging complete: $StagingRoot" -ForegroundColor Cyan
Write-Host "Upload these zips as separate Fab downloadables for this engine line."
