// Copyright (c) Immersive Labs. All Rights Reserved.

#include "LevelSelectionSetsEditor.h"

#include "Framework/Application/SlateApplication.h"
#include "Framework/Docking/TabManager.h"
#include "LevelSelectionSetsConstants.h"
#include "SLevelSelectionSetsPanel.h"
#include "Widgets/Docking/SDockTab.h"
#include "WorkspaceMenuStructure.h"
#include "WorkspaceMenuStructureModule.h"

#define LOCTEXT_NAMESPACE "FLevelSelectionSetsEditorModule"

void FLevelSelectionSetsEditorModule::StartupModule()
{
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(
		LevelSelectionSets::NomadTabId,
		FOnSpawnTab::CreateRaw(this, &FLevelSelectionSetsEditorModule::SpawnLevelSelectionSetsTab))
		.SetDisplayName(LOCTEXT("TabTitle", "Level Selection Sets"))
		.SetTooltipText(LOCTEXT("TabTooltip", "Save and recall named actor selections in the current level."))
		.SetGroup(WorkspaceMenu::GetMenuStructure().GetLevelEditorCategory())
		.SetMenuType(ETabSpawnerMenuType::Enabled);
}

void FLevelSelectionSetsEditorModule::ShutdownModule()
{
	if (FSlateApplication::IsInitialized())
	{
		FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(LevelSelectionSets::NomadTabId);
	}
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
