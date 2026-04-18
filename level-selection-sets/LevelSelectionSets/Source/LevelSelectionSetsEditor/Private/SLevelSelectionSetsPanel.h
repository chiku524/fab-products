// Copyright (c) [PUBLISHER_NAME]. All Rights Reserved.

#pragma once

#include "Misc/Optional.h"
#include "Widgets/SCompoundWidget.h"

class SLevelSelectionSetsPanel : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SLevelSelectionSetsPanel) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);

	virtual void ReleaseSlateResources(bool bReleaseChildren) override;

private:
	void HandleMapChange(uint32 MapChangeFlags);
	void RefreshFromWorld();
	void RefreshList();

	EVisibility GetRenameStripVisibility() const;

	FReply OnSaveFromSelection();
	FReply OnRecallSet(FName SetName);
	FReply OnDeleteSet(FName SetName);
	FReply OnRenameSet(FName SetName);
	FReply OnApplyRename();
	FReply OnCancelRename();

	void PushNotification(const FText& Message, bool bSuccess) const;

	TSharedPtr<class SVerticalBox> ListBox;
	TSharedPtr<class SEditableTextBox> NewSetNameBox;
	TSharedPtr<class SEditableTextBox> RenameValueBox;

	TOptional<FName> PendingRenameFrom;

	FDelegateHandle MapChangeHandle;
};
