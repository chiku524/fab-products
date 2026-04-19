// Copyright (c) Immersive Labs. All Rights Reserved.

#include "WorldBuilderTemplatesCreateSampleMapsCommandlet.h"

#include "WorldBuilderTemplatesSampleMapBuilder.h"

#include "Editor.h"
#include "Engine/World.h"
#include "FileHelpers.h"
#include "HAL/FileManager.h"
#include "Interfaces/IPluginManager.h"
#include "CoreGlobals.h"
#include "Misc/PackageName.h"
#include "Misc/Paths.h"

DEFINE_LOG_CATEGORY_STATIC(LogWorldBuilderTemplatesCmd, Log, All);

namespace
{
	struct FSampleTemplateEntry
	{
		const TCHAR* LongPackageName;
		void (*Setup)(UWorld*);
	};

	static const FSampleTemplateEntry GSampleTemplates[] = {
		{TEXT("/WorldBuilderTemplates/Maps/WBT_Template_Outdoor"), &WorldBuilderTemplatesSampleMapBuilder::SetupOutdoor},
		{TEXT("/WorldBuilderTemplates/Maps/WBT_Template_IndoorBlockout"), &WorldBuilderTemplatesSampleMapBuilder::SetupIndoorBlockout},
		{TEXT("/WorldBuilderTemplates/Maps/WBT_Template_Ocean"), &WorldBuilderTemplatesSampleMapBuilder::SetupOcean},
		{TEXT("/WorldBuilderTemplates/Maps/WBT_Template_City"), &WorldBuilderTemplatesSampleMapBuilder::SetupCity},
	};
}

UWorldBuilderTemplatesCreateSampleMapsCommandlet::UWorldBuilderTemplatesCreateSampleMapsCommandlet()
{
	IsEditor = true;
	IsClient = false;
	IsServer = false;
	LogToConsole = true;
}

int32 UWorldBuilderTemplatesCreateSampleMapsCommandlet::Main(const FString& Params)
{
	TGuardValue<bool> UnattendedGuard(GIsRunningUnattendedScript, true);

	const TSharedPtr<IPlugin> Plugin = IPluginManager::Get().FindPlugin(TEXT("WorldBuilderTemplates"));
	if (!Plugin.IsValid())
	{
		UE_LOG(LogWorldBuilderTemplatesCmd, Error, TEXT("WorldBuilderTemplates plugin is not loaded."));
		return 1;
	}

	const FString ContentDir = Plugin->GetContentDir();
	const FString MapsDir = FPaths::Combine(ContentDir, TEXT("Maps"));
	IFileManager::Get().MakeDirectory(*MapsDir, true);

	int32 Failures = 0;

	for (const FSampleTemplateEntry& Entry : GSampleTemplates)
	{
		FString DiskFilename;
		if (!FPackageName::TryConvertLongPackageNameToFilename(Entry.LongPackageName, DiskFilename, FPackageName::GetMapPackageExtension()))
		{
			UE_LOG(LogWorldBuilderTemplatesCmd, Error, TEXT("Invalid long package name: %s"), Entry.LongPackageName);
			++Failures;
			continue;
		}

		IFileManager::Get().MakeDirectory(*FPaths::GetPath(DiskFilename), true);

		UWorld* World = UEditorLoadingAndSavingUtils::NewBlankMap(false);
		if (!World)
		{
			UE_LOG(LogWorldBuilderTemplatesCmd, Error, TEXT("NewBlankMap failed before saving %s"), Entry.LongPackageName);
			++Failures;
			continue;
		}

		if (Entry.Setup)
		{
			Entry.Setup(World);
		}

		World->MarkPackageDirty();

		if (!FEditorFileUtils::SaveLevel(World->PersistentLevel, DiskFilename, nullptr))
		{
			UE_LOG(LogWorldBuilderTemplatesCmd, Error, TEXT("SaveLevel failed for %s (%s)"), Entry.LongPackageName, *DiskFilename);
			++Failures;
			continue;
		}

		UE_LOG(LogWorldBuilderTemplatesCmd, Display, TEXT("Wrote sample map: %s -> %s"), Entry.LongPackageName, *DiskFilename);
	}

	return Failures > 0 ? 2 : 0;
}
