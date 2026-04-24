// Copyright (c) Immersive Labs. All Rights Reserved.

#include "WorkflowToolkitEditor.h"

#include "Framework/Application/SlateApplication.h"
#include "Framework/Commands/UICommandList.h"
#include "Framework/Docking/TabManager.h"
#include "Framework/Commands/InputBindingManager.h"
#include "LevelEditor.h"
#include "Modules/ModuleManager.h"
#include "SWorkflowToolkitPanel.h"
#include "Textures/SlateIcon.h"
#include "Widgets/Docking/SDockTab.h"
#include "WorkflowToolkitActions.h"
#include "WorkflowToolkitCommands.h"
#include "WorkflowToolkitConstants.h"
#include "WorkflowToolkitEditorStyle.h"
#include "WorkspaceMenuStructure.h"
#include "WorkspaceMenuStructureModule.h"

#define LOCTEXT_NAMESPACE "FWorkflowToolkitEditorModule"

void FWorkflowToolkitEditorModule::StartupModule()
{
	FWorkflowToolkitEditorStyle::Register();

	FWorkflowToolkitCommands::Register();
	RegisterWorkflowToolkitInput();

	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(
		WorkflowToolkit::NomadTabId,
		FOnSpawnTab::CreateRaw(this, &FWorkflowToolkitEditorModule::SpawnWorkflowToolkitTab))
		.SetDisplayName(LOCTEXT("TabTitle", "Workflow Toolkit"))
		.SetTooltipText(LOCTEXT("TabTooltip", "Shortcuts for common editor workflows. Keys can be changed in Editor Preferences → Keyboard Shortcuts (Workflow Toolkit)."))
		.SetGroup(WorkspaceMenu::GetMenuStructure().GetLevelEditorCategory())
		.SetIcon(FSlateIcon(
			FWorkflowToolkitEditorStyle::GetStyleSetName(),
			FWorkflowToolkitEditorStyle::TabIconName,
			FWorkflowToolkitEditorStyle::TabIconSmallName))
		.SetMenuType(ETabSpawnerMenuType::Enabled);
}

void FWorkflowToolkitEditorModule::ShutdownModule()
{
	UnregisterWorkflowToolkitInput();

	if (FSlateApplication::IsInitialized())
	{
		FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(WorkflowToolkit::NomadTabId);
	}

	FWorkflowToolkitEditorStyle::Unregister();
}

