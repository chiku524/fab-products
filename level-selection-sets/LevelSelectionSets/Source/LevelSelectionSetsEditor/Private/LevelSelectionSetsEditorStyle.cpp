// Copyright (c) Immersive Labs. All Rights Reserved.

#include "LevelSelectionSetsEditorStyle.h"

#include "Brushes/SlateImageBrush.h"
#include "Interfaces/IPluginManager.h"
#include "Styling/SlateStyle.h"
#include "Styling/SlateStyleRegistry.h"

static TSharedPtr<FSlateStyleSet> StyleSet;

const FName FLevelSelectionSetsEditorStyle::TabIconName(TEXT("LevelSelectionSets.TabIcon"));
const FName FLevelSelectionSetsEditorStyle::TabIconSmallName(TEXT("LevelSelectionSets.TabIconSmall"));

const FName& FLevelSelectionSetsEditorStyle::GetStyleSetName()
{
	static const FName StyleName(TEXT("LevelSelectionSetsEditorStyle"));
	return StyleName;
}

void FLevelSelectionSetsEditorStyle::Register()
{
	if (StyleSet.IsValid())
	{
		return;
	}

	const TSharedPtr<IPlugin> Plugin = IPluginManager::Get().FindPlugin(TEXT("LevelSelectionSets"));
	if (!Plugin.IsValid())
	{
		return;
	}

	StyleSet = MakeShared<FSlateStyleSet>(GetStyleSetName());
	StyleSet->SetContentRoot(Plugin->GetBaseDir() / TEXT("Resources"));

	// Window menu / tab strip: 16px matches typical editor menu icons; brush scales from Icon128.png.
	const FVector2D MenuIcon(16.0, 16.0);
	StyleSet->Set(
		TabIconName,
		new FSlateImageBrush(StyleSet->RootToContentDir(TEXT("Icon128"), TEXT(".png")), MenuIcon));
	StyleSet->Set(
		TabIconSmallName,
		new FSlateImageBrush(StyleSet->RootToContentDir(TEXT("Icon128"), TEXT(".png")), MenuIcon));

	FSlateStyleRegistry::RegisterSlateStyle(*StyleSet);
}

void FLevelSelectionSetsEditorStyle::Unregister()
{
	if (StyleSet.IsValid())
	{
		FSlateStyleRegistry::UnRegisterSlateStyle(*StyleSet);
		StyleSet.Reset();
	}
}
