// Copyright (c) Immersive Labs. All Rights Reserved.

#pragma once

#include "Engine/DataAsset.h"
#include "WorldBuilderTemplateTypes.h"
#include "WorldBuilderTemplateRecipe.generated.h"

/**
 * Data asset describing a procedural template: which layout to build, random seed, and per-kind parameters.
 * Artists can duplicate assets in the Content Browser and tune values without C++.
 */
UCLASS(BlueprintType)
class UWorldBuilderTemplateRecipe : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Recipe")
	EWorldBuilderTemplateKind TemplateKind = EWorldBuilderTemplateKind::Outdoor;

	/** 0 = pick a random seed when applying (non-deterministic). Otherwise used for FRandomStream. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Recipe", meta = (ClampMin = "0"))
	int32 Seed = 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Outdoor")
	FWorldBuilderOutdoorParams Outdoor;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Indoor")
	FWorldBuilderIndoorParams Indoor;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ocean")
	FWorldBuilderOceanParams Ocean;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "City")
	FWorldBuilderCityParams City;

	UWorldBuilderTemplateRecipe();
};
