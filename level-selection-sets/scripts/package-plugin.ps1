#Requires -Version 5.1
<#
.SYNOPSIS
  Runs Epic's RunUAT BuildPlugin for Level Selection Sets (Windows editor plugin).

.DESCRIPTION
  Builds a Fab-ready plugin folder for one installed Unreal Engine tree. Run once
  per engine *minor line* you support (e.g. 5.4.x, 5.5.x), each from a machine
  with that engine installed.

.PARAMETER EngineRoot
  Root of the Unreal installation (folder that contains Engine\Build\BatchFiles\RunUAT.bat).

.PARAMETER UeVersionLabel
  Short label for the output folder name only (e.g. "5.4", "5.5"). Does not change the engine used.

.PARAMETER OutputParent
  Directory where the packaged plugin folder will be created. Default: dist\ under this product.
  Use a short path (e.g. C:\ilfab-ue57\lss) if RunUAT fails with Windows MAX_PATH under a deep repo clone.

.EXAMPLE
  .\package-plugin.ps1 -EngineRoot "C:\Program Files\Epic Games\UE_5.4"

.EXAMPLE
  .\package-plugin.ps1 -EngineRoot "D:\Unreal\UE_5.5" -UeVersionLabel "5.5" -OutputParent "C:\Out\FabBuilds"
#>

[CmdletBinding()]
param(
    [Parameter(Mandatory = $true)]
    [string] $EngineRoot,

    [Parameter(Mandatory = $false)]
    [string] $UeVersionLabel = "5.4",

    [Parameter(Mandatory = $false)]
    [string] $OutputParent = ""
)

$ErrorActionPreference = "Stop"

$EngineRoot = $EngineRoot.TrimEnd('\', '/')
$RunUAT = Join-Path $EngineRoot "Engine\Build\BatchFiles\RunUAT.bat"
if (-not (Test-Path -LiteralPath $RunUAT)) {
    Write-Error "RunUAT not found at: $RunUAT`nCheck -EngineRoot (expected Engine\Build\BatchFiles\RunUAT.bat under it)."
}

$ScriptDir = Split-Path -Parent $MyInvocation.MyCommand.Path
$ProductRoot = Split-Path -Parent $ScriptDir
$PluginFile = Join-Path $ProductRoot "LevelSelectionSets\LevelSelectionSets.uplugin"
if (-not (Test-Path -LiteralPath $PluginFile)) {
    Write-Error "Plugin descriptor not found: $PluginFile"
}

if ([string]::IsNullOrWhiteSpace($OutputParent)) {
    $OutputParent = Join-Path $ProductRoot "dist"
}
$null = New-Item -ItemType Directory -Force -Path $OutputParent

$PackageName = "LevelSelectionSets-UE$UeVersionLabel-Win64"
$PackageDir = Join-Path $OutputParent $PackageName

if (Test-Path -LiteralPath $PackageDir) {
    Write-Warning "Removing existing package output: $PackageDir"
    Remove-Item -LiteralPath $PackageDir -Recurse -Force
}

$PluginFileFull = (Resolve-Path -LiteralPath $PluginFile).Path
$PackageDirFull = $PackageDir

Write-Host "Engine:  $EngineRoot"
Write-Host "Plugin:  $PluginFileFull"
Write-Host "Package: $PackageDirFull"
Write-Host "Running RunUAT BuildPlugin ..."

# Invoke RunUAT via cmd so .bat argument parsing matches Epic's documented command line.
cmd.exe /c "`"$RunUAT`" BuildPlugin -Plugin=`"$PluginFileFull`" -Package=`"$PackageDirFull`" -Rocket"
if ($LASTEXITCODE -ne 0) {
    Write-Error "RunUAT failed with exit code $LASTEXITCODE."
}

Write-Host "Done. Zip the contents of the package folder (or the folder itself) for Fab upload after QA."
Write-Host "Next: run through docs/VERIFICATION.md and record results in docs/ENGINE_TEST_MATRIX.md"
