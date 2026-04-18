// Copyright (c) Immersive Labs. All Rights Reserved.

#include "SLevelSelectionSetsPanel.h"

#include "Editor.h"
#include "EngineUtils.h"
#include "ScopedTransaction.h"
#include "Framework/Notifications/NotificationManager.h"
#include "LevelSelectionSetsDataActor.h"
#include "LevelSelectionSetsTypes.h"
#include "Selection.h"
#include "Widgets/Input/SButton.h"
#include "Widgets/Input/SEditableTextBox.h"
#include "Widgets/Layout/SBorder.h"
#include "Widgets/Layout/SScrollBox.h"
#include "Widgets/Notifications/SNotificationList.h"
#include "Widgets/Text/STextBlock.h"

#define LOCTEXT_NAMESPACE "SLevelSelectionSetsPanel"

namespace LevelSelectionSetsPanelHelpers
{
	static UWorld* GetEditorWorld()
	{
		if (!GEditor)
		{
			return nullptr;
		}

		return GEditor->GetEditorWorldContext().World();
	}

	static AActor* FindActorByGuid(UWorld* World, const FGuid& Guid)
	{
		if (!World)
		{
			return nullptr;
		}

		for (TActorIterator<AActor> It(World); It; ++It)
		{
			AActor* Actor = *It;
			if (Actor && Actor->GetActorGuid() == Guid)
			{
				return Actor;
			}
		}

		return nullptr;
	}

	static void CollectGuidsFromSelection(TArray<FGuid>& OutGuids)
	{
		OutGuids.Reset();

		if (!GEditor)
		{
			return;
		}

		USelection* SelectedActors = GEditor->GetSelectedActors();
		if (!SelectedActors)
		{
			return;
		}

		for (FSelectionIterator It(*SelectedActors); It; ++It)
		{
			if (AActor* Actor = Cast<AActor>(*It))
			{
				const FGuid Guid = Actor->GetActorGuid();
				OutGuids.Add(Guid);
			}
		}
	}
}

void SLevelSelectionSetsPanel::Construct(const FArguments& InArgs)
{
	ChildSlot
	[
		SNew(SScrollBox)
		+ SScrollBox::Slot()
		[
			SNew(SVerticalBox)
			+ SVerticalBox::Slot()
			.AutoHeight()
			.Padding(4.f)
			[
				SNew(STextBlock)
				.Text(LOCTEXT("Help", "Save the current selection under a name, then recall it later. Data is stored in the level (editor-only actor)."))
				.WrapTextAt(360.f)
			]
			+ SVerticalBox::Slot()
			.AutoHeight()
			.Padding(4.f)
			[
				SNew(SHorizontalBox)
				.Visibility(this, &SLevelSelectionSetsPanel::GetRenameStripVisibility)
				+ SHorizontalBox::Slot()
				.FillWidth(1.f)
				.Padding(0.f, 0.f, 4.f, 0.f)
				[
					SAssignNew(RenameValueBox, SEditableTextBox)
					.HintText(LOCTEXT("RenameHint", "New name"))
				]
				+ SHorizontalBox::Slot()
				.AutoWidth()
				.Padding(2.f, 0.f)
				[
					SNew(SButton)
					.Text(LOCTEXT("ApplyRename", "Apply"))
					.OnClicked(this, &SLevelSelectionSetsPanel::OnApplyRename)
				]
				+ SHorizontalBox::Slot()
				.AutoWidth()
				.Padding(2.f, 0.f)
				[
					SNew(SButton)
					.Text(LOCTEXT("CancelRename", "Cancel"))
					.OnClicked(this, &SLevelSelectionSetsPanel::OnCancelRename)
				]
			]
			+ SVerticalBox::Slot()
			.AutoHeight()
			.Padding(4.f)
			[
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
				.FillWidth(1.f)
				.Padding(0.f, 0.f, 4.f, 0.f)
				[
					SAssignNew(NewSetNameBox, SEditableTextBox)
					.HintText(LOCTEXT("NameHint", "Set name"))
				]
				+ SHorizontalBox::Slot()
				.AutoWidth()
				[
					SNew(SButton)
					.Text(LOCTEXT("Save", "Save"))
					.OnClicked(this, &SLevelSelectionSetsPanel::OnSaveFromSelection)
					.ToolTipText(LOCTEXT("SaveTip", "Save the current actor selection under the name above (replaces an existing name)."))
				]
			]
			+ SVerticalBox::Slot()
			.FillHeight(1.f)
			.Padding(4.f)
			[
				SAssignNew(ListBox, SVerticalBox)
			]
		]
	];

	MapChangeHandle = FEditorDelegates::MapChange.AddSP(SharedThis(this), &SLevelSelectionSetsPanel::HandleMapChange);
	RefreshFromWorld();
}

SLevelSelectionSetsPanel::~SLevelSelectionSetsPanel()
{
	if (MapChangeHandle.IsValid())
	{
		FEditorDelegates::MapChange.Remove(MapChangeHandle);
		MapChangeHandle.Reset();
	}
}

