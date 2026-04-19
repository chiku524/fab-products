// Copyright (c) Immersive Labs. All Rights Reserved.

#include "WorldBuilderAuditConvertEditor.h"

#include "Framework/Application/SlateApplication.h"
#include "Framework/Docking/TabManager.h"
#include "Textures/SlateIcon.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Text/STextBlock.h"
#include "WorldBuilderAuditConvertConstants.h"
#include "WorldBuilderAuditConvertEditorStyle.h"
#include "WorkspaceMenuStructure.h"
#include "WorkspaceMenuStructureModule.h"

#define LOCTEXT_NAMESPACE "FWorldBuilderAuditConvertEditorModule"

void FWorldBuilderAuditConvertEditorModule::StartupModule()
{
	FWorldBuilderAuditConvertEditorStyle::Register();

	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(
		WorldBuilderAuditConvert::NomadTabId,
		FOnSpawnTab::CreateRaw(this, &FWorldBuilderAuditConvertEditorModule::SpawnWorldBuilderTab))
		.SetDisplayName(LOCTEXT("TabTitle", "WorldBuilder Audit & Convert"))
		.SetTooltipText(LOCTEXT("TabTooltip", "Audit levels for instancing opportunities and convert repeated meshes (full UI coming in a future release)."))
		.SetGroup(WorkspaceMenu::GetMenuStructure().GetToolsCategory())
		.SetIcon(FSlateIcon(
			FWorldBuilderAuditConvertEditorStyle::GetStyleSetName(),
			FWorldBuilderAuditConvertEditorStyle::TabIconName,
			FWorldBuilderAuditConvertEditorStyle::TabIconSmallName))
		.SetMenuType(ETabSpawnerMenuType::Enabled);
}

void FWorldBuilderAuditConvertEditorModule::ShutdownModule()
{
	if (FSlateApplication::IsInitialized())
	{
		FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(WorldBuilderAuditConvert::NomadTabId);
	}

	FWorldBuilderAuditConvertEditorStyle::Unregister();
}

TSharedRef<SDockTab> FWorldBuilderAuditConvertEditorModule::SpawnWorldBuilderTab(const FSpawnTabArgs& Args)
{
	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			SNew(STextBlock)
			.AutoWrapText(true)
			.Text(LOCTEXT("StubBody", "WorldBuilder Audit & Convert is loaded.\n\nThe full audit and conversion UI will ship in a future update; this panel is for smoke-testing the plugin in your project."))
		];
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FWorldBuilderAuditConvertEditorModule, WorldBuilderAuditConvertEditor);
