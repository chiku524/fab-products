// Copyright (c) Immersive Labs. All Rights Reserved.

#pragma once

#include "Math/RandomStream.h"
#include "WorldBuilderTemplateTypes.h"

class UWorld;
class UWorldBuilderTemplateRecipe;

namespace WorldBuilderTemplatesSampleMapBuilder
{
	void SetupOutdoor(UWorld* World);
	void SetupOutdoor(UWorld* World, const FWorldBuilderOutdoorParams& Params, FRandomStream& Rand);

	void SetupIndoorBlockout(UWorld* World);
	void SetupIndoorBlockout(UWorld* World, const FWorldBuilderIndoorParams& Params, FRandomStream& Rand);

	void SetupOcean(UWorld* World);
	void SetupOcean(UWorld* World, const FWorldBuilderOceanParams& Params, FRandomStream& Rand);

	void SetupCity(UWorld* World);
	void SetupCity(UWorld* World, const FWorldBuilderCityParams& Params, FRandomStream& Rand);

	void ApplyRecipe(UWorld* World, const UWorldBuilderTemplateRecipe* Recipe);
}