void SLevelSelectionSetsPanel::HandleMapChange(uint32 MapChangeFlags)
{
	PendingRenameFrom.Reset();
	RefreshFromWorld();
}

void SLevelSelectionSetsPanel::RefreshFromWorld()
{
	RefreshList();
}

EVisibility SLevelSelectionSetsPanel::GetRenameStripVisibility() const
{
	return PendingRenameFrom.IsSet() ? EVisibility::Visible : EVisibility::Collapsed;
}

void SLevelSelectionSetsPanel::RefreshList()
{
	if (!ListBox.IsValid())
	{
		return;
	}

	ListBox->ClearChildren();

	UWorld* World = LevelSelectionSetsPanelHelpers::GetEditorWorld();
	if (!World)
	{
		ListBox->AddSlot()
		.AutoHeight()
		[
			SNew(STextBlock)
			.Text(LOCTEXT("NoWorld", "Open a level to use selection sets."))
		];
		return;
	}

	const ALevelSelectionSetsData* Data = ALevelSelectionSetsData::FindInWorld(World);
	if (!Data || Data->GetSets().Num() == 0)
	{
		ListBox->AddSlot()
		.AutoHeight()
		[
			SNew(STextBlock)
			.Text(LOCTEXT("Empty", "No saved sets yet. Select actors, enter a name, and click Save."))
		];
		return;
	}

	for (const FNamedActorSelectionSet& Entry : Data->GetSets())
	{
		const FName SetName = Entry.SetName;

		ListBox->AddSlot()
		.AutoHeight()
		.Padding(0.f, 2.f)
		[
			SNew(SBorder)
			.Padding(4.f)
			[
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
				.FillWidth(1.f)
				.VAlign(VAlign_Center)
				[
					SNew(STextBlock)
					.Text(FText::FromName(SetName))
				]
				+ SHorizontalBox::Slot()
				.AutoWidth()
				.Padding(2.f, 0.f)
				[
					SNew(SButton)
					.Text(LOCTEXT("Recall", "Recall"))
					.OnClicked_Lambda(
						[this, SetName]()
						{
							return OnRecallSet(SetName);
						})
				]
				+ SHorizontalBox::Slot()
				.AutoWidth()
				.Padding(2.f, 0.f)
				[
					SNew(SButton)
					.Text(LOCTEXT("Rename", "Rename"))
					.OnClicked_Lambda(
						[this, SetName]()
						{
							return OnRenameSet(SetName);
						})
				]
				+ SHorizontalBox::Slot()
				.AutoWidth()
				.Padding(2.f, 0.f)
				[
					SNew(SButton)
					.Text(LOCTEXT("Delete", "Delete"))
					.OnClicked_Lambda(
						[this, SetName]()
						{
							return OnDeleteSet(SetName);
						})
				]
			]
		];
	}
}

FReply SLevelSelectionSetsPanel::OnSaveFromSelection()
{
	UWorld* World = LevelSelectionSetsPanelHelpers::GetEditorWorld();
	if (!World)
	{
		PushNotification(LOCTEXT("SaveNoWorld", "No active editor world."), false);
		return FReply::Handled();
	}

	ALevelSelectionSetsData* Data = ALevelSelectionSetsData::FindOrCreateInWorld(World);
	if (!Data)
	{
		PushNotification(LOCTEXT("SaveNoData", "Could not access selection set storage."), false);
		return FReply::Handled();
	}

	FString NameString = NewSetNameBox.IsValid() ? NewSetNameBox->GetText().ToString() : FString();
	NameString.TrimStartAndEndInline();
	if (NameString.IsEmpty())
	{
		PushNotification(LOCTEXT("SaveNoName", "Enter a set name before saving."), false);
		return FReply::Handled();
	}

	TArray<FGuid> Guids;
	LevelSelectionSetsPanelHelpers::CollectGuidsFromSelection(Guids);
	if (Guids.Num() == 0)
	{
		PushNotification(LOCTEXT("SaveNoSelection", "Select one or more actors in the level first."), false);
		return FReply::Handled();
	}

	const int32 SavedCount = Guids.Num();
	const FName SetName(*NameString);

	FScopedTransaction Transaction(LOCTEXT("SaveSelectionSet", "Save Selection Set"));
	Data->UpsertSet(SetName, MoveTemp(Guids));

	PushNotification(
		FText::Format(
			LOCTEXT("SavedFmt", "Saved selection set \"{0}\" ({1} actors)."),
			FText::FromName(SetName),
			FText::AsNumber(SavedCount)),
		true);

	RefreshList();
	return FReply::Handled();
}

