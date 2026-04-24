// Copyright (c) Immersive Labs. All Rights Reserved.

#include "SWorkflowToolkitPanel.h"

#include "Input/Reply.h"
#include "Styling/AppStyle.h"
#include "Styling/StyleColors.h"
#include "WorkflowToolkitEditorStyle.h"
#include "Widgets/Images/SImage.h"
#include "Widgets/Input/SButton.h"
#include "Widgets/Input/SEditableTextBox.h"
#include "Widgets/Layout/SBorder.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Layout/SScrollBox.h"
#include "Widgets/SBoxPanel.h"
#include "Widgets/SNullWidget.h"
#include "Widgets/Text/STextBlock.h"
#include "WorkflowToolkitActions.h"

#define LOCTEXT_NAMESPACE "SWorkflowToolkitPanel"

namespace WorkflowToolkitPanelLayout
{
	static constexpr float OuterPaddingL = 10.f;
	static constexpr float OuterPaddingT = 8.f;
	static constexpr float OuterPaddingR = 10.f;
	static constexpr float OuterPaddingB = 14.f;
	static constexpr float ScrollContentPaddingH = 4.f;
	static constexpr float ScrollContentPaddingV = 2.f;
	static constexpr float SectionBlockSpacing = 24.f;
	static constexpr float SectionTitleBottom = 10.f;
	static constexpr float SubcategoryFirstTop = 2.f;
	static constexpr float SubcategoryNextTop = 18.f;
	static constexpr float SubcategoryHeaderBottom = 8.f;
	static constexpr float CardGridColGap = 8.f;
	static constexpr float CardGridRowGap = 10.f;
}

/** FAppStyle / Starship icon names — themed with the editor. */
namespace WtkIcons
{
	// Sections
	static const FName SectionViewport(TEXT("Icons.SelectInViewport"));
	static const FName SectionBatch(TEXT("Icons.PlaceActors"));
	static const FName SectionAssets(TEXT("Icons.Save"));
	static const FName SectionEditor(TEXT("Icons.Toolbar.Settings"));
	static const FName SectionDiagnostics(TEXT("Icons.Audit"));
	static const FName SectionRuntime(TEXT("Icons.Play"));
	// Subcategory rows
	static const FName SubViewport(TEXT("Icons.FrameActor"));
	static const FName SubSelection(TEXT("Icons.GroupActors"));
	static const FName SubSnap(TEXT("Icons.Snap"));
	static const FName SubMeshes(TEXT("Icons.MakeStaticMesh"));
	static const FName SubPlacement(TEXT("Icons.PlaceActors"));
	static const FName SubWindows(TEXT("Icons.Details"));
	static const FName SubLogs(TEXT("Icons.Comment"));
	static const FName SubValidation(TEXT("Icons.Validate"));
	// Actions
	static const FName ActionFrame(TEXT("Icons.FrameActor"));
	static const FName ActionGroupClass(TEXT("Icons.GroupActors"));
	static const FName ActionClipboard(TEXT("Icons.Clipboard"));
	static const FName ActionColor(TEXT("Icons.Color"));
	static const FName ActionSnap(TEXT("Icons.Snap"));
	static const FName ActionTransform(TEXT("Icons.Transform"));
	static const FName ActionMesh(TEXT("Icons.MakeStaticMesh"));
	static const FName ActionOpenExternal(TEXT("Icons.OpenInExternalEditor"));
	static const FName ActionScalability(TEXT("Icons.Scalability"));
	static const FName ActionPlace(TEXT("Icons.PlaceActors"));
	static const FName ActionDuplicate(TEXT("Icons.ReplaceActor"));
	static const FName ActionSave(TEXT("Icons.Save"));
	static const FName ActionBrowse(TEXT("Icons.BrowseContent"));
	static const FName ActionSettings(TEXT("Icons.Toolbar.Settings"));
	static const FName ActionTools(TEXT("Icons.Tools"));
	static const FName ActionWorld(TEXT("Icons.World"));
	static const FName ActionTextEditor(TEXT("Icons.TextEditor"));
	static const FName ActionComment(TEXT("Icons.Comment"));
	static const FName ActionValidate(TEXT("Icons.Validate"));
	static const FName ActionConsole(TEXT("Icons.TextEditor"));
}

