// Copyright (c) Immersive Labs. All Rights Reserved.

#include "HarborSuiteEditorStyle.h"

#include "Brushes/SlateImageBrush.h"
#include "HarborSuiteConstants.h"
#include "Interfaces/IPluginManager.h"
#include "Styling/SlateStyle.h"
#include "Styling/SlateStyleRegistry.h"

static TSharedPtr<FSlateStyleSet> HarborSuiteStyleSet;

const FVector2D FHarborSuiteEditorStyle::Icon16(16.0, 16.0);
const FName FHarborSuiteEditorStyle::TabIconName(TEXT("HarborSuite.TabIcon"));
const FName FHarborSuiteEditorStyle::TabIconSmallName(TEXT("HarborSuite.TabIconSmall"));

const FName& FHarborSuiteEditorStyle::GetStyleSetName()
{
	static const FName StyleName(TEXT("HarborSuiteEditorStyle"));
	return StyleName;
}

void FHarborSuiteEditorStyle::Register()
{
	if (HarborSuiteStyleSet.IsValid())
	{
		return;
	}

	const TSharedPtr<IPlugin> Plugin = IPluginManager::Get().FindPlugin(TEXT("HarborSuite"));
	if (!Plugin.IsValid())
	{
		return;
	}

	HarborSuiteStyleSet = MakeShared<FSlateStyleSet>(GetStyleSetName());
	HarborSuiteStyleSet->SetContentRoot(Plugin->GetBaseDir() / TEXT("Resources"));

	HarborSuiteStyleSet->Set(
		TabIconName,
		new FSlateImageBrush(HarborSuiteStyleSet->RootToContentDir(TEXT("Icon128"), TEXT(".png")), Icon16));
	HarborSuiteStyleSet->Set(
		TabIconSmallName,
		new FSlateImageBrush(HarborSuiteStyleSet->RootToContentDir(TEXT("Icon128"), TEXT(".png")), Icon16));

	FSlateStyleRegistry::RegisterSlateStyle(*HarborSuiteStyleSet);
}

void FHarborSuiteEditorStyle::Unregister()
{
	if (HarborSuiteStyleSet.IsValid())
	{
		FSlateStyleRegistry::UnRegisterSlateStyle(*HarborSuiteStyleSet);
		HarborSuiteStyleSet.Reset();
	}
}
