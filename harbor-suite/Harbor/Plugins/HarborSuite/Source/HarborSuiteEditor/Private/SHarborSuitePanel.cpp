// Copyright (c) Immersive Labs. All Rights Reserved.

#include "SHarborSuitePanel.h"

#include "Editor.h"
#include "Framework/Notifications/NotificationManager.h"
#include "HarborSuiteActions.h"
#include "HarborSuiteEditorSubsystem.h"
#include "Styling/AppStyle.h"
#include "Widgets/Input/SButton.h"
#include "Widgets/Input/SCheckBox.h"
#include "Widgets/Input/SEditableTextBox.h"
#include "Widgets/Layout/SBorder.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Layout/SScrollBox.h"
#include "Widgets/Layout/SWidgetSwitcher.h"
#include "Widgets/Notifications/SNotificationList.h"
#include "Widgets/SBoxPanel.h"
#include "Widgets/Text/STextBlock.h"

#define LOCTEXT_NAMESPACE "SHarborSuitePanel"

void SHarborSuitePanel::Construct(const FArguments& InArgs)
{
	ChildSlot
	[
		SNew(SBorder)
		.BorderImage(FAppStyle::GetBrush("ToolPanel.GroupBorder"))
		.Padding(10.f)
		[
			SNew(SVerticalBox)
			+ SVerticalBox::Slot()
			.AutoHeight()
			.Padding(0.f, 0.f, 0.f, 10.f)
			[
				SNew(STextBlock)
				.Text(LOCTEXT("Intro", "Harbor Suite — Charts, Stowage, Shakedown, Clearance for small teams."))
				.AutoWrapText(true)
			]
			+ SVerticalBox::Slot()
			.AutoHeight()
			[
				BuildPillarStrip()
			]
			+ SVerticalBox::Slot()
			.FillHeight(1.f)
			.Padding(0.f, 12.f, 0.f, 0.f)
			[
				SAssignNew(PillarSwitcher, SWidgetSwitcher)
				+ SWidgetSwitcher::Slot()
				[
					BuildChartsContent()
				]
				+ SWidgetSwitcher::Slot()
				[
					BuildStowageContent()
				]
				+ SWidgetSwitcher::Slot()
				[
					BuildShakedownContent()
				]
				+ SWidgetSwitcher::Slot()
				[
					BuildClearanceContent()
				]
			]
		]
	];
}

void SHarborSuitePanel::PostInfo(const FText& Message) const
{
	FNotificationInfo Info(Message);
	Info.bUseLargeFont = false;
	Info.ExpireDuration = 3.5f;
	FSlateNotificationManager::Get().AddNotification(Info);
}

FReply SHarborSuitePanel::OnPillarClicked(EHarborPillar Pillar)
{
	ActivePillar = Pillar;
	if (PillarSwitcher.IsValid())
	{
		PillarSwitcher->SetActiveWidgetIndex(static_cast<int32>(Pillar));
	}
	Invalidate(EInvalidateWidgetReason::Paint);
	return FReply::Handled();
}

TSharedRef<SWidget> SHarborSuitePanel::BuildPillarStrip()
{
	const auto PillButton = [this](EHarborPillar Pillar, const FText& Label) -> TSharedRef<SWidget>
	{
		return SNew(SButton)
			.Text(Label)
			.OnClicked(FOnClicked::CreateLambda([this, Pillar]()
			{
				return OnPillarClicked(Pillar);
			}));
	};

	return SNew(SHorizontalBox)
		+ SHorizontalBox::Slot()
		.FillWidth(1.f)
		.Padding(2.f)
		[
			PillButton(EHarborPillar::Charts, LOCTEXT("TabCharts", "Charts"))
		]
		+ SHorizontalBox::Slot()
		.FillWidth(1.f)
		.Padding(2.f)
		[
			PillButton(EHarborPillar::Stowage, LOCTEXT("TabStowage", "Stowage"))
		]
		+ SHorizontalBox::Slot()
		.FillWidth(1.f)
		.Padding(2.f)
		[
			PillButton(EHarborPillar::Shakedown, LOCTEXT("TabShakedown", "Shakedown"))
		]
		+ SHorizontalBox::Slot()
		.FillWidth(1.f)
		.Padding(2.f)
		[
			PillButton(EHarborPillar::Clearance, LOCTEXT("TabClearance", "Clearance"))
		];
}

