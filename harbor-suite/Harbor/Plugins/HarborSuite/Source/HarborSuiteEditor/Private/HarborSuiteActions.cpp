// Copyright (c) Immersive Labs. All Rights Reserved.

#include "HarborSuiteActions.h"

#include "Components/StaticMeshComponent.h"
#include "Editor.h"
#include "FileHelpers.h"
#include "Engine/PointLight.h"
#include "Engine/World.h"
#include "EngineUtils.h"
#include "GameFramework/PlayerStart.h"
#include "GameFramework/Pawn.h"
#include "Kismet/GameplayStatics.h"
#include "ScopedTransaction.h"
#include "Selection.h"

#define LOCTEXT_NAMESPACE "HarborSuiteActions"

static UWorld* FindFirstPieWorld()
{
	if (!GEditor)
	{
		return nullptr;
	}

	for (const FWorldContext& Ctx : GEditor->GetWorldContexts())
	{
		if (Ctx.WorldType == EWorldType::PIE && Ctx.World())
		{
			return Ctx.World();
		}
	}

	return nullptr;
}

static UWorld* GetEditorWorld()
{
	if (!GEditor)
	{
		return nullptr;
	}

	return GEditor->GetEditorWorldContext().World();
}

void FHarborSuiteActions::SaveAllDirtyPackagesQuiet()
{
	UEditorLoadingAndSavingUtils::SaveDirtyPackages(
		/*bSaveMapPackages*/ true,
		/*bSaveContentPackages*/ true);
}

void FHarborSuiteActions::PrefixActorLabelsOnSelection(const FString& Prefix)
{
	if (!GEditor)
	{
		return;
	}

	USelection* SelectedActors = GEditor->GetSelectedActors();
	if (!SelectedActors || SelectedActors->Num() == 0)
	{
		return;
	}

	const FString UsePrefix = Prefix.IsEmpty() ? FString(TEXT("Harbor_")) : Prefix;

	FScopedTransaction Transaction(LOCTEXT("HarborPrefixTx", "Harbor Stowage: prefix actor labels"));
	for (FSelectionIterator It(*SelectedActors); It; ++It)
	{
		if (AActor* Actor = Cast<AActor>(*It))
		{
			Actor->Modify();
			const FString OldLabel = Actor->GetActorLabel();
			if (!OldLabel.StartsWith(UsePrefix))
			{
				Actor->SetActorLabel(UsePrefix + OldLabel);
			}
		}
	}
}

void FHarborSuiteActions::ResetPiePlayerToFirstPlayerStart()
{
	UWorld* World = FindFirstPieWorld();
	if (!World)
	{
		return;
	}

	APlayerStart* FirstStart = nullptr;
	for (TActorIterator<APlayerStart> It(World); It; ++It)
	{
		FirstStart = *It;
		break;
	}

	if (!FirstStart)
	{
		return;
	}

	if (APawn* Pawn = UGameplayStatics::GetPlayerPawn(World, 0))
	{
		Pawn->SetActorTransform(FirstStart->GetActorTransform(), false, nullptr, ETeleportType::TeleportPhysics);
	}
}

void FHarborSuiteActions::SetPieGlobalTimeDilation(float Dilation)
{
	UWorld* World = FindFirstPieWorld();
	if (!World)
	{
		return;
	}

	const float Clamped = FMath::Clamp(Dilation, 0.0001f, 20.f);
	UGameplayStatics::SetGlobalTimeDilation(World, Clamped);
}

void FHarborSuiteActions::BuildClearanceReport(FHarborClearanceReport& OutReport)
{
	OutReport = FHarborClearanceReport();

	UWorld* World = GetEditorWorld();
	if (!World)
	{
		OutReport.SummaryText = TEXT("No editor world available (open a level).");
		return;
	}

	int32 MeshActors = 0;
	int32 Lights = 0;
	int32 Problems = 0;

	for (TActorIterator<AActor> It(World); It; ++It)
	{
		AActor* Actor = *It;
		if (!Actor)
		{
			continue;
		}

		++OutReport.TotalActors;

		if (Actor->FindComponentByClass<UStaticMeshComponent>())
		{
			++MeshActors;
		}

		if (Cast<APointLight>(Actor))
		{
			++Lights;
		}

		if (Actor->GetActorLabel().Contains(TEXT("Problem"), ESearchCase::IgnoreCase))
		{
			++Problems;
		}
	}

	OutReport.StaticMeshActors = MeshActors;
	OutReport.PointLights = Lights;
	OutReport.ProblemLabelActors = Problems;

	OutReport.SummaryText = FString::Printf(
		TEXT("Actors: %d\nWith static mesh component: %d\nPoint lights: %d\nLabels containing \"Problem\": %d"),
		OutReport.TotalActors,
		OutReport.StaticMeshActors,
		OutReport.PointLights,
		OutReport.ProblemLabelActors);
}

void FHarborSuiteActions::SelectActorsWithProblemInLabel()
{
	if (!GEditor)
	{
		return;
	}

	UWorld* World = GetEditorWorld();
	if (!World)
	{
		return;
	}

	GEditor->SelectNone(false, true);

	for (TActorIterator<AActor> It(World); It; ++It)
	{
		AActor* Actor = *It;
		if (Actor && Actor->GetActorLabel().Contains(TEXT("Problem"), ESearchCase::IgnoreCase))
		{
			GEditor->SelectActor(Actor, true, false);
		}
	}
}

#undef LOCTEXT_NAMESPACE