void SWorkflowToolkitPanel::Construct(const FArguments& InArgs)
{
	TSharedPtr<SEditableTextBox> EditorConsoleCommandBox;

	ChildSlot
		[
			SNew(SBorder)
			.BorderImage(FWorkflowToolkitEditorStyle::GetBrush(FWorkflowToolkitEditorStyle::PageBackgroundBrushName))
			.Padding(FMargin(
				WorkflowToolkitPanelLayout::OuterPaddingL,
				WorkflowToolkitPanelLayout::OuterPaddingT,
				WorkflowToolkitPanelLayout::OuterPaddingR,
				WorkflowToolkitPanelLayout::OuterPaddingB))
			[
				BuildActionsTabScroll(EditorConsoleCommandBox)
			]
		];
}

TSharedRef<SWidget> SWorkflowToolkitPanel::BuildActionsTabScroll(TSharedPtr<SEditableTextBox>& OutEditorConsoleBox) const
{
	return SNew(SScrollBox)
		+ SScrollBox::Slot()
		.Padding(FMargin(
			WorkflowToolkitPanelLayout::ScrollContentPaddingH,
			WorkflowToolkitPanelLayout::ScrollContentPaddingV,
			WorkflowToolkitPanelLayout::ScrollContentPaddingH,
			WorkflowToolkitPanelLayout::ScrollContentPaddingV))
		[
			SNew(SVerticalBox)
			+ SVerticalBox::Slot().AutoHeight().Padding(0, 0, 0, 14)
			[
				BuildIntroHeader()
			]
			+ SVerticalBox::Slot().AutoHeight().Padding(0, 0, 0, WorkflowToolkitPanelLayout::SectionBlockSpacing)
			[
				BuildSection(
					LOCTEXT("SectionSelection", "Selection & viewport"),
					WtkIcons::SectionViewport,
					SNew(SVerticalBox)
					+ SVerticalBox::Slot().AutoHeight()
					[
						BuildSubcategoryBlock(
							LOCTEXT("SubViewport", "Viewport"),
							TArray<TSharedRef<SWidget>>
							{
								BuildActionCard(
									LOCTEXT("BtnFrame", "Frame selection in viewport"),
									LOCTEXT("TipFrame", "Frames the current selection in the active level viewport (only the focused viewport moves)."),
									FSimpleDelegate::CreateStatic(&FWorkflowToolkitActions::FrameSelectionInActiveViewport),
									WtkIcons::ActionFrame),
							},
							/*bFirstInSection=*/true,
							WtkIcons::SubViewport)
					]
					+ SVerticalBox::Slot().AutoHeight()
					[
						BuildSubcategoryBlock(
							LOCTEXT("SubSelection", "Selection"),
							TArray<TSharedRef<SWidget>>
							{
								BuildActionCard(
									LOCTEXT("BtnSameClass", "Select all actors of same class"),
									LOCTEXT("TipSameClass", "Uses the first selected actor's class and selects every matching actor in the level."),
									FSimpleDelegate::CreateStatic(&FWorkflowToolkitActions::SelectAllActorsOfSameClassAsFirstSelection),
									WtkIcons::ActionGroupClass),
								BuildActionCard(
									LOCTEXT("BtnCopyPaths", "Copy actor paths to clipboard"),
									LOCTEXT("TipCopyPaths", "Copies full object paths of selected actors (one per line) for logs, configs, or sharing with teammates."),
									FSimpleDelegate::CreateStatic(&FWorkflowToolkitActions::CopySelectedActorPathsToClipboard),
									WtkIcons::ActionClipboard),
								BuildActionCard(
									LOCTEXT("BtnSameMaterial", "Select all with same material (slot 0)"),
									LOCTEXT("TipSameMaterial", "Uses the first static mesh's material on slot 0 from the selection and selects every actor using that material on slot 0."),
									FSimpleDelegate::CreateStatic(&FWorkflowToolkitActions::SelectAllActorsUsingSameMaterialAsFirstStaticMeshSelection),
									WtkIcons::ActionColor),
							},
							/*bFirstInSection=*/false,
							WtkIcons::SubSelection)
					]
					+ SVerticalBox::Slot().AutoHeight()
					[
						BuildSubcategoryBlock(
							LOCTEXT("SubSnapGrid", "Snap & grid"),
							TArray<TSharedRef<SWidget>>
							{
								BuildActionCard(
									LOCTEXT("BtnSnapInt", "Snap locations to integer grid"),
									LOCTEXT("TipSnapInt", "Rounds selected actor locations to whole world units."),
									FSimpleDelegate::CreateStatic(&FWorkflowToolkitActions::SnapSelectedActorLocationsToIntegerGrid),
									WtkIcons::ActionSnap),
								BuildActionCard(
									LOCTEXT("BtnSnapRot", "Snap rotation to 90° grid"),
									LOCTEXT("TipSnapRot", "Snaps roll, pitch, and yaw to the nearest 90° for quick orthogonal alignment."),
									FSimpleDelegate::CreateStatic(&FWorkflowToolkitActions::SnapSelectedActorsRotationToNearestRightAngles),
									WtkIcons::ActionTransform),
							},
							/*bFirstInSection=*/false,
							WtkIcons::SubSnap)
					])
			]
			+ SVerticalBox::Slot().AutoHeight().Padding(0, 0, 0, WorkflowToolkitPanelLayout::SectionBlockSpacing)
			[
				BuildSection(
					LOCTEXT("SectionBatch", "Batch & placement"),
					WtkIcons::SectionBatch,
					SNew(SVerticalBox)
					+ SVerticalBox::Slot().AutoHeight()
					[
						BuildSubcategoryBlock(
							LOCTEXT("SubStaticMeshes", "Static meshes"),
							TArray<TSharedRef<SWidget>>
							{
								BuildActionCard(
									LOCTEXT("BtnSameMesh", "Select all actors using same static mesh"),
									LOCTEXT("TipSameMesh", "Uses the first static mesh found on the selection and selects every actor that references it."),
									FSimpleDelegate::CreateStatic(&FWorkflowToolkitActions::SelectAllActorsUsingSameStaticMeshAsFirstSelection),
									WtkIcons::ActionMesh),
								BuildActionCard(
									LOCTEXT("BtnOpenMesh", "Open static mesh asset"),
									LOCTEXT("TipOpenMesh", "Opens the Static Mesh editor for the first mesh on the selection (fast material / LOD tweaks)."),
									FSimpleDelegate::CreateStatic(&FWorkflowToolkitActions::OpenFirstStaticMeshFromSelectionInAssetEditor),
									WtkIcons::ActionOpenExternal),
								BuildActionCard(
									LOCTEXT("BtnMobility", "Set static mesh mobility to Static"),
									LOCTEXT("TipMobility", "Sets every StaticMeshComponent on selected actors to Static mobility (lighting-friendly batch fix)."),
									FSimpleDelegate::CreateStatic(&FWorkflowToolkitActions::SetSelectedStaticMeshComponentsMobilityStatic),
									WtkIcons::ActionScalability),
							},
							/*bFirstInSection=*/true,
							WtkIcons::SubMeshes)
					]
					+ SVerticalBox::Slot().AutoHeight()
					[
						BuildSubcategoryBlock(
							LOCTEXT("SubPlacement", "Placement"),
							TArray<TSharedRef<SWidget>>
							{
								BuildActionCard(
									LOCTEXT("BtnFloor", "Align selection bottom to floor (trace)"),
									LOCTEXT("TipFloor", "Vertical trace moves each actor so its bounds bottom meets the first visibility hit below."),
									FSimpleDelegate::CreateStatic(&FWorkflowToolkitActions::AlignSelectedActorsBottomToFloorTrace),
									WtkIcons::ActionPlace),
								BuildActionCard(
									LOCTEXT("BtnDup", "Duplicate selection"),
									LOCTEXT("TipDup", "Runs the editor Duplicate command on the current selection."),
									FSimpleDelegate::CreateStatic(&FWorkflowToolkitActions::DuplicateSelectedActors),
									WtkIcons::ActionDuplicate),
							},
							/*bFirstInSection=*/false,
							WtkIcons::SubPlacement)
					])
			]
			+ SVerticalBox::Slot().AutoHeight().Padding(0, 0, 0, WorkflowToolkitPanelLayout::SectionBlockSpacing)
			[
				BuildSection(
					LOCTEXT("SectionAssets", "Assets & saving"),
					WtkIcons::SectionAssets,
					BuildCardGrid(
						TArray<TSharedRef<SWidget>>
						{
							BuildActionCard(
								LOCTEXT("BtnSaveAll", "Save all dirty packages"),
								LOCTEXT("TipSaveAll", "Saves all dirty map and content packages without a confirmation dialog."),
								FSimpleDelegate::CreateStatic(&FWorkflowToolkitActions::SaveAllDirtyPackagesWithoutPrompt),
								WtkIcons::ActionSave),
							BuildActionCard(
								LOCTEXT("BtnSyncCB", "Sync Content Browser to selection"),
								LOCTEXT("TipSyncCB", "Focuses the Content Browser on the selected asset, or a mesh used by the selected actor."),
								FSimpleDelegate::CreateStatic(&FWorkflowToolkitActions::SyncContentBrowserToSelection),
								WtkIcons::ActionBrowse),
						}))
			]
			+ SVerticalBox::Slot().AutoHeight().Padding(0, 0, 0, WorkflowToolkitPanelLayout::SectionBlockSpacing)
			[
				BuildSection(
					LOCTEXT("SectionEditorShell", "Editor windows & console"),
					WtkIcons::SectionEditor,
					SNew(SVerticalBox)
					+ SVerticalBox::Slot().AutoHeight().Padding(0, 0, 0, 14)
					[
						BuildConsoleCommandCard(OutEditorConsoleBox)
					]
					+ SVerticalBox::Slot().AutoHeight()
					[
						BuildSubcategoryBlock(
							LOCTEXT("SubEditorWindows", "Windows"),
							TArray<TSharedRef<SWidget>>
							{
								BuildActionCard(
									LOCTEXT("BtnProjSettings", "Open Project Settings — Engine / General"),
									LOCTEXT("TipProjSettings", "Opens Project Settings to the Engine → General section."),
									FSimpleDelegate::CreateStatic(&FWorkflowToolkitActions::OpenProjectSettingsEngineGeneral),
									WtkIcons::ActionSettings),
								BuildActionCard(
									LOCTEXT("BtnPlugins", "Open Plugins"),
									LOCTEXT("TipPlugins", "Opens the Plugins browser tab."),
									FSimpleDelegate::CreateStatic(&FWorkflowToolkitActions::OpenPluginsEditorTab),
									WtkIcons::ActionTools),
								BuildActionCard(
									LOCTEXT("BtnWorldSettings", "Open World Settings"),
									LOCTEXT("TipWorldSettings", "Opens the World Settings tab for the current level."),
									FSimpleDelegate::CreateStatic(&FWorkflowToolkitActions::OpenWorldSettingsTab),
									WtkIcons::ActionWorld),
							},
							/*bFirstInSection=*/true,
							WtkIcons::SubWindows)
					])
			]
			+ SVerticalBox::Slot().AutoHeight().Padding(0, 0, 0, WorkflowToolkitPanelLayout::SectionBlockSpacing)
			[
				BuildSection(
					LOCTEXT("SectionLogs", "Diagnostics"),
					WtkIcons::SectionDiagnostics,
					SNew(SVerticalBox)
					+ SVerticalBox::Slot().AutoHeight()
					[
						BuildSubcategoryBlock(
							LOCTEXT("SubLogs", "Logs"),
							TArray<TSharedRef<SWidget>>
							{
								BuildActionCard(
									LOCTEXT("BtnOutputLog", "Open Output Log"),
									LOCTEXT("TipOutputLog", "Opens the Output Log tab."),
									FSimpleDelegate::CreateStatic(&FWorkflowToolkitActions::OpenOutputLogTab),
									WtkIcons::ActionTextEditor),
								BuildActionCard(
									LOCTEXT("BtnMessageLog", "Open Message Log"),
									LOCTEXT("TipMessageLog", "Opens the Message Log tab."),
									FSimpleDelegate::CreateStatic(&FWorkflowToolkitActions::OpenMessageLogTab),
									WtkIcons::ActionComment),
							},
							/*bFirstInSection=*/true,
							WtkIcons::SubLogs)
					]
					+ SVerticalBox::Slot().AutoHeight()
					[
						BuildSubcategoryBlock(
							LOCTEXT("SubValidation", "Level validation"),
							TArray<TSharedRef<SWidget>>
							{
								BuildActionCard(
									LOCTEXT("BtnMapCheck", "Run map check"),
									LOCTEXT("TipMapCheck", "Runs MAP CHECK and reports issues in the Message Log (validation before check-in)."),
									FSimpleDelegate::CreateStatic(&FWorkflowToolkitActions::RunMapCheck),
									WtkIcons::ActionValidate),
							},
							/*bFirstInSection=*/false,
							WtkIcons::SubValidation)
					])
			]
			+ SVerticalBox::Slot().AutoHeight().Padding(0, 0, 0, 0)
			[
				BuildSection(
					LOCTEXT("SectionRuntime", "Runtime companion (PIE / game)"),
					WtkIcons::SectionRuntime,
					SNew(SBorder)
					.BorderImage(FWorkflowToolkitEditorStyle::GetBrush(FWorkflowToolkitEditorStyle::InfoCardBrushName))
					.Padding(FMargin(14, 12, 14, 12))
					[
						SNew(SHorizontalBox)
						+ SHorizontalBox::Slot().AutoWidth().Padding(0, 0, 12, 0).VAlign(VAlign_Top)
						[
							BuildAppIcon(WtkIcons::SectionRuntime, 22.f, FStyleColors::Foreground)
						]
						+ SHorizontalBox::Slot().FillWidth(1.f)
						[
							SNew(STextBlock)
							.AutoWrapText(true)
							.ColorAndOpacity(FStyleColors::Foreground)
							.Font(FAppStyle::GetFontStyle("SmallFont"))
							.Text(LOCTEXT(
								"RuntimeHint",
								"In Blueprints: Game Instance → Get Subsystem → Workflow Toolkit Runtime Subsystem — pause, time dilation, on-screen print, teleport, camera blend, and console (non-shipping). Rebind keys under Editor Preferences → Keyboard Shortcuts → search \"Workflow Toolkit\"."))
						]
					])
			]
		];
}

