// Copyright (c) Immersive Labs. All Rights Reserved.

#include "SWorldBuilderTemplatesPanel.h"

#include "AssetRegistry/ARFilter.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "Editor.h"
#include "FileHelpers.h"
#include "WorldBuilderTemplatesSettings.h"
#include "Framework/Notifications/NotificationManager.h"
#include "Interfaces/IPluginManager.h"
#include "Modules/ModuleManager.h"
#include "Widgets/Input/SButton.h"
#include "Widgets/Layout/SScrollBox.h"
#include "Widgets/Notifications/SNotificationList.h"
#include "Widgets/Text/STextBlock.h"
#include "Widgets/Views/SListView.h"
#include "Widgets/Views/STableRow.h"
#include "Engine/World.h"
#include "Styling/AppStyle.h"
#include "UObject/TopLevelAssetPath.h"

namespace
{
	FString NormalizePackageRoot(FString InPath)
	{
		InPath.TrimStartAndEndInline();
		while (InPath.Len() > 1 && InPath.EndsWith(TEXT("/")))
		{
			InPath.LeftChopInline(1, EAllowShrinking::No);
		}
		return InPath;
	}

	bool IsAllowedPackageRoot(const FString& InPath)
	{
		return InPath.StartsWith(TEXT("/")) && !InPath.Contains(TEXT(".."));
	}
}

#define LOCTEXT_NAMESPACE "SWorldBuilderTemplatesPanel"

void SWorldBuilderTemplatesPanel::Construct(const FArguments& InArgs)
{
	ChildSlot
		[
			SNew(SVerticalBox)
			+ SVerticalBox::Slot()
			.AutoHeight()
			.Padding(8.0f)
			[
				SNew(STextBlock)
				.AutoWrapText(true)
				.Text(LOCTEXT(
					"Intro",
					"Pick a template, then use Replace current level (or double-click a row) to load it as the active editor map. "
					"Unreal may prompt you to save the level you already have open."))
			]
			+ SVerticalBox::Slot()
			.AutoHeight()
			.Padding(8.0f, 0.0f, 8.0f, 8.0f)
			[
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
				.AutoWidth()
				[
					SNew(SButton)
					.Text(LOCTEXT("RefreshList", "Refresh list"))
					.OnClicked(this, &SWorldBuilderTemplatesPanel::OnRefreshClicked)
				]
			]
			+ SVerticalBox::Slot()
			.AutoHeight()
			.Padding(8.0f, 0.0f, 8.0f, 8.0f)
			[
				SNew(STextBlock)
				.Visibility_Lambda([this]()
				{
					return TemplateItems.Num() == 0 ? EVisibility::Visible : EVisibility::Collapsed;
				})
				.AutoWrapText(true)
				.Text(LOCTEXT(
					"EmptyHelp",
					"No template maps were found. Add .umap files under this plugin's Content folder, adjust "
					"Project Settings → Plugins → World Builder Templates (extra package path roots), "
					"then click Refresh list."))
			]
			+ SVerticalBox::Slot()
			.FillHeight(1.0f)
			.Padding(4.0f, 0.0f, 4.0f, 4.0f)
			[
				SNew(SScrollBox)
				+ SScrollBox::Slot()
				[
					SAssignNew(TemplateListView, SListView<TSharedPtr<FWorldTemplateListItem>>)
					.ListItemsSource(&TemplateItems)
					.SelectionMode(ESelectionMode::Single)
					.OnGenerateRow(this, &SWorldBuilderTemplatesPanel::OnGenerateTemplateRow)
					.OnMouseButtonDoubleClick_Lambda([this](TSharedPtr<FWorldTemplateListItem> Item)
					{
						if (Item.IsValid())
						{
							OnReplaceCurrentLevel(Item);
						}
					})
				]
			]
		];

	RefreshTemplateList();
}

