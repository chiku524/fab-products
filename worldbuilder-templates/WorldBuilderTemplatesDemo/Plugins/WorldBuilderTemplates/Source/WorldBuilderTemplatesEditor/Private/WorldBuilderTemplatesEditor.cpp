// Copyright (c) Immersive Labs. All Rights Reserved.

#include "WorldBuilderTemplatesEditor.h"

#include "Framework/Application/SlateApplication.h"
#include "Framework/Docking/TabManager.h"
#include "SWorldBuilderTemplatesPanel.h"
#include "Textures/SlateIcon.h"
#include "Widgets/Docking/SDockTab.h"
#include "WorldBuilderTemplatesConstants.h"
#include "WorldBuilderTemplatesEditorStyle.h"
#include "WorkspaceMenuStructure.h"
#include "WorkspaceMenuStructureModule.h"

#define LOCTEXT_NAMESPACE "FWorldBuilderTemplatesEditorModule"

void FWorldBuilderTemplatesEditorModule::StartupModule()
{
	FWorldBuilderTemplatesEditorStyle::Register();

	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(
		WorldBuilderTemplates::NomadTabId,
		FOnSpawnTab::CreateRaw(this, &FWorldBuilderTemplatesEditorModule::SpawnWorldBuilderTemplatesTab))
		.SetDisplayName(LOCTEXT("TabTitle", "World Builder Templates"))
		.SetTooltipText(LOCTEXT("TabTooltip", "Browse ready-made world maps that ship with this plugin and open one as a starting point."))
		.SetGroup(WorkspaceMenu::GetMenuStructure().GetLevelEditorCategory())
		.SetIcon(FSlateIcon(
			FWorldBuilderTemplatesEditorStyle::GetStyleSetName(),
			FWorldBuilderTemplatesEditorStyle::TabIconName,
			FWorldBuilderTemplatesEditorStyle::TabIconSmallName))
		.SetMenuType(ETabSpawnerMenuType::Enabled);
}

void FWorldBuilderTemplatesEditorModule::ShutdownModule()
{
	if (FSlateApplication::IsInitialized())
	{
		FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(WorldBuilderTemplates::NomadTabId);
	}

	FWorldBuilderTemplatesEditorStyle::Unregister();
}

TSharedRef<SDockTab> FWorldBuilderTemplatesEditorModule::SpawnWorldBuilderTemplatesTab(const FSpawnTabArgs& Args)
{
	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			SNew(SWorldBuilderTemplatesPanel)
		];
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FWorldBuilderTemplatesEditorModule, WorldBuilderTemplatesEditor);