TSharedRef<SWidget> SWorkflowToolkitPanel::BuildIntroHeader() const
{
	return SNew(SBorder)
		.BorderImage(FWorkflowToolkitEditorStyle::GetBrush(FWorkflowToolkitEditorStyle::HeroCardBrushName))
		.Padding(FMargin(16, 14, 16, 14))
		[
			SNew(SVerticalBox)
			+ SVerticalBox::Slot().AutoHeight()
			[
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot().AutoWidth().Padding(0, 0, 12, 0).VAlign(VAlign_Center)
				[
					SNew(SBox)
					.WidthOverride(40.f)
					.HeightOverride(40.f)
					[
						SNew(SImage)
						.Image(FWorkflowToolkitEditorStyle::GetBrush(FWorkflowToolkitEditorStyle::TabIconName))
					]
				]
				+ SHorizontalBox::Slot().FillWidth(1.f).VAlign(VAlign_Center)
				[
					SNew(STextBlock)
					.Text(LOCTEXT("IntroTitle", "Workflow Toolkit"))
					.Font(FAppStyle::GetFontStyle("NormalFont"))
					.ColorAndOpacity(FStyleColors::ForegroundHeader)
					.Justification(ETextJustify::Left)
				]
			]
			+ SVerticalBox::Slot().AutoHeight().Padding(0, 6, 0, 8)
			[
				SNew(STextBlock)
				.AutoWrapText(true)
				.ColorAndOpacity(FStyleColors::Foreground)
				.Font(FAppStyle::GetFontStyle("SmallFont"))
				.Text(LOCTEXT(
					"IntroBody",
					"Actions below are also bound to editor commands. Change keys in Keyboard Shortcuts (search Workflow Toolkit)."))
			]
			+ SVerticalBox::Slot().AutoHeight().Padding(0, 0, 0, 10)
			[
				SNew(SButton)
				.ButtonStyle(FAppStyle::Get(), "FlatButton.Primary")
				.ContentPadding(FMargin(12, 8))
				.ToolTipText(LOCTEXT(
					"PanelShortcutTip",
					"Opens Editor Preferences → General → Keyboard Shortcuts. In the search box, type Open Workflow Toolkit (category: Workflow Toolkit). Assign the key that shows or focuses this panel (default Alt+Shift+W). Use the same shortcut again to focus the tab; close the tab from its × when you are done."))
				.OnClicked_Lambda([]()
				{
					FWorkflowToolkitActions::OpenEditorKeyboardShortcutsSettings();
					return FReply::Handled();
				})
				[
					SNew(STextBlock)
					.Text(LOCTEXT("PanelShortcutBtn", "Set shortcut for this panel…"))
				]
			]
			+ SVerticalBox::Slot().AutoHeight()
			[
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot().AutoWidth().Padding(0, 0, 8, 0).VAlign(VAlign_Top)
				[
					BuildAppIcon(WtkIcons::ActionTools, 16.f, FStyleColors::AccentGray)
				]
				+ SHorizontalBox::Slot().FillWidth(1.f)
				[
					SNew(STextBlock)
					.AutoWrapText(true)
					.ColorAndOpacity(FStyleColors::AccentGray)
					.Font(FAppStyle::GetFontStyle("SmallFont"))
					.Text(LOCTEXT(
						"IntroExamples",
						"Examples: Ctrl+Alt+F frame selection, Ctrl+Alt+S save all, Ctrl+Alt+B sync Content Browser, Ctrl+Alt+O Output Log."))
				]
			]
		];
}

