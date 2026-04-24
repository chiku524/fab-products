// Copyright (c) Immersive Labs. All Rights Reserved.

#pragma once

#include "WorldBuilderTemplateTypes.h"

namespace WorldBuilderTemplateDefaults
{
	/** Matches the shipped WBT_Template_Outdoor layout (fixed trees, seed 91021 for rocks). */
	FWorldBuilderOutdoorParams MakeOutdoorShipped();

	FWorldBuilderIndoorParams MakeIndoorShipped();
	FWorldBuilderOceanParams MakeOceanShipped();
	FWorldBuilderCityParams MakeCityShipped();
}
