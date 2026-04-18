// Copyright (c) [PUBLISHER_NAME]. All Rights Reserved.

#include "LevelSelectionSetsDataActor.h"

#include "EngineUtils.h"

ALevelSelectionSetsData::ALevelSelectionSetsData()
{
	PrimaryActorTick.bCanEverTick = false;
	SetCanBeDamaged(false);
	SetActorHiddenInGame(true);
	SetIsTemporarilyHiddenInEditor(true);
	bIsEditorOnlyActor = true;
	SetActorLabel(TEXT("Level Selection Sets (data)"));
}

ALevelSelectionSetsData* ALevelSelectionSetsData::FindInWorld(UWorld* World)
{
	if (!World)
	{
		return nullptr;
	}

	for (TActorIterator<ALevelSelectionSetsData> It(World); It; ++It)
	{
		return *It;
	}

	return nullptr;
}

ALevelSelectionSetsData* ALevelSelectionSetsData::FindOrCreateInWorld(UWorld* World)
{
	if (ALevelSelectionSetsData* Existing = FindInWorld(World))
	{
		return Existing;
	}

	if (!World)
	{
		return nullptr;
	}

	ULevel* PersistentLevel = World->PersistentLevel;
	if (!PersistentLevel)
	{
		return nullptr;
	}

	FActorSpawnParameters SpawnParams;
	SpawnParams.Name = MakeUniqueObjectName(PersistentLevel, ALevelSelectionSetsData::StaticClass(), TEXT("LevelSelectionSetsData"));
	SpawnParams.OverrideLevel = PersistentLevel;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	return World->SpawnActor<ALevelSelectionSetsData>(FTransform::Identity, SpawnParams);
}

void ALevelSelectionSetsData::UpsertSet(FName SetName, TArray<FActorGuid>&& ActorGuids)
{
	if (SetName.IsNone())
	{
		return;
	}

	Modify();
	for (FNamedActorSelectionSet& Entry : Sets)
	{
		if (Entry.SetName == SetName)
		{
			Entry.ActorGuids = MoveTemp(ActorGuids);
			MarkPackageDirty();
			return;
		}
	}

	FNamedActorSelectionSet NewEntry;
	NewEntry.SetName = SetName;
	NewEntry.ActorGuids = MoveTemp(ActorGuids);
	Sets.Add(MoveTemp(NewEntry));
	MarkPackageDirty();
}

bool ALevelSelectionSetsData::RemoveSet(FName SetName)
{
	if (SetName.IsNone())
	{
		return false;
	}

	Modify();
	const int32 Removed = Sets.RemoveAll(
		[&SetName](const FNamedActorSelectionSet& Entry)
		{
			return Entry.SetName == SetName;
		});

	if (Removed > 0)
	{
		MarkPackageDirty();
		return true;
	}

	return false;
}

bool ALevelSelectionSetsData::RenameSet(FName OldName, FName NewName)
{
	if (OldName.IsNone() || NewName.IsNone() || OldName == NewName)
	{
		return false;
	}

	for (const FNamedActorSelectionSet& Entry : Sets)
	{
		if (Entry.SetName == NewName)
		{
			return false;
		}
	}

	Modify();
	for (FNamedActorSelectionSet& Entry : Sets)
	{
		if (Entry.SetName == OldName)
		{
			Entry.SetName = NewName;
			MarkPackageDirty();
			return true;
		}
	}

	return false;
}
