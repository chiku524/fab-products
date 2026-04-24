// Copyright (c) Immersive Labs. All Rights Reserved.

#pragma once

#include "Containers/UnrealString.h"

struct FWorkflowToolkitActions
{
	static void FrameSelectionInActiveViewport();
	static void SelectAllActorsOfSameClassAsFirstSelection();
	static void SaveAllDirtyPackagesWithoutPrompt();
	static void SyncContentBrowserToSelection();
	static void OpenOutputLogTab();
	static void OpenMessageLogTab();
	static void SnapSelectedActorLocationsToIntegerGrid();

	static void SelectAllActorsUsingSameStaticMeshAsFirstSelection();
	static void SetSelectedStaticMeshComponentsMobilityStatic();
	static void AlignSelectedActorsBottomToFloorTrace();
	static void DuplicateSelectedActors();
	static void ExecuteEditorConsoleCommand(const FString& Command);

	static void OpenProjectSettingsEngineGeneral();
	static void OpenPluginsEditorTab();
	static void OpenWorldSettingsTab();
	static void OpenEditorKeyboardShortcutsSettings();

	static void CopySelectedActorPathsToClipboard();
	static void SnapSelectedActorsRotationToNearestRightAngles();
	static void SelectAllActorsUsingSameMaterialAsFirstStaticMeshSelection();
	static void OpenFirstStaticMeshFromSelectionInAssetEditor();
	static void RunMapCheck();

private:
	FWorkflowToolkitActions() = delete;
};
