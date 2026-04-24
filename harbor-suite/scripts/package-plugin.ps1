#Requires -Version 5.1
<#
.SYNOPSIS
  Runs Epic's RunUAT BuildPlugin for Harbor Suite (Windows editor plugin).

.PARAMETER EngineRoot
  Root of the Unreal installation (folder that contains Engine\Build\BatchFiles\RunUAT.bat).

.PARAMETER UeVersionLabel
  Short label for the output folder name only (e.g. "5.7"). Does not change the engine used.

.PARAMETER OutputParent
  Directory where the packaged plugin folder will be created. Default: dist\ under harbor-suite.

.EXAMPLE
  .\package-plugin.ps1 -EngineRoot "C:\Program Files\Epic Games\UE_5.7"
#>

[CmdletBinding()]
param(
    [Parameter(Mandatory = $true)]
    [string] $EngineRoot,

    [Parameter(Mandatory = $false)]
    [string] $UeVersionLabel = "5.7",

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
$PluginFile = Join-Path $ProductRoot "Harbor\Plugins\HarborSuite\HarborSuite.uplugin"
if (-not (Test-Path -LiteralPath $PluginFile)) {
    Write-Error "Plugin descriptor not found: $PluginFile"
}

if ([string]::IsNullOrWhiteSpace($OutputParent)) {
    $OutputParent = Join-Path $ProductRoot "dist"
}
$null = New-Item -ItemType Directory -Force -Path $OutputParent

$PackageName = "HarborSuite-UE$UeVersionLabel-Win64"
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

cmd.exe /c "`"$RunUAT`" BuildPlugin -Plugin=`"$PluginFileFull`" -Package=`"$PackageDirFull`" -Rocket"
if ($LASTEXITCODE -ne 0) {
    Write-Error "RunUAT failed with exit code $LASTEXITCODE."
}

Write-Host "Done. Zip the package folder for Fab upload after QA (see docs/VERIFICATION.md)."