TSharedRef<SWidget> SWorkflowToolkitPanel::BuildAppIcon(FName IconBrushName, float Size, const FSlateColor& Tint) const
{
	return SNew(SBox)
		.WidthOverride(Size)
		.HeightOverride(Size)
		[
			SNew(SImage)
			.Image(FAppStyle::GetBrush(IconBrushName))
			.ColorAndOpacity(Tint)
		];
}

TSharedRef<SWidget> SWorkflowToolkitPanel::BuildSection(const FText& Title, FName SectionIconName, TSharedRef<SWidget> Body) const
{
	return SNew(SVerticalBox)
		+ SVerticalBox::Slot().AutoHeight().Padding(0, 0, 0, WorkflowToolkitPanelLayout::SectionTitleBottom)
		[
			BuildSectionHeader(Title, SectionIconName)
		]
		+ SVerticalBox::Slot().AutoHeight()
		[
			Body
		];
}

TSharedRef<SWidget> SWorkflowToolkitPanel::BuildSectionHeader(const FText& Title, FName IconBrushName) const
{
	return SNew(SHorizontalBox)
		+ SHorizontalBox::Slot().AutoWidth().Padding(0, 0, 8, 0).VAlign(VAlign_Center)
		[
			BuildAppIcon(IconBrushName, 20.f, FStyleColors::ForegroundHeader)
		]
		+ SHorizontalBox::Slot().FillWidth(1.f).VAlign(VAlign_Center)
		[
			SNew(STextBlock)
			.Text(Title)
			.Font(FAppStyle::GetFontStyle("DetailsView.CategoryFont"))
			.ColorAndOpacity(FStyleColors::ForegroundHeader)
		];
}

