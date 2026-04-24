// Copyright (c) Immersive Labs. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

enum class EHarborPillar : uint8
{
	Charts = 0,
	Stowage = 1,
	Shakedown = 2,
	Clearance = 3,
};

class SHarborSuitePanel : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SHarborSuitePanel) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);

private:
	EHarborPillar ActivePillar = EHarborPillar::Charts;

	TSharedPtr<class SWidgetSwitcher> PillarSwitcher;
	TSharedPtr<class SEditableTextBox> StowagePrefixField;

	FString StowagePrefix = TEXT("Harbor_");

	FText ClearanceReportText = FText::FromString(TEXT("Run a scan to summarize the open editor level."));

	FReply OnPillarClicked(EHarborPillar Pillar);

	TSharedRef<SWidget> BuildPillarStrip();
	TSharedRef<SWidget> BuildChartsContent();
	TSharedRef<SWidget> BuildStowageContent();
	TSharedRef<SWidget> BuildShakedownContent();
	TSharedRef<SWidget> BuildClearanceContent();

	void PostInfo(const FText& Message) const;
};