TSharedRef<SWidget> SHarborSuitePanel::BuildChartsContent()
{
	TSharedRef<SVerticalBox> List = SNew(SVerticalBox);

	if (GEditor)
	{
		if (UHarborSuiteEditorSubsystem* Charts = GEditor->GetEditorSubsystem<UHarborSuiteEditorSubsystem>())
		{
			const int32 Count = Charts->GetStepCount();
			for (int32 i = 0; i < Count; ++i)
			{
				const FText Title = Charts->GetStepTitle(i);
				const FText Hint = Charts->GetStepHint(i);
				const int32 Index = i;

				List->AddSlot()
				.AutoHeight()
				.Padding(0.f, 6.f)
				[
					SNew(SHorizontalBox)
					+ SHorizontalBox::Slot()
					.AutoWidth()
					.VAlign(VAlign_Top)
					.Padding(0.f, 2.f, 8.f, 0.f)
					[
						SNew(SCheckBox)
						.IsChecked_Lambda([Index]() -> ECheckBoxState
						{
							if (GEditor)
							{
								if (const UHarborSuiteEditorSubsystem* S = GEditor->GetEditorSubsystem<UHarborSuiteEditorSubsystem>())
								{
									return S->IsStepDone(Index) ? ECheckBoxState::Checked : ECheckBoxState::Unchecked;
								}
							}
							return ECheckBoxState::Unchecked;
						})
						.OnCheckStateChanged_Lambda([this, Index](ECheckBoxState NewState)
						{
							if (GEditor)
							{
								if (UHarborSuiteEditorSubsystem* S = GEditor->GetEditorSubsystem<UHarborSuiteEditorSubsystem>())
								{
									S->SetStepDone(Index, NewState == ECheckBoxState::Checked);
								}
							}
							Invalidate(EInvalidateWidgetReason::Paint);
						})
					]
					+ SHorizontalBox::Slot()
					.FillWidth(1.f)
					[
						SNew(SVerticalBox)
						+ SVerticalBox::Slot().AutoHeight()
						[
							SNew(STextBlock)
							.Text(Title)
							.Font(FAppStyle::GetFontStyle("NormalFontBold"))
						]
						+ SVerticalBox::Slot().AutoHeight()
						[
							SNew(STextBlock)
							.Text(Hint)
							.AutoWrapText(true)
							.ColorAndOpacity(FSlateColor::UseSubduedForeground())
						]
					]
				];
			}
		}
	}

	return SNew(SScrollBox)
		+ SScrollBox::Slot()
		[
			SNew(SVerticalBox)
			+ SVerticalBox::Slot()
			.AutoHeight()
			[
				SNew(STextBlock)
				.Text(LOCTEXT("ChartsTitle", "Charts — Vertical Slice Gate"))
				.Font(FAppStyle::GetFontStyle("HeadingExtraSmall"))
			]
			+ SVerticalBox::Slot()
			.AutoHeight()
			.Padding(0.f, 8.f)
			[
				SNew(STextBlock)
				.Text(LOCTEXT("ChartsBlurb", "Check steps off as you go. Progress is saved per project under Saved/HarborSuite/ChartsState.json."))
				.AutoWrapText(true)
				.ColorAndOpacity(FSlateColor::UseSubduedForeground())
			]
			+ SVerticalBox::Slot()
			.AutoHeight()
			[
				List
			]
			+ SVerticalBox::Slot()
			.AutoHeight()
			.Padding(0.f, 12.f)
			[
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
				.AutoWidth()
				.Padding(0.f, 0.f, 8.f, 0.f)
				[
					SNew(SButton)
					.Text(LOCTEXT("SaveDirty", "Save all dirty packages"))
					.ToolTipText(LOCTEXT("SaveDirtyTip", "Runs the same style of save used by quick iteration: maps + content, no modal."))
					.OnClicked_Lambda([this]()
					{
						FHarborSuiteActions::SaveAllDirtyPackagesQuiet();
						PostInfo(LOCTEXT("SavedDirty", "Harbor Charts: save requested for dirty packages."));
						return FReply::Handled();
					})
				]
				+ SHorizontalBox::Slot()
				.AutoWidth()
				[
					SNew(SButton)
					.Text(LOCTEXT("ResetRunbook", "Reset runbook"))
					.ToolTipText(LOCTEXT("ResetRunbookTip", "Clears checkmarks for the Vertical Slice Gate."))
					.OnClicked_Lambda([this]()
					{
						if (GEditor)
						{
							if (UHarborSuiteEditorSubsystem* S = GEditor->GetEditorSubsystem<UHarborSuiteEditorSubsystem>())
							{
								S->ResetActiveRunbook();
							}
						}
						PostInfo(LOCTEXT("ResetRunbookDone", "Harbor Charts: runbook reset."));
						return FReply::Handled();
					})
				]
			]
		];
}