TSharedRef<SWidget> SWorkflowToolkitPanel::BuildSubcategoryHeader(const FText& Title, FName IconBrushName) const
{
	return SNew(SHorizontalBox)
		+ SHorizontalBox::Slot().AutoWidth().Padding(0, 0, 6, 0).VAlign(VAlign_Center)
		[
			BuildAppIcon(IconBrushName, 16.f, FStyleColors::AccentGray)
		]
		+ SHorizontalBox::Slot().FillWidth(1.f).VAlign(VAlign_Center)
		[
			SNew(STextBlock)
			.Text(Title)
			.Font(FAppStyle::GetFontStyle("SmallFont"))
			.ColorAndOpacity(FStyleColors::AccentGray)
		];
}

TSharedRef<SWidget> SWorkflowToolkitPanel::BuildSubcategoryBlock(
	const FText& Subtitle,
	TArray<TSharedRef<SWidget>> Cards,
	bool bFirstInSection,
	FName SubIconName) const
{
	return SNew(SVerticalBox)
		+ SVerticalBox::Slot().AutoHeight().Padding(
			0,
			bFirstInSection ? WorkflowToolkitPanelLayout::SubcategoryFirstTop : WorkflowToolkitPanelLayout::SubcategoryNextTop,
			0,
			WorkflowToolkitPanelLayout::SubcategoryHeaderBottom)
		[
			BuildSubcategoryHeader(Subtitle, SubIconName)
		]
		+ SVerticalBox::Slot().AutoHeight()
		[
			BuildCardGrid(Cards)
		];
}

