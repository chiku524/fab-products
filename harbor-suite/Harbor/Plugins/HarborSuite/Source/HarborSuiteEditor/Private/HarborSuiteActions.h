// Copyright (c) Immersive Labs. All Rights Reserved.

#pragma once

#include "Containers/UnrealString.h"

struct FHarborClearanceReport
{
	int32 TotalActors = 0;
	int32 StaticMeshActors = 0;
	int32 PointLights = 0;
	int32 ProblemLabelActors = 0;
	FString SummaryText;
};

class FHarborSuiteActions
{
public:
	static void SaveAllDirtyPackagesQuiet();

	static void PrefixActorLabelsOnSelection(const FString& Prefix);

	static void ResetPiePlayerToFirstPlayerStart();

	static void SetPieGlobalTimeDilation(float Dilation);

	static void BuildClearanceReport(FHarborClearanceReport& OutReport);

	static void SelectActorsWithProblemInLabel();
};