void SWorldBuilderTemplatesPanel::RefreshTemplateList()
{
	TemplateItems.Reset();

	const TSharedPtr<IPlugin> Plugin = IPluginManager::Get().FindPlugin(TEXT("WorldBuilderTemplates"));
	if (!Plugin.IsValid())
	{
		if (TemplateListView.IsValid())
		{
			TemplateListView->RequestListRefresh();
		}
		return;
	}

	TArray<FString> Roots;
	FString MountPath = NormalizePackageRoot(Plugin->GetMountedAssetPath());
	if (IsAllowedPackageRoot(MountPath))
	{
		Roots.Add(MountPath);
	}

	const UWorldBuilderTemplatesSettings* Settings = GetDefault<UWorldBuilderTemplatesSettings>();
	if (Settings)
	{
		for (FString Extra : Settings->ExtraPackagePathRoots)
		{
			Extra = NormalizePackageRoot(Extra);
			if (!IsAllowedPackageRoot(Extra))
			{
				continue;
			}
			Roots.AddUnique(Extra);
		}
	}

	FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>(TEXT("AssetRegistry"));
	IAssetRegistry& AssetRegistry = AssetRegistryModule.Get();

	AssetRegistry.ScanPathsSynchronous(Roots, true);

	TSet<FName> SeenPackages;

	for (const FString& Root : Roots)
	{
		FARFilter Filter;
		Filter.bRecursivePaths = true;
		Filter.ClassPaths.Add(FTopLevelAssetPath(UWorld::StaticClass()));
		Filter.PackagePaths.Add(FName(*Root));

		TArray<FAssetData> Assets;
		AssetRegistry.GetAssets(Filter, Assets);

		for (FAssetData& Asset : Assets)
		{
			if (!Asset.IsValid() || Asset.IsRedirector())
			{
				continue;
			}

			const FName Pkg = Asset.PackageName;
			if (SeenPackages.Contains(Pkg))
			{
				continue;
			}
			SeenPackages.Add(Pkg);
			TemplateItems.Add(MakeShared<FWorldTemplateListItem>(MoveTemp(Asset)));
		}
	}

	TemplateItems.Sort([](const TSharedPtr<FWorldTemplateListItem>& A, const TSharedPtr<FWorldTemplateListItem>& B)
	{
		return A->Asset.AssetName.LexicalLess(B->Asset.AssetName);
	});

	if (TemplateListView.IsValid())
	{
		TemplateListView->RequestListRefresh();
	}
}

FReply SWorldBuilderTemplatesPanel::OnRefreshClicked()
{
	RefreshTemplateList();
	PushNotification(LOCTEXT("Refreshed", "Template list refreshed."), true);
	return FReply::Handled();
}

FReply SWorldBuilderTemplatesPanel::OnReplaceCurrentLevel(TSharedPtr<FWorldTemplateListItem> Item)
{
	if (!Item.IsValid())
	{
		return FReply::Handled();
	}

	const FString PackageName = Item->Asset.PackageName.ToString();
	const bool bOk = FEditorFileUtils::LoadMap(PackageName, false, true);
	if (bOk)
	{
		PushNotification(
			FText::Format(
				LOCTEXT("ReplacedLevelFmt", "Loaded '{0}' as the current level (replaced the previous map)."),
				FText::FromName(Item->Asset.AssetName)),
			true);
	}
	else
	{
		PushNotification(
			FText::Format(
				LOCTEXT("ReplaceLevelFailedFmt", "Could not load '{0}'. Save or discard changes to the current map if prompted, then try again."),
				FText::FromName(Item->Asset.AssetName)),
			false);
	}

	return FReply::Handled();
}

TSharedRef<ITableRow> SWorldBuilderTemplatesPanel::OnGenerateTemplateRow(
	TSharedPtr<FWorldTemplateListItem> Item,
	const TSharedRef<STableViewBase>& OwnerTable)
{
	check(Item.IsValid());

	const FText Title = FText::FromName(Item->Asset.AssetName);
	const FText Tooltip = FText::FromString(Item->Asset.GetObjectPathString());

	return SNew(STableRow<TSharedPtr<FWorldTemplateListItem>>, OwnerTable)
		.Padding(FMargin(4.0f, 2.0f))
		.ToolTipText(Tooltip)
		[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot()
			.FillWidth(1.0f)
			.VAlign(VAlign_Center)
			.Padding(4.0f, 0.0f)
			[
				SNew(STextBlock)
				.Text(Title)
			]
			+ SHorizontalBox::Slot()
			.AutoWidth()
			.Padding(2.0f, 0.0f)
			[
				SNew(SButton)
				.Text(LOCTEXT("ReplaceCurrentLevel", "Replace current level"))
				.ToolTipText(LOCTEXT("ReplaceCurrentLevelTip", "Load this map as the active editor level, replacing the map you have open. You may be prompted to save."))
				.OnClicked_Lambda([this, Item]()
				{
					return OnReplaceCurrentLevel(Item);
				})
			]
		];
}

void SWorldBuilderTemplatesPanel::PushNotification(const FText& Message, bool bSuccess) const
{
	FNotificationInfo Info(Message);
	Info.ExpireDuration = 4.0f;
	Info.bUseLargeFont = false;
	Info.bFireAndForget = true;
	Info.bUseSuccessFailIcons = true;
	Info.Image = bSuccess ? FAppStyle::Get().GetBrush(TEXT("NotificationList.SuccessImage")) : FAppStyle::Get().GetBrush(TEXT("NotificationList.FailImage"));

	FSlateNotificationManager::Get().AddNotification(Info);
}

#undef LOCTEXT_NAMESPACE