TSharedRef<SWidget> SWorkflowToolkitPanel::BuildConsoleCommandCard(TSharedPtr<SEditableTextBox>& OutEditorConsoleBox) const
{
	return SNew(SBorder)
		.BorderImage(FWorkflowToolkitEditorStyle::GetBrush(FWorkflowToolkitEditorStyle::ConsoleCardBrushName))
		.Padding(FMargin(14, 12, 14, 12))
		[
			SNew(SVerticalBox)
			+ SVerticalBox::Slot().AutoHeight().Padding(0, 0, 0, 8)
			[
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot().AutoWidth().Padding(0, 0, 8, 0).VAlign(VAlign_Center)
				[
					BuildAppIcon(WtkIcons::ActionConsole, 20.f, FStyleColors::ForegroundHeader)
				]
				+ SHorizontalBox::Slot().FillWidth(1.f).VAlign(VAlign_Center)
				[
					SNew(STextBlock)
					.Text(LOCTEXT("ConsoleCardTitle", "Editor console"))
					.Font(FAppStyle::GetFontStyle("NormalFont"))
					.ColorAndOpacity(FStyleColors::ForegroundHeader)
				]
			]
			+ SVerticalBox::Slot().AutoHeight().Padding(0, 0, 0, 10)
			[
				SNew(STextBlock)
				.AutoWrapText(true)
				.ColorAndOpacity(FStyleColors::Foreground)
				.Font(FAppStyle::GetFontStyle("SmallFont"))
				.Text(LOCTEXT("ConsoleCardDesc", "Runs a command in the editor console (e.g. stat fps, logs)."))
			]
			+ SVerticalBox::Slot().AutoHeight()
			[
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot().FillWidth(1.f).Padding(0, 0, 8, 0)
				[
					SAssignNew(OutEditorConsoleBox, SEditableTextBox)
					.HintText(LOCTEXT("ConsoleHint", "Editor console command (e.g. stat fps)..."))
				]
				+ SHorizontalBox::Slot().AutoWidth()
				[
					SNew(SButton)
					.ButtonStyle(FAppStyle::Get(), "FlatButton.Primary")
					.ContentPadding(FMargin(8, 6))
					.OnClicked(FOnClicked::CreateLambda([OutEditorConsoleBox]()
					{
						if (OutEditorConsoleBox.IsValid())
						{
							FWorkflowToolkitActions::ExecuteEditorConsoleCommand(OutEditorConsoleBox->GetText().ToString());
						}
						return FReply::Handled();
					}))
					[
						SNew(STextBlock)
						.Text(LOCTEXT("RunConsole", "Run"))
					]
				]
			]
		];
}

