// Copyright (c) Immersive Labs. All Rights Reserved.

#pragma once

#include "GameFramework/Actor.h"
#include "LevelSelectionSetsTypes.h"
#include "LevelSelectionSetsDataActor.generated.h"

class UWorld;

/**
 * Editor-only anchor actor stored in the persistent level. Selection sets save with the map.
 */
UCLASS(NotPlaceable)
class ALevelSelectionSetsData : public AActor
{
	GENERATED_BODY()

public:
	ALevelSelectionSetsData();

	static ALevelSelectionSetsData* FindInWorld(UWorld* World);
	static ALevelSelectionSetsData* FindOrCreateInWorld(UWorld* World);

	const TArray<FNamedActorSelectionSet>& GetSets() const { return Sets; }

	void UpsertSet(FName SetName, TArray<FActorGuid>&& ActorGuids);
	bool RemoveSet(FName SetName);
	bool RenameSet(FName OldName, FName NewName);

private:
	UPROPERTY(VisibleAnywhere, Category = "LevelSelectionSets")
	TArray<FNamedActorSelectionSet> Sets;
};
