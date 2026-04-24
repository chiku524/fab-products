// Copyright (c) Immersive Labs. All Rights Reserved.

#include "WorkflowToolkitCommands.h"

#include "InputCoreTypes.h"
#include "WorkflowToolkitEditorStyle.h"

#define LOCTEXT_NAMESPACE "WorkflowToolkitCommands"

FWorkflowToolkitCommands::FWorkflowToolkitCommands()
	: TCommands<FWorkflowToolkitCommands>(
		  TEXT("WorkflowToolkit"),
		  NSLOCTEXT("Contexts", "WorkflowToolkit", "Workflow Toolkit"),
		  NAME_None,
		  FWorkflowToolkitEditorStyle::GetStyleSetName())
{
}

void FWorkflowToolkitCommands::RegisterCommands()
{
	UI_COMMAND(
		OpenWorkflowToolkitPanel,
		"Open Workflow Toolkit",
		"Opens the Workflow Toolkit panel (Window menu).",
		EUserInterfaceActionType::Button,
		FInputChord(EModifierKey::Alt | EModifierKey::Shift, EKeys::W));

	UI_COMMAND(
		FrameSelectionInViewport,
		"Frame Selection in Viewport",
		"Frames the current actor selection in the active level viewport.",
		EUserInterfaceActionType::Button,
		FInputChord(EModifierKey::Control | EModifierKey::Alt, EKeys::F));

	UI_COMMAND(
		SelectAllActorsSameClass,
		"Select All Actors of Same Class",
		"Selects every actor in the level whose class matches the first selected actor.",
		EUserInterfaceActionType::Button,
		FInputChord());

	UI_COMMAND(
		SnapActorLocationsIntegerGrid,
		"Snap Actor Locations to Integer Grid",
		"Rounds selected actor locations to whole world units.",
		EUserInterfaceActionType::Button,
		FInputChord());

	UI_COMMAND(
		SelectAllActorsSameStaticMesh,
		"Select All Actors Using Same Static Mesh",
		"Selects actors that share the same static mesh as the first selection.",
		EUserInterfaceActionType::Button,
		FInputChord());

	UI_COMMAND(
		SetStaticMeshMobilityStatic,
		"Set Static Mesh Mobility to Static",
		"Sets StaticMeshComponent mobility to Static on selected actors.",
		EUserInterfaceActionType::Button,
		FInputChord());

	UI_COMMAND(
		AlignSelectionBottomToFloor,
		"Align Selection Bottom to Floor",
		"Trace down and align actor bounds so the bottom sits on the floor.",
		EUserInterfaceActionType::Button,
		FInputChord());

	UI_COMMAND(
		DuplicateSelection,
		"Duplicate Selection (Workflow Toolkit)",
		"Duplicates the current selection (editor Duplicate command).",
		EUserInterfaceActionType::Button,
		FInputChord());

	UI_COMMAND(
		SaveAllDirtyPackages,
		"Save All Dirty Packages",
		"Saves all dirty map and content packages without a confirmation dialog.",
		EUserInterfaceActionType::Button,
		FInputChord(EModifierKey::Control | EModifierKey::Alt, EKeys::S));

	UI_COMMAND(
		SyncContentBrowserToSelection,
		"Sync Content Browser to Selection",
		"Focuses the Content Browser on the selected asset or mesh.",
		EUserInterfaceActionType::Button,
		FInputChord(EModifierKey::Control | EModifierKey::Alt, EKeys::B));

	UI_COMMAND(
		OpenProjectSettingsEngineGeneral,
		"Open Project Settings (Engine General)",
		"Opens Project Settings to Engine → General.",
		EUserInterfaceActionType::Button,
		FInputChord());

	UI_COMMAND(
		OpenPluginsEditor,
		"Open Plugins Window",
		"Opens the Plugins browser.",
		EUserInterfaceActionType::Button,
		FInputChord());

	UI_COMMAND(
		OpenWorldSettings,
		"Open World Settings",
		"Opens the World Settings tab for the current level.",
		EUserInterfaceActionType::Button,
		FInputChord());

	UI_COMMAND(
		OpenOutputLog,
		"Open Output Log",
		"Opens the Output Log tab.",
		EUserInterfaceActionType::Button,
		FInputChord(EModifierKey::Control | EModifierKey::Alt, EKeys::O));

	UI_COMMAND(
		OpenMessageLog,
		"Open Message Log",
		"Opens the Message Log tab.",
		EUserInterfaceActionType::Button,
		FInputChord());

	UI_COMMAND(
		OpenKeyboardShortcutsSettings,
		"Keyboard Shortcuts Settings",
		"Opens Editor Preferences → Keyboard Shortcuts so you can rebind Workflow Toolkit keys.",
		EUserInterfaceActionType::Button,
		FInputChord());

	UI_COMMAND(
		CopyActorPathsToClipboard,
		"Copy Actor Paths to Clipboard",
		"Copies the full object paths of selected actors (one per line) for pasting into logs, configs, or documentation.",
		EUserInterfaceActionType::Button,
		FInputChord());

	UI_COMMAND(
		SnapRotationTo90DegreeGrid,
		"Snap Rotation to 90° Grid",
		"Snaps each selected actor's rotation to the nearest 90° on roll, pitch, and yaw (quick grid alignment).",
		EUserInterfaceActionType::Button,
		FInputChord());

	UI_COMMAND(
		SelectAllActorsSameMaterial,
		"Select All Actors with Same Material (slot 0)",
		"Uses the first static mesh material on slot 0 from the selection and selects every actor that uses that material on slot 0.",
		EUserInterfaceActionType::Button,
		FInputChord());

	UI_COMMAND(
		OpenStaticMeshAssetFromSelection,
		"Open Static Mesh Asset from Selection",
		"Opens the Static Mesh editor for the first static mesh found on the current selection.",
		EUserInterfaceActionType::Button,
		FInputChord());

	UI_COMMAND(
		RunMapCheck,
		"Run Map Check",
		"Runs the editor Map Check command (reports errors/warnings in the Message Log).",
		EUserInterfaceActionType::Button,
		FInputChord());
}

#undef LOCTEXT_NAMESPACE
