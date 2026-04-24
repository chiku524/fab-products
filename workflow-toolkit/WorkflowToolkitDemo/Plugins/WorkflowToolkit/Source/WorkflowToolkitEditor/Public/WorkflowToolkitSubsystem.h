// Copyright (c) Immersive Labs. All Rights Reserved.

#pragma once

#include "EditorSubsystem.h"
#include "WorkflowToolkitSubsystem.generated.h"

UCLASS()
class WORKFLOWTOOLKITEDITOR_API UWorkflowToolkitSubsystem : public UEditorSubsystem
{
	GENERATED_BODY()

public:
	/** Frames the current actor selection in the first active level viewport. */
	UFUNCTION(BlueprintCallable, Category = "Workflow Toolkit")
	void FrameSelectionInActiveViewport();

	/** Selects every actor in the level whose class matches the first selected actor. */
	UFUNCTION(BlueprintCallable, Category = "Workflow Toolkit")
	void SelectAllActorsOfSameClassAsFirstSelection();

	/** Saves all dirty map and content packages without prompting. */
	UFUNCTION(BlueprintCallable, Category = "Workflow Toolkit")
	void SaveAllDirtyPackagesWithoutPrompt();

	/** Focuses the Content Browser on the first selected asset, or a mesh used by a selected actor. */
	UFUNCTION(BlueprintCallable, Category = "Workflow Toolkit")
	void SyncContentBrowserToSelection();

	UFUNCTION(BlueprintCallable, Category = "Workflow Toolkit")
	void OpenOutputLogTab();

	UFUNCTION(BlueprintCallable, Category = "Workflow Toolkit")
	void OpenMessageLogTab();

	/** Rounds selected actor world locations to whole world units. */
	UFUNCTION(BlueprintCallable, Category = "Workflow Toolkit")
	void SnapSelectedActorLocationsToIntegerGrid();

	/** Selects every actor whose static mesh matches the first selected actor's static mesh. */
	UFUNCTION(BlueprintCallable, Category = "Workflow Toolkit")
	void SelectAllActorsUsingSameStaticMeshAsFirstSelection();

	/** Sets mobility to Static on every StaticMeshComponent on the selected actors (batch for lighting-friendly meshes). */
	UFUNCTION(BlueprintCallable, Category = "Workflow Toolkit")
	void SetSelectedStaticMeshComponentsMobilityStatic();

	/** Moves each selected actor vertically so its bounds bottom sits on the first visibility hit below (floor/walkable). */
	UFUNCTION(BlueprintCallable, Category = "Workflow Toolkit")
	void AlignSelectedActorsBottomToFloorTrace();

	UFUNCTION(BlueprintCallable, Category = "Workflow Toolkit")
	void DuplicateSelectedActors();

	UFUNCTION(BlueprintCallable, Category = "Workflow Toolkit")
	void ExecuteEditorConsoleCommand(const FString& Command);

	UFUNCTION(BlueprintCallable, Category = "Workflow Toolkit")
	void OpenProjectSettingsEngineGeneral();

	UFUNCTION(BlueprintCallable, Category = "Workflow Toolkit")
	void OpenPluginsEditorTab();

	UFUNCTION(BlueprintCallable, Category = "Workflow Toolkit")
	void OpenWorldSettingsTab();

	/** Opens Editor Preferences → General → Keyboard Shortcuts (search "Workflow Toolkit" to rebind). */
	UFUNCTION(BlueprintCallable, Category = "Workflow Toolkit")
	void OpenEditorKeyboardShortcutsSettings();

	UFUNCTION(BlueprintCallable, Category = "Workflow Toolkit")
	void CopySelectedActorPathsToClipboard();

	UFUNCTION(BlueprintCallable, Category = "Workflow Toolkit")
	void SnapSelectedActorsRotationToNearestRightAngles();

	UFUNCTION(BlueprintCallable, Category = "Workflow Toolkit")
	void SelectAllActorsUsingSameMaterialAsFirstStaticMeshSelection();

	UFUNCTION(BlueprintCallable, Category = "Workflow Toolkit")
	void OpenFirstStaticMeshFromSelectionInAssetEditor();

	UFUNCTION(BlueprintCallable, Category = "Workflow Toolkit")
	void RunMapCheck();
};