FReply SLevelSelectionSetsPanel::OnRecallSet(FName SetName)
{
	UWorld* World = LevelSelectionSetsPanelHelpers::GetEditorWorld();
	if (!World || !GEditor)
	{
		PushNotification(LOCTEXT("RecallNoWorld", "No active editor world."), false);
		return FReply::Handled();
	}

	const ALevelSelectionSetsData* DataConst = ALevelSelectionSetsData::FindInWorld(World);
	if (!DataConst)
	{
		PushNotification(LOCTEXT("RecallNoData", "No saved selection sets for this level."), false);
		RefreshList();
		return FReply::Handled();
	}

	const FNamedActorSelectionSet* Found = DataConst->GetSets().FindByPredicate(
		[&SetName](const FNamedActorSelectionSet& Entry)
		{
			return Entry.SetName == SetName;
		});

	if (!Found)
	{
		PushNotification(LOCTEXT("RecallMissing", "That set no longer exists."), false);
		RefreshList();
		return FReply::Handled();
	}

	GEditor->SelectNone(false, true);

	int32 Resolved = 0;
	int32 Missing = 0;
	for (const FGuid& Guid : Found->ActorGuids)
	{
		if (AActor* Actor = LevelSelectionSetsPanelHelpers::FindActorByGuid(World, Guid))
		{
			GEditor->SelectActor(Actor, true, false);
			++Resolved;
		}
		else
		{
			++Missing;
		}
	}

	GEditor->RedrawAllViewports(true);

	PushNotification(
		FText::Format(
			LOCTEXT("RecallFmt", "Recalled \"{0}\": {1} actors selected, {2} missing."),
			FText::FromName(SetName),
			FText::AsNumber(Resolved),
			FText::AsNumber(Missing)),
		Missing == 0);

	return FReply::Handled();
}

FReply SLevelSelectionSetsPanel::OnDeleteSet(FName SetName)
{
	UWorld* World = LevelSelectionSetsPanelHelpers::GetEditorWorld();
	if (!World)
	{
		return FReply::Handled();
	}

	if (ALevelSelectionSetsData* Data = ALevelSelectionSetsData::FindInWorld(World))
	{
		FScopedTransaction Transaction(LOCTEXT("DeleteSelectionSet", "Delete Selection Set"));
		Data->RemoveSet(SetName);
	}

	if (PendingRenameFrom.IsSet() && PendingRenameFrom.GetValue() == SetName)
	{
		PendingRenameFrom.Reset();
	}

	PushNotification(FText::Format(LOCTEXT("DeletedFmt", "Deleted set \"{0}\"."), FText::FromName(SetName)), true);
	Invalidate(EInvalidateWidgetReason::Layout);
	RefreshList();
	return FReply::Handled();
}

FReply SLevelSelectionSetsPanel::OnRenameSet(FName OldName)
{
	PendingRenameFrom = OldName;
	if (RenameValueBox.IsValid())
	{
		RenameValueBox->SetText(FText::FromName(OldName));
	}

	Invalidate(EInvalidateWidgetReason::Layout);
	return FReply::Handled();
}

FReply SLevelSelectionSetsPanel::OnApplyRename()
{
	UWorld* World = LevelSelectionSetsPanelHelpers::GetEditorWorld();
	if (!World || !PendingRenameFrom.IsSet())
	{
		PendingRenameFrom.Reset();
		Invalidate(EInvalidateWidgetReason::Layout);
		return FReply::Handled();
	}

	ALevelSelectionSetsData* Data = ALevelSelectionSetsData::FindInWorld(World);
	if (!Data)
	{
		PendingRenameFrom.Reset();
		Invalidate(EInvalidateWidgetReason::Layout);
		return FReply::Handled();
	}

	FString NewString = RenameValueBox.IsValid() ? RenameValueBox->GetText().ToString() : FString();
	NewString.TrimStartAndEndInline();
	if (NewString.IsEmpty())
	{
		PushNotification(LOCTEXT("RenameEmpty", "Name was empty; rename canceled."), false);
		return FReply::Handled();
	}

	const FName NewName(*NewString);
	const FName OldName = PendingRenameFrom.GetValue();

	FScopedTransaction Transaction(LOCTEXT("RenameSelectionSet", "Rename Selection Set"));
	if (!Data->RenameSet(OldName, NewName))
	{
		PushNotification(LOCTEXT("RenameFailed", "Rename failed (name may already exist or set was missing)."), false);
		return FReply::Handled();
	}

	PendingRenameFrom.Reset();
	Invalidate(EInvalidateWidgetReason::Layout);
	PushNotification(FText::Format(LOCTEXT("RenamedFmt", "Renamed set to \"{0}\"."), FText::FromName(NewName)), true);
	RefreshList();
	return FReply::Handled();
}

FReply SLevelSelectionSetsPanel::OnCancelRename()
{
	PendingRenameFrom.Reset();
	Invalidate(EInvalidateWidgetReason::Layout);
	return FReply::Handled();
}

void SLevelSelectionSetsPanel::PushNotification(const FText& Message, bool bSuccess) const
{
	FNotificationInfo Info(Message);
	Info.ExpireDuration = bSuccess ? 3.f : 6.f;
	Info.bUseLargeFont = false;
	Info.bUseSuccessFailIcons = true;

	FSlateNotificationManager::Get().AddNotification(Info);
}

#undef LOCTEXT_NAMESPACE
