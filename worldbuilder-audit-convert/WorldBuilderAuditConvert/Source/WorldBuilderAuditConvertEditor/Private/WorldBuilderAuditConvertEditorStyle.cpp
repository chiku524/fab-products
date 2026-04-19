// Copyright (c) Immersive Labs. All Rights Reserved.

#include "WorldBuilderAuditConvertEditorStyle.h"

#include "Interfaces/IPluginManager.h"
#include "Styling/SlateStyle.h"
#include "Styling/SlateStyleMacros.h"
#include "Styling/SlateStyleRegistry.h"

static TSharedPtr<FSlateStyleSet> StyleSet;

const FName FWorldBuilderAuditConvertEditorStyle::TabIconName(TEXT("WorldBuilderAuditConvert.TabIcon"));
const FName FWorldBuilderAuditConvertEditorStyle::TabIconSmallName(TEXT("WorldBuilderAuditConvert.TabIconSmall"));

const FName& FWorldBuilderAuditConvertEditorStyle::GetStyleSetName()
{
	static const FName StyleName(TEXT("WorldBuilderAuditConvertEditorStyle"));
	return StyleName;
}

void FWorldBuilderAuditConvertEditorStyle::Register()
{
	if (StyleSet.IsValid())
	{
		return;
	}

	const TSharedPtr<IPlugin> Plugin = IPluginManager::Get().FindPlugin(TEXT("WorldBuilderAuditConvert"));
	if (!Plugin.IsValid())
	{
		return;
	}

	StyleSet = MakeShared<FSlateStyleSet>(GetStyleSetName());
	StyleSet->SetContentRoot(Plugin->GetBaseDir() / TEXT("Resources"));

	const FVector2D MenuIcon(16.0, 16.0);
	StyleSet->Set(TabIconName, new IMAGE_BRUSH(TEXT("Icon128"), MenuIcon));
	StyleSet->Set(TabIconSmallName, new IMAGE_BRUSH(TEXT("Icon128"), MenuIcon));

	FSlateStyleRegistry::RegisterSlateStyle(*StyleSet);
}

void FWorldBuilderAuditConvertEditorStyle::Unregister()
{
	if (StyleSet.IsValid())
	{
		FSlateStyleRegistry::UnRegisterSlateStyle(*StyleSet);
		StyleSet.Reset();
	}
}