TSharedRef<SWidget> SWorkflowToolkitPanel::BuildActionCard(
	const FText& Label,
	const FText& Tooltip,
	FSimpleDelegate OnClicked,
	FName IconBrushName) const
{
	return SNew(SBorder)
		.BorderImage(FWorkflowToolkitEditorStyle::GetBrush(FWorkflowToolkitEditorStyle::CardSurfaceBrushName))
		.Padding(FMargin(0))
		[
			SNew(SButton)
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.ButtonStyle(FAppStyle::Get(), "FlatButton.Default")
			.ForegroundColor(FStyleColors::Foreground)
			.ToolTipText(Tooltip)
			.OnClicked_Lambda([OnClicked]()
			{
				OnClicked.ExecuteIfBound();
				return FReply::Handled();
			})
			.ContentPadding(FMargin(12, 12))
			[
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot().AutoWidth().Padding(0, 0, 10, 0).VAlign(VAlign_Top)
				[
					BuildAppIcon(IconBrushName, 20.f, FStyleColors::Foreground)
				]
				+ SHorizontalBox::Slot().FillWidth(1.f)
				[
					SNew(SVerticalBox)
					+ SVerticalBox::Slot().AutoHeight()
					[
						SNew(STextBlock)
						.Text(Label)
						.Font(FAppStyle::GetFontStyle("NormalFont"))
						.ColorAndOpacity(FStyleColors::Foreground)
						.AutoWrapText(true)
					]
					+ SVerticalBox::Slot().AutoHeight().Padding(0, 6, 0, 0)
					[
						SNew(STextBlock)
						.Text(Tooltip)
						.AutoWrapText(true)
						.Font(FAppStyle::GetFontStyle("SmallFont"))
						.ColorAndOpacity(FStyleColors::AccentGray)
					]
				]
			]
		];
}

