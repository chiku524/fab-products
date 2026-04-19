#Requires -Version 5.1
<#
.SYNOPSIS
  Runs UnrealEditor-Cmd with WorldBuilderTemplatesCreateSampleMaps to bake sample .umap files into the plugin Content folder.

.PARAMETER EngineRoot
  Unreal Engine root (contains Engine\Binaries\Win64\UnrealEditor-Cmd.exe).

.PARAMETER UProjectPath
  Absolute path to a .uproject that has WorldBuilderTemplates enabled under Plugins/.
#>

[CmdletBinding()]
param(
    [Parameter(Mandatory = $true)]
    [string] $EngineRoot,

    [Parameter(Mandatory = $true)]
    [string] $UProjectPath
)

$ErrorActionPreference = "Stop"

$EngineRoot = $EngineRoot.TrimEnd('\', '/')
$EditorCmd = Join-Path $EngineRoot "Engine\Binaries\Win64\UnrealEditor-Cmd.exe"
if (-not (Test-Path -LiteralPath $EditorCmd)) {
    Write-Error "UnrealEditor-Cmd not found: $EditorCmd"
}

if (-not (Test-Path -LiteralPath $UProjectPath)) {
    Write-Error "Project not found: $UProjectPath"
}

$UProjectFull = (Resolve-Path -LiteralPath $UProjectPath).Path

Write-Host "EditorCmd: $EditorCmd"
Write-Host "UProject:  $UProjectFull"
Write-Host "Running WorldBuilderTemplatesCreateSampleMaps ..."

$argList = @(
    "`"$UProjectFull`"",
    "-run=WorldBuilderTemplatesCreateSampleMaps",
    "-unattended",
    "-nop4",
    "-nosplash",
    "-log"
)

$proc = Start-Process -FilePath $EditorCmd -ArgumentList $argList -NoNewWindow -Wait -PassThru
if ($proc.ExitCode -ne 0) {
    Write-Error "Commandlet exited with code $($proc.ExitCode)."
}

Write-Host "Done. Check Plugins/WorldBuilderTemplates/Content/Maps for new .umap assets."