TSharedRef<SWidget> SHarborSuitePanel::BuildStowageContent()
{
	return SNew(SScrollBox)
		+ SScrollBox::Slot()
		[
			SNew(SVerticalBox)
			+ SVerticalBox::Slot()
			.AutoHeight()
			[
				SNew(STextBlock)
				.Text(LOCTEXT("StowageTitle", "Stowage — Outliner hygiene"))
				.Font(FAppStyle::GetFontStyle("HeadingExtraSmall"))
			]
			+ SVerticalBox::Slot()
			.AutoHeight()
			.Padding(0.f, 8.f)
			[
				SNew(STextBlock)
				.Text(LOCTEXT("StowageBlurb", "Prefix actor labels for the current selection so levels stay readable when actor count grows."))
				.AutoWrapText(true)
				.ColorAndOpacity(FSlateColor::UseSubduedForeground())
			]
			+ SVerticalBox::Slot()
			.AutoHeight()
			.Padding(0.f, 8.f)
			[
				SNew(STextBlock)
				.Text(LOCTEXT("PrefixLabel", "Prefix"))
			]
			+ SVerticalBox::Slot()
			.AutoHeight()
			[
				SAssignNew(StowagePrefixField, SEditableTextBox)
				.Text(FText::FromString(StowagePrefix))
				.OnTextChanged_Lambda([this](const FText& T) { StowagePrefix = T.ToString(); })
				.HintText(LOCTEXT("PrefixHint", "e.g. Harbor_ or LS_"))
			]
			+ SVerticalBox::Slot()
			.AutoHeight()
			.Padding(0.f, 10.f)
			[
				SNew(SButton)
				.Text(LOCTEXT("ApplyPrefix", "Apply prefix to selection"))
				.OnClicked_Lambda([this]()
				{
					const FString P = StowagePrefixField.IsValid() ? StowagePrefixField->GetText().ToString() : StowagePrefix;
					FHarborSuiteActions::PrefixActorLabelsOnSelection(P);
					PostInfo(LOCTEXT("PrefixDone", "Harbor Stowage: prefix applied where needed."));
					return FReply::Handled();
				})
			]
		];
}

