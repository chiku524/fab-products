#Requires -Version 5.1
<#
.SYNOPSIS
  Runs Epic's RunUAT BuildPlugin for Workflow Toolkit (Windows editor + runtime plugin).

.PARAMETER EngineRoot
  Root of the Unreal installation (folder that contains Engine\Build\BatchFiles\RunUAT.bat).

.PARAMETER UeVersionLabel
  Short label for the output folder name (e.g. "5.7").

.PARAMETER OutputParent
  Directory for packaged output. Default: dist\ under this product.
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
$PluginFile = Join-Path $ProductRoot "WorkflowToolkit\WorkflowToolkit.uplugin"
if (-not (Test-Path -LiteralPath $PluginFile)) {
    Write-Error "Plugin descriptor not found: $PluginFile"
}

if ([string]::IsNullOrWhiteSpace($OutputParent)) {
    $OutputParent = Join-Path $ProductRoot "dist"
}
$null = New-Item -ItemType Directory -Force -Path $OutputParent

$PackageName = "WorkflowToolkit-UE$UeVersionLabel-Win64"
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

Write-Host "Done. Optional: copy to a test project with scripts/copy-packaged-plugin-to-test-project.ps1 (set PackageRoot to the dist folder above)."
Write-Host "Zip the package folder for Fab upload after QA."
