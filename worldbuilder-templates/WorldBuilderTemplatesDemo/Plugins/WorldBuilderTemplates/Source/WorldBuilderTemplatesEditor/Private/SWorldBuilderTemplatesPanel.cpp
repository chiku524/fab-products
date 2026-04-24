// Copyright (c) Immersive Labs. All Rights Reserved.

#include "SWorldBuilderTemplatesPanel.h"

#include "AssetRegistry/ARFilter.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "Editor.h"
#include "FileHelpers.h"
#include "UnrealEdGlobals.h"
#include "WorldBuilderTemplatesSampleMapBuilder.h"
#include "WorldBuilderTemplatesSettings.h"
#include "WorldBuilderTemplateRecipe.h"
#include "Framework/Notifications/NotificationManager.h"
#include "Interfaces/IPluginManager.h"
#include "Modules/ModuleManager.h"
#include "Widgets/Input/SButton.h"
#include "Widgets/Input/SCheckBox.h"
#include "Widgets/Input/SComboBox.h"
#include "Widgets/Input/SNumericEntryBox.h"
#include "Widgets/Layout/SScrollBox.h"
#include "Widgets/Notifications/SNotificationList.h"
#include "Widgets/Text/STextBlock.h"
#include "Widgets/Views/SListView.h"
#include "Widgets/Views/STableRow.h"
#include "Engine/World.h"
#include "Styling/AppStyle.h"
#include "UObject/TopLevelAssetPath.h"
#include "UObject/Package.h"

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
	ProceduralKindOptions = {
		MakeShared<FString>(TEXT("Outdoor")),
		MakeShared<FString>(TEXT("Indoor blockout")),
		MakeShared<FString>(TEXT("Ocean / coast")),
		MakeShared<FString>(TEXT("City / plaza")),
	};
	CurrentProceduralKindLabel = ProceduralKindOptions[0];
	ProceduralKind = EWorldBuilderTemplateKind::Outdoor;

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
				SNew(STextBlock)
				.AutoWrapText(true)
				.Text(LOCTEXT(
					"ProceduralIntro",
					"Procedural generation: build a new blank map from a layout preset. Change the seed for different random placements "
					"(rocks, scattered trees, city variation). Create a World Builder Template Recipe data asset to save tuned parameters."))
			]
			+ SVerticalBox::Slot()
			.AutoHeight()
			.Padding(8.0f, 0.0f, 8.0f, 8.0f)
			[
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
				.AutoWidth()
				.VAlign(VAlign_Center)
				.Padding(0.f, 0.f, 6.f, 0.f)
				[
					SNew(STextBlock)
					.Text(LOCTEXT("KindLabel", "Kind"))
				]
				+ SHorizontalBox::Slot()
				.FillWidth(1.f)
				.Padding(0.f, 0.f, 8.f, 0.f)
				[
					SNew(SComboBox<TSharedPtr<FString>>)
					.OptionsSource(&ProceduralKindOptions)
					.InitiallySelectedItem(ProceduralKindOptions[0])
					.OnSelectionChanged(this, &SWorldBuilderTemplatesPanel::OnProceduralKindChanged)
					.OnGenerateWidget_Lambda([](TSharedPtr<FString> Item)
					{
						return SNew(STextBlock).Text(FText::FromString(Item.IsValid() ? *Item : FString()));
					})
					[
						SNew(STextBlock)
						.Text_Lambda([this]()
						{
							return FText::FromString(CurrentProceduralKindLabel.IsValid() ? *CurrentProceduralKindLabel : FString(TEXT("Outdoor")));
						})
					]
				]
				+ SHorizontalBox::Slot()
				.AutoWidth()
				.VAlign(VAlign_Center)
				.Padding(0.f, 0.f, 6.f, 0.f)
				[
					SNew(STextBlock)
					.Text(LOCTEXT("SeedLabel", "Seed"))
				]
				+ SHorizontalBox::Slot()
				.AutoWidth()
				.Padding(0.f, 0.f, 8.f, 0.f)
				[
					SNew(SNumericEntryBox<int32>)
					.MinValue(0)
					.MaxValue(2147483647)
					.Value_Lambda([this]() { return ProceduralSeed; })
					.OnValueChanged_Lambda([this](int32 V) { ProceduralSeed = V; })
				]
				+ SHorizontalBox::Slot()
				.AutoWidth()
				.Padding(0.f, 0.f, 4.f, 0.f)
				[
					SNew(SButton)
					.Text(LOCTEXT("RandomSeed", "Random seed"))
					.OnClicked(this, &SWorldBuilderTemplatesPanel::OnRandomizeSeedClicked)
				]
				+ SHorizontalBox::Slot()
				.AutoWidth()
				[
					SNew(SButton)
					.Text(LOCTEXT("GenerateProcedural", "Generate new blank map"))
					.OnClicked(this, &SWorldBuilderTemplatesPanel::OnGenerateProceduralMap)
				]
			]
			+ SVerticalBox::Slot()
			.AutoHeight()
			.Padding(8.0f, 0.0f, 8.0f, 8.0f)
			[
				SNew(SCheckBox)
				.Visibility_Lambda([this]()
				{
					return ProceduralKind == EWorldBuilderTemplateKind::Outdoor ? EVisibility::Visible : EVisibility::Collapsed;
				})
				.IsChecked_Lambda([this]()
				{
					return bOutdoorScatterTrees ? ECheckBoxState::Checked : ECheckBoxState::Unchecked;
				})
				.OnCheckStateChanged_Lambda([this](ECheckBoxState S)
				{
					bOutdoorScatterTrees = (S == ECheckBoxState::Checked);
				})
				[
					SNew(STextBlock)
					.Text(LOCTEXT("ScatterTrees", "Outdoor: scatter trees (uses seed instead of fixed anchors)"))
				]
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

void SWorldBuilderTemplatesPanel::OnProceduralKindChanged(TSharedPtr<FString> NewSelection, ESelectInfo::Type SelectInfo)
{
	(void)SelectInfo;
	if (!NewSelection.IsValid())
	{
		return;
	}
	CurrentProceduralKindLabel = NewSelection;
	for (int32 i = 0; i < ProceduralKindOptions.Num(); ++i)
	{
		if (ProceduralKindOptions[i] == NewSelection)
		{
			ProceduralKind = static_cast<EWorldBuilderTemplateKind>(i);
			break;
		}
	}
}

FReply SWorldBuilderTemplatesPanel::OnRandomizeSeedClicked()
{
	ProceduralSeed = FMath::Rand() & 0x7FFFFFFF;
	if (ProceduralSeed == 0)
	{
		ProceduralSeed = 1;
	}
	return FReply::Handled();
}

FReply SWorldBuilderTemplatesPanel::OnGenerateProceduralMap()
{
	if (!GEditor)
	{
		PushNotification(LOCTEXT("NoEditor", "Editor not available."), false);
		return FReply::Handled();
	}

	UWorld* World = UEditorLoadingAndSavingUtils::NewBlankMap(false);
	if (!World)
	{
		PushNotification(LOCTEXT("NoWorld", "Could not create a blank map."), false);
		return FReply::Handled();
	}

	UWorldBuilderTemplateRecipe* Recipe = NewObject<UWorldBuilderTemplateRecipe>(GetTransientPackage(), NAME_None, RF_Transient);
	Recipe->TemplateKind = ProceduralKind;
	Recipe->Seed = ProceduralSeed;
	if (ProceduralKind == EWorldBuilderTemplateKind::Outdoor && bOutdoorScatterTrees)
	{
		Recipe->Outdoor.bUseFixedTreePositions = false;
	}

	WorldBuilderTemplatesSampleMapBuilder::ApplyRecipe(World, Recipe);
	World->MarkPackageDirty();
	PushNotification(LOCTEXT("GenOk", "Generated procedural scene on a new blank map. Save when ready."), true);
	return FReply::Handled();
}

#undef LOCTEXT_NAMESPACE
