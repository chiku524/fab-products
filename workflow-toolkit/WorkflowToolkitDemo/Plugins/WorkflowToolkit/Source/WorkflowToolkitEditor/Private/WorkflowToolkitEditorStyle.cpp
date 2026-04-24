// Copyright (c) Immersive Labs. All Rights Reserved.

#include "WorkflowToolkitEditorStyle.h"

#include "Brushes/SlateImageBrush.h"
#include "Styling/AppStyle.h"
#include "Brushes/SlateRoundedBoxBrush.h"
#include "Interfaces/IPluginManager.h"
#include "Styling/SlateStyle.h"
#include "Styling/SlateStyleRegistry.h"
#include "Styling/StyleColors.h"

static TSharedPtr<FSlateStyleSet> StyleSet;

const FName FWorkflowToolkitEditorStyle::TabIconName(TEXT("WorkflowToolkit.TabIcon"));
const FName FWorkflowToolkitEditorStyle::TabIconSmallName(TEXT("WorkflowToolkit.TabIconSmall"));

const FName FWorkflowToolkitEditorStyle::PageBackgroundBrushName(TEXT("WorkflowToolkit.PageBackground"));
const FName FWorkflowToolkitEditorStyle::CardSurfaceBrushName(TEXT("WorkflowToolkit.CardSurface"));
const FName FWorkflowToolkitEditorStyle::HeroCardBrushName(TEXT("WorkflowToolkit.HeroCard"));
const FName FWorkflowToolkitEditorStyle::ConsoleCardBrushName(TEXT("WorkflowToolkit.ConsoleCard"));
const FName FWorkflowToolkitEditorStyle::InfoCardBrushName(TEXT("WorkflowToolkit.InfoCard"));

const FName& FWorkflowToolkitEditorStyle::GetStyleSetName()
{
	static const FName StyleName(TEXT("WorkflowToolkitEditorStyle"));
	return StyleName;
}

void FWorkflowToolkitEditorStyle::Register()
{
	if (StyleSet.IsValid())
	{
		return;
	}

	const TSharedPtr<IPlugin> Plugin = IPluginManager::Get().FindPlugin(TEXT("WorkflowToolkit"));
	if (!Plugin.IsValid())
	{
		return;
	}

	StyleSet = MakeShared<FSlateStyleSet>(GetStyleSetName());
	StyleSet->SetContentRoot(Plugin->GetBaseDir() / TEXT("Resources"));

	const FVector2D MenuIcon(16.0, 16.0);
	StyleSet->Set(
		TabIconName,
		new FSlateImageBrush(StyleSet->RootToContentDir(TEXT("Icon128"), TEXT(".png")), MenuIcon));
	StyleSet->Set(
		TabIconSmallName,
		new FSlateImageBrush(StyleSet->RootToContentDir(TEXT("Icon128"), TEXT(".png")), MenuIcon));

	// Theme-aware surfaces (FStyleColors follow the active editor theme / Starship colors).
	StyleSet->Set(
		PageBackgroundBrushName,
		new FSlateRoundedBoxBrush(FStyleColors::Recessed, 8.0f));
	StyleSet->Set(
		CardSurfaceBrushName,
		new FSlateRoundedBoxBrush(FStyleColors::Panel, 8.0f, FStyleColors::InputOutline, 1.0f));
	StyleSet->Set(
		HeroCardBrushName,
		new FSlateRoundedBoxBrush(FStyleColors::Header, 10.0f, FStyleColors::AccentBlue, 1.5f));
	StyleSet->Set(
		ConsoleCardBrushName,
		new FSlateRoundedBoxBrush(FStyleColors::Input, 8.0f, FStyleColors::InputOutline, 1.0f));
	StyleSet->Set(
		InfoCardBrushName,
		new FSlateRoundedBoxBrush(FStyleColors::Secondary, 8.0f, FStyleColors::AccentGray, 1.0f));

	FSlateStyleRegistry::RegisterSlateStyle(*StyleSet);
}

const FSlateBrush* FWorkflowToolkitEditorStyle::GetBrush(FName BrushName)
{
	if (StyleSet.IsValid())
	{
		return StyleSet->GetBrush(BrushName);
	}
	return FAppStyle::Get().GetBrush("ToolPanel.GroupBorder");
}

void FWorkflowToolkitEditorStyle::Unregister()
{
	if (StyleSet.IsValid())
	{
		FSlateStyleRegistry::UnRegisterSlateStyle(*StyleSet);
		StyleSet.Reset();
	}
}