TSharedRef<SWidget> SWorkflowToolkitPanel::BuildCardGrid(TArray<TSharedRef<SWidget>> Cards) const
{
	if (Cards.Num() == 0)
	{
		return SNullWidget::NullWidget;
	}

	if (Cards.Num() == 1)
	{
		return Cards[0];
	}

	const float ColGap = WorkflowToolkitPanelLayout::CardGridColGap;
	const float RowGap = WorkflowToolkitPanelLayout::CardGridRowGap;

	TSharedRef<SVerticalBox> Grid = SNew(SVerticalBox);
	for (int32 i = 0; i < Cards.Num(); i += 2)
	{
		const bool bHasPair = (i + 1 < Cards.Num());
		if (bHasPair)
		{
			const bool bLastRow = (i + 2 >= Cards.Num());
			Grid->AddSlot()
				.AutoHeight()
				.Padding(0, 0, 0, bLastRow ? 0.f : RowGap)
				[
					SNew(SHorizontalBox)
					+ SHorizontalBox::Slot().FillWidth(1.f).Padding(0, 0, ColGap * 0.5f, 0)
					[
						Cards[i]
					]
					+ SHorizontalBox::Slot().FillWidth(1.f).Padding(ColGap * 0.5f, 0, 0, 0)
					[
						Cards[i + 1]
					]
				];
		}
		else
		{
			Grid->AddSlot()
				.AutoHeight()
				[
					Cards[i]
				];
		}
	}
	return Grid;
}

#undef LOCTEXT_NAMESPACE
