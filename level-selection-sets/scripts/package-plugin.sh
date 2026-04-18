#!/usr/bin/env bash
# Package Level Selection Sets via RunUAT (Git Bash / WSL on Windows with UE installed).
# Usage: ./package-plugin.sh <EngineRoot> [UeVersionLabel] [OutputParent]
# Example: ./package-plugin.sh "/c/Program Files/Epic Games/UE_5.4" 5.4

set -euo pipefail

ENGINE_ROOT="${1:?Usage: $0 <EngineRoot> [UeVersionLabel] [OutputParent]}"
UE_LABEL="${2:-5.4}"
OUTPUT_PARENT="${3:-}"

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PRODUCT_ROOT="$(dirname "$SCRIPT_DIR")"
PLUGIN_FILE="$PRODUCT_ROOT/LevelSelectionSets/LevelSelectionSets.uplugin"
RUNUAT="$ENGINE_ROOT/Engine/Build/BatchFiles/RunUAT.bat"

if [[ ! -f "$RUNUAT" ]]; then
  echo "RunUAT not found: $RUNUAT" >&2
  exit 1
fi
if [[ ! -f "$PLUGIN_FILE" ]]; then
  echo "Plugin not found: $PLUGIN_FILE" >&2
  exit 1
fi

if [[ -z "$OUTPUT_PARENT" ]]; then
  OUTPUT_PARENT="$PRODUCT_ROOT/dist"
fi
mkdir -p "$OUTPUT_PARENT"

PKG_NAME="LevelSelectionSets-UE${UE_LABEL}-Win64"
PKG_DIR="$OUTPUT_PARENT/$PKG_NAME"
PLUGIN_FULL="$(cd "$(dirname "$PLUGIN_FILE")" && pwd)/$(basename "$PLUGIN_FILE")"

rm -rf "$PKG_DIR"

echo "Engine:  $ENGINE_ROOT"
echo "Plugin:  $PLUGIN_FULL"
echo "Package: $PKG_DIR"
echo "Running RunUAT BuildPlugin ..."

# Windows RunUAT must run under cmd from Git Bash
cmd.exe //c "\"$RUNUAT\" BuildPlugin -Plugin=\"$PLUGIN_FULL\" -Package=\"$PKG_DIR\" -Rocket"
echo "Done. See docs/VERIFICATION.md and docs/ENGINE_TEST_MATRIX.md for QA."
