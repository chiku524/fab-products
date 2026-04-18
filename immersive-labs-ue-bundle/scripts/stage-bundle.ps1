#Requires -Version 5.1
<#
.SYNOPSIS
  Stages Fab-ready zips for the Immersive Labs UE bundle (one engine line at a time).

.DESCRIPTION
  Expects RunUAT output folders under each plugin product's dist/:
  - level-selection-sets/dist/LevelSelectionSets-UE<ver>-Win64
  - worldbuilder-audit-convert/dist/WorldBuilderAuditConvert-UE<ver>-Win64
  Zips the Unreal Game Dev Starter Kit folder for documentation delivery.

.PARAMETER UeVersionLabel
  Must match the label used when running package-plugin.ps1 (e.g. "5.4").

.PARAMETER StagingRoot
  Default: immersive-labs-ue-bundle/staging/<UE label>/
#>

[CmdletBinding()]
param(
    [Parameter(Mandatory = $false)]
    [string] $UeVersionLabel = "5.4",

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

$Lss = Join-Path $RepoRoot "level-selection-sets\dist\LevelSelectionSets-UE$UeVersionLabel-Win64"
$Wb = Join-Path $RepoRoot "worldbuilder-audit-convert\dist\WorldBuilderAuditConvert-UE$UeVersionLabel-Win64"
$Kit = Join-Path $RepoRoot "unreal-game-dev-starter-kit"

Zip-IfExists -SourceDir $Lss -ZipPath (Join-Path $StagingRoot "LevelSelectionSets-UE$UeVersionLabel-Win64.zip")
Zip-IfExists -SourceDir $Wb -ZipPath (Join-Path $StagingRoot "WorldBuilderAuditConvert-UE$UeVersionLabel-Win64.zip")

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
Write-Host "Staging complete: $StagingRoot"
Write-Host "Upload these zips as separate Fab downloadables for this engine line."
