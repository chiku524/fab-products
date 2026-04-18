// Copyright (c) Immersive Labs. All Rights Reserved.

#pragma once

#include "Engine/ActorGuid.h"
#include "LevelSelectionSetsTypes.generated.h"

USTRUCT()
struct FNamedActorSelectionSet
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "LevelSelectionSets")
	FName SetName;

	UPROPERTY(EditAnywhere, Category = "LevelSelectionSets")
	TArray<FActorGuid> ActorGuids;
};
