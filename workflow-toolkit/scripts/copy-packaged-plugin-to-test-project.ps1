# Copies the latest RunUAT BuildPlugin output into the default WorkflowToolkit test project.
# Run from repo: pwsh -File workflow-toolkit/scripts/copy-packaged-plugin-to-test-project.ps1
# Prerequisite: Run scripts/package-plugin.ps1 (output: workflow-toolkit/dist/WorkflowToolkit-UE<ver>-Win64) or set -PackageRoot.

param(
	[string]$PackageRoot = "",
	[string]$Destination = ""
)

$ErrorActionPreference = "Stop"

if ([string]::IsNullOrEmpty($PackageRoot)) {
	$wtRoot = Split-Path $PSScriptRoot -Parent
	$dist = Join-Path $wtRoot "dist"
	if (Test-Path -LiteralPath $dist) {
		$pick = Get-ChildItem -LiteralPath $dist -Directory -ErrorAction SilentlyContinue | Where-Object { $_.Name -like "WorkflowToolkit-UE*-Win64" } | Sort-Object Name -Descending | Select-Object -First 1
		if ($null -ne $pick) {
			$PackageRoot = $pick.FullName
		}
	}
	if ([string]::IsNullOrEmpty($PackageRoot) -or -not (Test-Path -LiteralPath $PackageRoot)) {
		Write-Error "No packaged plugin found under $dist. Run: .\scripts\package-plugin.ps1 -EngineRoot `"<UE_5.7_root>`""
	}
}
if ([string]::IsNullOrEmpty($Destination)) {
	$Destination = Join-Path $env:USERPROFILE "Documents\Unreal Projects\WorkflowToolkit\Plugins\WorkflowToolkit"
}

$uplugin = Join-Path $PackageRoot "WorkflowToolkit.uplugin"
if (-not (Test-Path $uplugin)) {
	Write-Error "PackageRoot is not a valid packaged plugin (missing WorkflowToolkit.uplugin): $PackageRoot"
	exit 1
}

$parent = Split-Path $Destination -Parent
if (-not (Test-Path $parent)) {
	New-Item -ItemType Directory -Path $parent -Force | Out-Null
}

if (Test-Path $Destination) {
	Remove-Item $Destination -Recurse -Force
}

Copy-Item -Path $PackageRoot -Destination $Destination -Recurse -Force
Write-Host "Copied packaged plugin to: $Destination"
