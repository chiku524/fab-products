// Copyright (c) Immersive Labs. All Rights Reserved.

#pragma once

#include "AssetRegistry/AssetData.h"
#include "Widgets/SCompoundWidget.h"
#include "Widgets/Views/SListView.h"

class STableViewBase;

struct FWorldTemplateListItem
{
	explicit FWorldTemplateListItem(FAssetData InAsset)
		: Asset(MoveTemp(InAsset))
	{
	}

	FAssetData Asset;
};

class SWorldBuilderTemplatesPanel : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SWorldBuilderTemplatesPanel) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);

private:
	void RefreshTemplateList();
	FReply OnRefreshClicked();

	/** LoadMap(LoadAsTemplate=false): replaces the editor's current level with this map asset. */
	FReply OnReplaceCurrentLevel(TSharedPtr<FWorldTemplateListItem> Item);

	TSharedRef<ITableRow> OnGenerateTemplateRow(
		TSharedPtr<FWorldTemplateListItem> Item,
		const TSharedRef<STableViewBase>& OwnerTable);

	void PushNotification(const FText& Message, bool bSuccess) const;

	TSharedPtr<SListView<TSharedPtr<FWorldTemplateListItem>>> TemplateListView;
	TArray<TSharedPtr<FWorldTemplateListItem>> TemplateItems;
};
