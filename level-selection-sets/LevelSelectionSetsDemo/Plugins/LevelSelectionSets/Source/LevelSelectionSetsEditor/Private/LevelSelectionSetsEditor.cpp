// Copyright (c) Immersive Labs. All Rights Reserved.

#include "LevelSelectionSetsEditor.h"

#include "Framework/Application/SlateApplication.h"
#include "Framework/Docking/TabManager.h"
#include "LevelSelectionSetsConstants.h"
#include "LevelSelectionSetsEditorStyle.h"
#include "SLevelSelectionSetsPanel.h"
#include "Textures/SlateIcon.h"
#include "Widgets/Docking/SDockTab.h"
#include "WorkspaceMenuStructure.h"
#include "WorkspaceMenuStructureModule.h"

#define LOCTEXT_NAMESPACE "FLevelSelectionSetsEditorModule"

void FLevelSelectionSetsEditorModule::StartupModule()
{
	FLevelSelectionSetsEditorStyle::Register();

	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(
		LevelSelectionSets::NomadTabId,
		FOnSpawnTab::CreateRaw(this, &FLevelSelectionSetsEditorModule::SpawnLevelSelectionSetsTab))
		.SetDisplayName(LOCTEXT("TabTitle", "Level Selection Sets"))
		.SetTooltipText(LOCTEXT("TabTooltip", "Save and recall named actor selections in the current level."))
		.SetGroup(WorkspaceMenu::GetMenuStructure().GetLevelEditorCategory())
		.SetIcon(FSlateIcon(
			FLevelSelectionSetsEditorStyle::GetStyleSetName(),
			FLevelSelectionSetsEditorStyle::TabIconName,
			FLevelSelectionSetsEditorStyle::TabIconSmallName))
		.SetMenuType(ETabSpawnerMenuType::Enabled);
}

void FLevelSelectionSetsEditorModule::ShutdownModule()
{
	if (FSlateApplication::IsInitialized())
	{
		FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(LevelSelectionSets::NomadTabId);
	}

	FLevelSelectionSetsEditorStyle::Unregister();
}

TSharedRef<SDockTab> FLevelSelectionSetsEditorModule::SpawnLevelSelectionSetsTab(const FSpawnTabArgs& Args)
{
	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			SNew(SLevelSelectionSetsPanel)
		];
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FLevelSelectionSetsEditorModule, LevelSelectionSetsEditor);
