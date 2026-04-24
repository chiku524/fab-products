#Requires -Version 5.1
<#
.SYNOPSIS
  Generates Visual Studio solution/project files for an Unreal .uproject (same as Explorer's
  "Generate Visual Studio project files" when that context menu is missing).

.DESCRIPTION
  Calls Epic's UnrealVersionSelector.exe with /projectfiles. This does not compile the
  project; it only regenerates the .sln and project files so Visual Studio can build.

.PARAMETER UProjectPath
  Full path to YourProject.uproject.

.PARAMETER EngineRoot
  Root of an Unreal installation (folder containing Engine\Binaries\Win64\UnrealVersionSelector.exe).
  If omitted, the script tries to infer it from the .uproject file's EngineAssociation (e.g. 5.7 -> UE_5.7).

.EXAMPLE
  .\generate-ue-project-files.ps1 -UProjectPath "C:\full\path\to\harbor-suite\Harbor\Harbor.uproject"
#>

[CmdletBinding()]
param(
    [Parameter(Mandatory = $true)]
    [string] $UProjectPath,

    [Parameter(Mandatory = $false)]
    [string] $EngineRoot = ""
)

$ErrorActionPreference = "Stop"

$UProjectPath = $UProjectPath.Trim()
if (-not (Test-Path -LiteralPath $UProjectPath)) {
    Write-Error "File not found: $UProjectPath"
}
$UProjectFull = (Resolve-Path -LiteralPath $UProjectPath).Path
if (-not $UProjectFull.EndsWith(".uproject", [System.StringComparison]::OrdinalIgnoreCase)) {
    Write-Error "Expected a .uproject file path."
}

function Get-UnrealVersionSelectorPath {
    param([string] $Root)
    $Root = $Root.TrimEnd('\', '/')
    $p = Join-Path $Root "Engine\Binaries\Win64\UnrealVersionSelector.exe"
    if (Test-Path -LiteralPath $p) { return $p }
    return $null
}

$Selector = $null

if (-not [string]::IsNullOrWhiteSpace($EngineRoot)) {
    $EngineRoot = $EngineRoot.TrimEnd('\', '/')
    $Selector = Get-UnrealVersionSelectorPath -Root $EngineRoot
    if (-not $Selector) {
        Write-Error "UnrealVersionSelector.exe not found under: $EngineRoot\Engine\Binaries\Win64\"
    }
}
else {
    $epicRoot = "C:\Program Files\Epic Games"
    $assoc = $null
    try {
        $json = Get-Content -LiteralPath $UProjectFull -Raw | ConvertFrom-Json
        $assoc = $json.EngineAssociation
    } catch {
        Write-Warning "Could not parse .uproject JSON; will search for any installed engine."
    }

    if ($assoc -and $assoc -match '^[\d.]+$') {
        $guess = Join-Path $epicRoot ("UE_" + $assoc)
        $Selector = Get-UnrealVersionSelectorPath -Root $guess
        if ($Selector) {
            Write-Host "Using engine inferred from EngineAssociation ($assoc): $guess"
        }
    }

    if (-not $Selector -and (Test-Path -LiteralPath $epicRoot)) {
        $dirs = Get-ChildItem -LiteralPath $epicRoot -Directory -ErrorAction SilentlyContinue | Where-Object { $_.Name -like "UE_*" } | Sort-Object Name -Descending
        foreach ($d in $dirs) {
            $cand = Get-UnrealVersionSelectorPath -Root $d.FullName
            if ($cand) {
                $Selector = $cand
                Write-Warning "Using first Unreal install found: $($d.FullName) (pass -EngineRoot to pin a specific engine)."
                break
            }
        }
    }

    if (-not $Selector) {
        Write-Error @"
UnrealVersionSelector.exe not found. Install Unreal Engine from the Epic Games Launcher, or pass -EngineRoot, e.g.:
  -EngineRoot ""C:\Program Files\Epic Games\UE_5.7""
"@
    }
}

Write-Host "UnrealVersionSelector: $Selector"
Write-Host "Project:               $UProjectFull"
Write-Host "Running /projectfiles ..."

$proc = Start-Process -FilePath $Selector -ArgumentList @("/projectfiles", $UProjectFull) -Wait -PassThru -NoNewWindow
if ($proc.ExitCode -ne 0) {
    Write-Error "UnrealVersionSelector exited with code $($proc.ExitCode)."
}

Write-Host "Done. Open the generated .sln in Visual Studio and build Development Editor."
