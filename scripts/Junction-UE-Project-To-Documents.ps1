#Requires -Version 5.1
<#
.SYNOPSIS
  Creates a directory junction in "Documents\Unreal Projects\<Name>" that points at your
  real project folder (e.g. under fab-products), then optionally opens the .uproject with
  the same handler as a normal double-click (UnrealVersionSelector / editor).

.DESCRIPTION
  Unreal and Epic tooling often *assume* projects live under:
    %USERPROFILE%\Documents\Unreal Projects\
  but your source can stay in a git clone elsewhere. A **junction** is a same-volume
  directory link: both paths see identical files, so you only maintain one copy.

  **Double-clicking** a .uproject only runs the registered "open" program for that
  extension — it will not run a custom "copy to Documents" step. Use this script (or
  a shortcut to it) when you want that workflow. After the junction exists, double-
  opening:
    %USERPROFILE%\Documents\Unreal Projects\<Name>\<Project>.uproject
  is the same project as in the repo.

  **Cross-volume:** Junctions work on the *same* NTFS volume. If your repo is on D:
  and Documents is on C:, Create-SymbolicLink (symlink) may be needed and can require
  Developer Mode or elevation — see the error message if junction fails.

.PARAMETER UProjectPath
  Full path to the .uproject file (e.g. ...\harbor-suite\Harbor\Harbor.uproject).

.PARAMETER DocumentsUnrealRoot
  Default: $env:USERPROFILE\Documents\Unreal Projects

.PARAMETER LinkFolderName
  Folder name under DocumentsUnrealRoot. Default: uproject name without .uproject

.PARAMETER OpenAfter
  If set, runs the .uproject path under Documents (invokes the same shell open action as a double-click).

.EXAMPLE
  .\Junction-UE-Project-To-Documents.ps1 -UProjectPath "C:\work\fab-products\harbor-suite\Harbor\Harbor.uproject" -OpenAfter
#>
[CmdletBinding(SupportsShouldProcess = $true)]
param(
	[Parameter(Mandatory = $true)]
	[string] $UProjectPath,

	[Parameter(Mandatory = $false)]
	[string] $DocumentsUnrealRoot = "",

	[Parameter(Mandatory = $false)]
	[string] $LinkFolderName = "",

	[Parameter(Mandatory = $false)]
	[switch] $OpenAfter
)

$ErrorActionPreference = "Stop"

$UProjectPath = $UProjectPath.Trim()
if (-not (Test-Path -LiteralPath $UProjectPath)) {
	Write-Error "File not found: $UProjectPath"
}
$uFull = (Resolve-Path -LiteralPath $UProjectPath).Path
if (-not $uFull.EndsWith(".uproject", [StringComparison]::OrdinalIgnoreCase)) {
	Write-Error "Path must be a .uproject file"
}

$sourceDir = (Split-Path -Parent $uFull)
$projName = [System.IO.Path]::GetFileNameWithoutExtension($uFull)

if ([string]::IsNullOrWhiteSpace($LinkFolderName)) {
	$LinkFolderName = $projName
}
if ([string]::IsNullOrWhiteSpace($DocumentsUnrealRoot)) {
	$DocumentsUnrealRoot = Join-Path $env:USERPROFILE "Documents\Unreal Projects"
}
$junctionPath = Join-Path $DocumentsUnrealRoot $LinkFolderName
$uProjectAtJunction = Join-Path $junctionPath ([System.IO.Path]::GetFileName($uFull))

$null = New-Item -ItemType Directory -Force -Path $DocumentsUnrealRoot

if (Test-Path -LiteralPath $junctionPath) {
	$item = Get-Item -LiteralPath $junctionPath -Force
	$isJunction = ($item.Attributes -band [IO.FileAttributes]::ReparsePoint) -ne 0
	if (-not $isJunction) {
		Write-Error "Path already exists and is not a junction: $junctionPath (rename or remove it, or use -LinkFolderName)."
	} else {
		Write-Host "Junction already exists (reusing): $junctionPath — if the wrong project opens, delete this junction folder in Explorer and re-run."
	}
} else {
	if ($PSCmdlet.ShouldProcess($junctionPath, "Create directory junction to $sourceDir")) {
		try {
			New-Item -ItemType Junction -Path $junctionPath -Target $sourceDir | Out-Null
		} catch {
			Write-Error "Could not create junction. Same-volume (e.g. C: to C:) NTFS is required for junctions. If your repo and Documents are on different drives, copy the project or use a dev-environment symlink. Original error: $($_.Exception.Message)"
		}
		Write-Host "Created junction: $junctionPath -> $sourceDir"
	}
}

if (-not (Test-Path -LiteralPath $uProjectAtJunction)) {
	Write-Error "After junction, uproject not found at: $uProjectAtJunction"
}

if ($OpenAfter) {
	Write-Host "Opening: $uProjectAtJunction"
	# Same shell "open" as double-click; uses your .uproject file association (UnrealVersionSelector, etc.)
	Start-Process -FilePath $uProjectAtJunction
}

Write-Host "Use this file for a normal Unreal open path: $uProjectAtJunction"
Write-Host "Plugins enabled in the .uproject (e.g. HarborSuite) load when the editor starts; if you get a 'missing module' dialog, build Development Editor for this project from Visual Studio first."
