@echo off
REM Links harbor-suite\Harbor\ to %USERPROFILE%\Documents\Unreal Projects\Harbor\ then opens the .uproject
REM (double-clicking THIS file — not a replacement for the global .uproject handler).
set "ROOT=%~dp0"
set "U=%ROOT%Harbor\Harbor.uproject"
set "PS1=%ROOT%..\scripts\Junction-UE-Project-To-Documents.ps1"
if not exist "%U%" ( echo Missing: "%U%" & exit /b 1 )
if not exist "%PS1%" ( echo Missing: "%PS1%" & exit /b 1 )
powershell.exe -NoProfile -ExecutionPolicy Bypass -File "%PS1%" -UProjectPath "%U%" -OpenAfter
