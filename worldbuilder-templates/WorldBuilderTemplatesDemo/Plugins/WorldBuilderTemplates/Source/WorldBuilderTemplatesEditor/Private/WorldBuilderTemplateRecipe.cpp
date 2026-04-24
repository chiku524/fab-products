// Copyright (c) Immersive Labs. All Rights Reserved.

#include "WorldBuilderTemplateRecipe.h"

#include "WorldBuilderTemplateDefaults.h"

UWorldBuilderTemplateRecipe::UWorldBuilderTemplateRecipe()
{
	Outdoor = WorldBuilderTemplateDefaults::MakeOutdoorShipped();
	Indoor = WorldBuilderTemplateDefaults::MakeIndoorShipped();
	Ocean = WorldBuilderTemplateDefaults::MakeOceanShipped();
	City = WorldBuilderTemplateDefaults::MakeCityShipped();
}
