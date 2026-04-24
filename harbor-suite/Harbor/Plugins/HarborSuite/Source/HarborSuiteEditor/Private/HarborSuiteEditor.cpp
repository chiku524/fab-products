// Copyright (c) Immersive Labs. All Rights Reserved.

#include "HarborSuiteEditor.h"

#include "Framework/Application/SlateApplication.h"
#include "Framework/Docking/TabManager.h"
#include "HarborSuiteConstants.h"
#include "HarborSuiteEditorStyle.h"
#include "SHarborSuitePanel.h"
#include "Textures/SlateIcon.h"
#include "Widgets/Docking/SDockTab.h"
#include "WorkspaceMenuStructure.h"
#include "WorkspaceMenuStructureModule.h"

#define LOCTEXT_NAMESPACE "FHarborSuiteEditorModule"

void FHarborSuiteEditorModule::StartupModule()
{
	FHarborSuiteEditorStyle::Register();

	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(
		HarborSuite::NomadTabName,
		FOnSpawnTab::CreateRaw(this, &FHarborSuiteEditorModule::SpawnHarborSuiteTab))
		.SetDisplayName(LOCTEXT("TabTitle", "Harbor Suite"))
		.SetTooltipText(LOCTEXT("TabTooltip", "Charts, Stowage, Shakedown, and Clearance for small-team Unreal workflows."))
		.SetGroup(WorkspaceMenu::GetMenuStructure().GetLevelEditorCategory())
		.SetIcon(FSlateIcon(
			FHarborSuiteEditorStyle::GetStyleSetName(),
			FHarborSuiteEditorStyle::TabIconName,
			FHarborSuiteEditorStyle::TabIconSmallName))
		.SetMenuType(ETabSpawnerMenuType::Enabled);
}

void FHarborSuiteEditorModule::ShutdownModule()
{
	if (FSlateApplication::IsInitialized())
	{
		FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(HarborSuite::NomadTabName);
	}

	FHarborSuiteEditorStyle::Unregister();
}

TSharedRef<SDockTab> FHarborSuiteEditorModule::SpawnHarborSuiteTab(const FSpawnTabArgs& Args)
{
	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			SNew(SHarborSuitePanel)
		];
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FHarborSuiteEditorModule, HarborSuiteEditor);