TSharedRef<SWidget> SHarborSuitePanel::BuildShakedownContent()
{
	return SNew(SScrollBox)
		+ SScrollBox::Slot()
		[
			SNew(SVerticalBox)
			+ SVerticalBox::Slot()
			.AutoHeight()
			[
				SNew(STextBlock)
				.Text(LOCTEXT("ShakedownTitle", "Shakedown — PIE iteration"))
				.Font(FAppStyle::GetFontStyle("HeadingExtraSmall"))
			]
			+ SVerticalBox::Slot()
			.AutoHeight()
			.Padding(0.f, 8.f)
			[
				SNew(STextBlock)
				.Text(LOCTEXT("ShakedownBlurb", "Start Play-In-Editor, then use these to shorten your loop. They operate on the active PIE world."))
				.AutoWrapText(true)
				.ColorAndOpacity(FSlateColor::UseSubduedForeground())
			]
			+ SVerticalBox::Slot()
			.AutoHeight()
			.Padding(0.f, 10.f)
			[
				SNew(SButton)
				.Text(LOCTEXT("PieReset", "Move player to first PlayerStart"))
				.OnClicked_Lambda([this]()
				{
					FHarborSuiteActions::ResetPiePlayerToFirstPlayerStart();
					PostInfo(LOCTEXT("PieResetDone", "Harbor Shakedown: PIE player reset (if PIE and PlayerStart exist)."));
					return FReply::Handled();
				})
			]
			+ SVerticalBox::Slot()
			.AutoHeight()
			.Padding(0.f, 6.f)
			[
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
				.AutoWidth()
				.Padding(0.f, 0.f, 8.f, 0.f)
				[
					SNew(SButton)
					.Text(LOCTEXT("PieHalf", "Time dilation 0.5x"))
					.OnClicked_Lambda([this]()
					{
						FHarborSuiteActions::SetPieGlobalTimeDilation(0.5f);
						PostInfo(LOCTEXT("PieHalfDone", "Harbor Shakedown: PIE time dilation set to 0.5x."));
						return FReply::Handled();
					})
				]
				+ SHorizontalBox::Slot()
				.AutoWidth()
				[
					SNew(SButton)
					.Text(LOCTEXT("PieOne", "Time dilation 1.0x"))
					.OnClicked_Lambda([this]()
					{
						FHarborSuiteActions::SetPieGlobalTimeDilation(1.f);
						PostInfo(LOCTEXT("PieOneDone", "Harbor Shakedown: PIE time dilation set to 1.0x."));
						return FReply::Handled();
					})
				]
			]
		];
}

TSharedRef<SWidget> SHarborSuitePanel::BuildClearanceContent()
{
	return SNew(SScrollBox)
		+ SScrollBox::Slot()
		[
			SNew(SVerticalBox)
			+ SVerticalBox::Slot()
			.AutoHeight()
			[
				SNew(STextBlock)
				.Text(LOCTEXT("ClearanceTitle", "Clearance — lightweight signals"))
				.Font(FAppStyle::GetFontStyle("HeadingExtraSmall"))
			]
			+ SVerticalBox::Slot()
			.AutoHeight()
			.Padding(0.f, 8.f)
			[
				SNew(STextBlock)
				.Text(LOCTEXT("ClearanceBlurb", "Summarizes the open editor level. Tag demo actors with \"Problem\" in the label to practice triage."))
				.AutoWrapText(true)
				.ColorAndOpacity(FSlateColor::UseSubduedForeground())
			]
			+ SVerticalBox::Slot()
			.AutoHeight()
			.Padding(0.f, 10.f)
			[
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
				.AutoWidth()
				.Padding(0.f, 0.f, 8.f, 0.f)
				[
					SNew(SButton)
					.Text(LOCTEXT("RunScan", "Run scan"))
					.OnClicked_Lambda([this]()
					{
						FHarborClearanceReport Report;
						FHarborSuiteActions::BuildClearanceReport(Report);
						ClearanceReportText = FText::FromString(Report.SummaryText);
						Invalidate(EInvalidateWidgetReason::Paint);
						PostInfo(LOCTEXT("ScanDone", "Harbor Clearance: scan updated."));
						return FReply::Handled();
					})
				]
				+ SHorizontalBox::Slot()
				.AutoWidth()
				[
					SNew(SButton)
					.Text(LOCTEXT("SelectProblems", "Select labels containing \"Problem\""))
					.OnClicked_Lambda([this]()
					{
						FHarborSuiteActions::SelectActorsWithProblemInLabel();
						PostInfo(LOCTEXT("SelectProblemsDone", "Harbor Clearance: selection updated."));
						return FReply::Handled();
					})
				]
			]
			+ SVerticalBox::Slot()
			.FillHeight(1.f)
			[
				SNew(SScrollBox)
				+ SScrollBox::Slot()
				[
					SNew(STextBlock)
					.Text_Lambda([this]() { return ClearanceReportText; })
					.AutoWrapText(true)
				]
			]
		];
}

#undef LOCTEXT_NAMESPACE