void FWorkflowToolkitEditorModule::RegisterWorkflowToolkitInput()
{
	WorkflowToolkitPluginCommands = MakeShared<FUICommandList>();

	const FWorkflowToolkitCommands& C = FWorkflowToolkitCommands::Get();

	WorkflowToolkitPluginCommands->MapAction(
		C.OpenWorkflowToolkitPanel,
		FExecuteAction::CreateLambda([]()
		{
			if (FSlateApplication::IsInitialized())
			{
				FGlobalTabmanager::Get()->TryInvokeTab(FTabId(WorkflowToolkit::NomadTabId));
			}
		}));

	WorkflowToolkitPluginCommands->MapAction(
		C.FrameSelectionInViewport,
		FExecuteAction::CreateStatic(&FWorkflowToolkitActions::FrameSelectionInActiveViewport));

	WorkflowToolkitPluginCommands->MapAction(
		C.SelectAllActorsSameClass,
		FExecuteAction::CreateStatic(&FWorkflowToolkitActions::SelectAllActorsOfSameClassAsFirstSelection));

	WorkflowToolkitPluginCommands->MapAction(
		C.SnapActorLocationsIntegerGrid,
		FExecuteAction::CreateStatic(&FWorkflowToolkitActions::SnapSelectedActorLocationsToIntegerGrid));

	WorkflowToolkitPluginCommands->MapAction(
		C.SelectAllActorsSameStaticMesh,
		FExecuteAction::CreateStatic(&FWorkflowToolkitActions::SelectAllActorsUsingSameStaticMeshAsFirstSelection));

	WorkflowToolkitPluginCommands->MapAction(
		C.SetStaticMeshMobilityStatic,
		FExecuteAction::CreateStatic(&FWorkflowToolkitActions::SetSelectedStaticMeshComponentsMobilityStatic));

	WorkflowToolkitPluginCommands->MapAction(
		C.AlignSelectionBottomToFloor,
		FExecuteAction::CreateStatic(&FWorkflowToolkitActions::AlignSelectedActorsBottomToFloorTrace));

	WorkflowToolkitPluginCommands->MapAction(
		C.DuplicateSelection,
		FExecuteAction::CreateStatic(&FWorkflowToolkitActions::DuplicateSelectedActors));

	WorkflowToolkitPluginCommands->MapAction(
		C.SaveAllDirtyPackages,
		FExecuteAction::CreateStatic(&FWorkflowToolkitActions::SaveAllDirtyPackagesWithoutPrompt));

	WorkflowToolkitPluginCommands->MapAction(
		C.SyncContentBrowserToSelection,
		FExecuteAction::CreateStatic(&FWorkflowToolkitActions::SyncContentBrowserToSelection));

	WorkflowToolkitPluginCommands->MapAction(
		C.OpenProjectSettingsEngineGeneral,
		FExecuteAction::CreateStatic(&FWorkflowToolkitActions::OpenProjectSettingsEngineGeneral));

	WorkflowToolkitPluginCommands->MapAction(
		C.OpenPluginsEditor,
		FExecuteAction::CreateStatic(&FWorkflowToolkitActions::OpenPluginsEditorTab));

	WorkflowToolkitPluginCommands->MapAction(
		C.OpenWorldSettings,
		FExecuteAction::CreateStatic(&FWorkflowToolkitActions::OpenWorldSettingsTab));

	WorkflowToolkitPluginCommands->MapAction(
		C.OpenOutputLog,
		FExecuteAction::CreateStatic(&FWorkflowToolkitActions::OpenOutputLogTab));

	WorkflowToolkitPluginCommands->MapAction(
		C.OpenMessageLog,
		FExecuteAction::CreateStatic(&FWorkflowToolkitActions::OpenMessageLogTab));

	WorkflowToolkitPluginCommands->MapAction(
		C.OpenKeyboardShortcutsSettings,
		FExecuteAction::CreateStatic(&FWorkflowToolkitActions::OpenEditorKeyboardShortcutsSettings));

	WorkflowToolkitPluginCommands->MapAction(
		C.CopyActorPathsToClipboard,
		FExecuteAction::CreateStatic(&FWorkflowToolkitActions::CopySelectedActorPathsToClipboard));

	WorkflowToolkitPluginCommands->MapAction(
		C.SnapRotationTo90DegreeGrid,
		FExecuteAction::CreateStatic(&FWorkflowToolkitActions::SnapSelectedActorsRotationToNearestRightAngles));

	WorkflowToolkitPluginCommands->MapAction(
		C.SelectAllActorsSameMaterial,
		FExecuteAction::CreateStatic(&FWorkflowToolkitActions::SelectAllActorsUsingSameMaterialAsFirstStaticMeshSelection));

	WorkflowToolkitPluginCommands->MapAction(
		C.OpenStaticMeshAssetFromSelection,
		FExecuteAction::CreateStatic(&FWorkflowToolkitActions::OpenFirstStaticMeshFromSelectionInAssetEditor));

	WorkflowToolkitPluginCommands->MapAction(
		C.RunMapCheck,
		FExecuteAction::CreateStatic(&FWorkflowToolkitActions::RunMapCheck));

	FInputBindingManager::Get().RegisterCommandList(
		FWorkflowToolkitCommands::Get().GetContextName(),
		WorkflowToolkitPluginCommands.ToSharedRef());

	FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>(TEXT("LevelEditor"));
	LevelEditorModule.GetGlobalLevelEditorActions()->Append(WorkflowToolkitPluginCommands.ToSharedRef());
}

void FWorkflowToolkitEditorModule::UnregisterWorkflowToolkitInput()
{
	if (WorkflowToolkitPluginCommands.IsValid() && FWorkflowToolkitCommands::IsRegistered())
	{
		FInputBindingManager::Get().UnregisterCommandList(
			FWorkflowToolkitCommands::Get().GetContextName(),
			WorkflowToolkitPluginCommands.ToSharedRef());
	}
	WorkflowToolkitPluginCommands.Reset();

	if (FWorkflowToolkitCommands::IsRegistered())
	{
		FWorkflowToolkitCommands::Unregister();
	}
}

TSharedRef<SDockTab> FWorkflowToolkitEditorModule::SpawnWorkflowToolkitTab(const FSpawnTabArgs& Args)
{
	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			SNew(SWorkflowToolkitPanel)
		];
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FWorkflowToolkitEditorModule, WorkflowToolkitEditor);

UE_DEFINE_TCOMMANDS(FWorkflowToolkitCommands)
