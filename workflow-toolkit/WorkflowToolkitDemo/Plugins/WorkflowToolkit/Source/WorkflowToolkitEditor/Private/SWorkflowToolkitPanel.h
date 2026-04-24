// Copyright (c) Immersive Labs. All Rights Reserved.

#pragma once

#include "Containers/Array.h"
#include "Delegates/Delegate.h"
#include "Internationalization/Text.h"
#include "Styling/SlateColor.h"
#include "Templates/SharedPointer.h"
#include "UObject/NameTypes.h"
#include "Widgets/SCompoundWidget.h"

class SEditableTextBox;

class SWorkflowToolkitPanel : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SWorkflowToolkitPanel) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);

private:
	TSharedRef<SWidget> BuildIntroHeader() const;
	TSharedRef<SWidget> BuildActionsTabScroll(TSharedPtr<SEditableTextBox>& OutEditorConsoleBox) const;
	TSharedRef<SWidget> BuildCardGrid(TArray<TSharedRef<SWidget>> Cards) const;
	TSharedRef<SWidget> BuildActionCard(const FText& Label, const FText& Tooltip, FSimpleDelegate OnClicked, FName IconBrushName) const;
	TSharedRef<SWidget> BuildAppIcon(FName IconBrushName, float Size, const FSlateColor& Tint) const;
	TSharedRef<SWidget> BuildSection(const FText& Title, FName SectionIconName, TSharedRef<SWidget> Body) const;
	TSharedRef<SWidget> BuildSectionHeader(const FText& Title, FName IconBrushName) const;
	TSharedRef<SWidget> BuildSubcategoryHeader(const FText& Title, FName IconBrushName) const;
	TSharedRef<SWidget> BuildSubcategoryBlock(
		const FText& Subtitle,
		TArray<TSharedRef<SWidget>> Cards,
		bool bFirstInSection,
		FName SubIconName) const;
	TSharedRef<SWidget> BuildConsoleCommandCard(TSharedPtr<SEditableTextBox>& OutEditorConsoleBox) const;
};
