// Copyright (c) Immersive Labs. All Rights Reserved.

#include "WorkflowToolkitActions.h"

#include "CollisionQueryParams.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/StaticMeshComponent.h"
#include "ContentBrowserModule.h"
#include "Editor.h"
#include "HAL/PlatformApplicationMisc.h"
#include "Materials/MaterialInterface.h"
#include "Subsystems/AssetEditorSubsystem.h"
#include "Engine/World.h"
#include "EngineUtils.h"
#include "FileHelpers.h"
#include "Framework/Docking/TabManager.h"
#include "IContentBrowserSingleton.h"
#include "ISettingsModule.h"
#include "LevelEditor.h"
#include "Modules/ModuleManager.h"
#include "Selection.h"
#include "UnrealEdGlobals.h"

void FWorkflowToolkitActions::FrameSelectionInActiveViewport()
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

	FBox Bounds(ForceInit);
	for (FSelectionIterator It(*SelectedActors); It; ++It)
	{
		if (AActor* Actor = Cast<AActor>(*It))
		{
			Bounds += Actor->GetComponentsBoundingBox(true);
		}
	}

	if (Bounds.GetVolume() <= KINDA_SMALL_NUMBER)
	{
		return;
	}

	GEditor->MoveViewportCamerasToBox(Bounds, /*bActiveViewportOnly=*/true);
}

void FWorkflowToolkitActions::SelectAllActorsOfSameClassAsFirstSelection()
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

	AActor* FirstActor = nullptr;
	for (FSelectionIterator It(*SelectedActors); It; ++It)
	{
		FirstActor = Cast<AActor>(*It);
		if (FirstActor)
		{
			break;
		}
	}

	if (!FirstActor)
	{
		return;
	}

	UWorld* World = FirstActor->GetWorld();
	if (!World)
	{
		return;
	}

	const UClass* ActorClass = FirstActor->GetClass();

	GEditor->SelectNone(false, true);

	for (TActorIterator<AActor> It(World); It; ++It)
	{
		AActor* Actor = *It;
		if (Actor && Actor->GetClass() == ActorClass)
		{
			GEditor->SelectActor(Actor, true, false);
		}
	}
}

void FWorkflowToolkitActions::SaveAllDirtyPackagesWithoutPrompt()
{
	UEditorLoadingAndSavingUtils::SaveDirtyPackages(
		/*bSaveMapPackages*/ true,
		/*bSaveContentPackages*/ true);
}

void FWorkflowToolkitActions::SyncContentBrowserToSelection()
{
	if (!GEditor)
	{
		return;
	}

	FContentBrowserModule& ContentBrowserModule = FModuleManager::LoadModuleChecked<FContentBrowserModule>(TEXT("ContentBrowser"));
	IContentBrowserSingleton& ContentBrowser = ContentBrowserModule.Get();

	TArray<UObject*> ObjectsToSync;

	USelection* ObjectSelection = GEditor->GetSelectedObjects();
	if (ObjectSelection && ObjectSelection->Num() > 0)
	{
		for (FSelectionIterator It(*ObjectSelection); It; ++It)
		{
			if (UObject* Obj = *It)
			{
				ObjectsToSync.Add(Obj);
				break;
			}
		}
	}

	if (ObjectsToSync.Num() == 0)
	{
		USelection* ActorSelection = GEditor->GetSelectedActors();
		if (ActorSelection && ActorSelection->Num() > 0)
		{
			for (FSelectionIterator It(*ActorSelection); It; ++It)
			{
				AActor* Actor = Cast<AActor>(*It);
				if (!Actor)
				{
					continue;
				}

				TArray<UActorComponent*> Components;
				Actor->GetComponents(Components);
				for (UActorComponent* Component : Components)
				{
					if (UStaticMeshComponent* SMC = Cast<UStaticMeshComponent>(Component))
					{
						if (UStaticMesh* Mesh = SMC->GetStaticMesh())
						{
							ObjectsToSync.Add(Mesh);
							break;
						}
					}
					if (USkeletalMeshComponent* SKC = Cast<USkeletalMeshComponent>(Component))
					{
						if (USkeletalMesh* Mesh = SKC->GetSkeletalMeshAsset())
						{
							ObjectsToSync.Add(Mesh);
							break;
						}
					}
				}

				if (ObjectsToSync.Num() > 0)
				{
					break;
				}
			}
		}
	}

	if (ObjectsToSync.Num() > 0)
	{
		ContentBrowser.SyncBrowserToAssets(ObjectsToSync);
	}
}

void FWorkflowToolkitActions::OpenOutputLogTab()
{
	FGlobalTabmanager::Get()->TryInvokeTab(FTabId(TEXT("OutputLog")));
}

void FWorkflowToolkitActions::OpenMessageLogTab()
{
	FGlobalTabmanager::Get()->TryInvokeTab(FTabId(TEXT("MessageLog")));
}

void FWorkflowToolkitActions::SnapSelectedActorLocationsToIntegerGrid()
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

	for (FSelectionIterator It(*SelectedActors); It; ++It)
	{
		AActor* Actor = Cast<AActor>(*It);
		if (!Actor)
		{
			continue;
		}

		const FVector Loc = Actor->GetActorLocation();
		const FVector Snapped(
			FMath::RoundToFloat(Loc.X),
			FMath::RoundToFloat(Loc.Y),
			FMath::RoundToFloat(Loc.Z));
		Actor->SetActorLocation(Snapped, false, nullptr, ETeleportType::TeleportPhysics);
	}
}

void FWorkflowToolkitActions::SelectAllActorsUsingSameStaticMeshAsFirstSelection()
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

	UStaticMesh* TargetMesh = nullptr;
	AActor* ReferenceActor = nullptr;

	for (FSelectionIterator It(*SelectedActors); It; ++It)
	{
		AActor* Actor = Cast<AActor>(*It);
		if (!Actor)
		{
			continue;
		}

		TArray<UActorComponent*> Components;
		Actor->GetComponents(Components);
		for (UActorComponent* Component : Components)
		{
			if (UStaticMeshComponent* SMC = Cast<UStaticMeshComponent>(Component))
			{
				if (UStaticMesh* Mesh = SMC->GetStaticMesh())
				{
					TargetMesh = Mesh;
					ReferenceActor = Actor;
					break;
				}
			}
		}

		if (TargetMesh)
		{
			break;
		}
	}

	if (!TargetMesh || !ReferenceActor)
	{
		return;
	}

	UWorld* World = ReferenceActor->GetWorld();
	if (!World)
	{
		return;
	}

	GEditor->SelectNone(false, true);

	for (TActorIterator<AActor> It(World); It; ++It)
	{
		AActor* Actor = *It;
		if (!Actor)
		{
			continue;
		}

		TArray<UActorComponent*> Components;
		Actor->GetComponents(Components);
		for (UActorComponent* Component : Components)
		{
			if (UStaticMeshComponent* SMC = Cast<UStaticMeshComponent>(Component))
			{
				if (SMC->GetStaticMesh() == TargetMesh)
				{
					GEditor->SelectActor(Actor, true, false);
					break;
				}
			}
		}
	}
}

void FWorkflowToolkitActions::SetSelectedStaticMeshComponentsMobilityStatic()
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

	for (FSelectionIterator It(*SelectedActors); It; ++It)
	{
		AActor* Actor = Cast<AActor>(*It);
		if (!Actor)
		{
			continue;
		}

		TArray<UActorComponent*> Components;
		Actor->GetComponents(Components);
		for (UActorComponent* Component : Components)
		{
			if (UStaticMeshComponent* SMC = Cast<UStaticMeshComponent>(Component))
			{
				SMC->Modify();
				SMC->SetMobility(EComponentMobility::Static);
			}
		}
	}

	GEditor->RedrawLevelEditingViewports(true);
}

void FWorkflowToolkitActions::AlignSelectedActorsBottomToFloorTrace()
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

	for (FSelectionIterator It(*SelectedActors); It; ++It)
	{
		AActor* Actor = Cast<AActor>(*It);
		if (!Actor)
		{
			continue;
		}

		UWorld* World = Actor->GetWorld();
		if (!World)
		{
			continue;
		}

		FVector Origin;
		FVector BoxExtent;
		Actor->GetActorBounds(false, Origin, BoxExtent, false);
		const float BottomZ = Origin.Z - BoxExtent.Z;

		const FVector TraceStart = Origin + FVector(0.f, 0.f, 100000.f);
		const FVector TraceEnd = Origin - FVector(0.f, 0.f, 100000.f);

		FCollisionQueryParams Params(SCENE_QUERY_STAT(WorkflowToolkitFloorAlign), /*bTraceComplex=*/ false, Actor);
		FHitResult Hit;
		if (World->LineTraceSingleByChannel(Hit, TraceStart, TraceEnd, ECC_Visibility, Params) && Hit.bBlockingHit)
		{
			const float DeltaZ = Hit.ImpactPoint.Z - BottomZ;
			Actor->AddActorWorldOffset(FVector(0.f, 0.f, DeltaZ), false, nullptr, ETeleportType::TeleportPhysics);
		}
	}
}

void FWorkflowToolkitActions::DuplicateSelectedActors()
{
	if (!GEditor)
	{
		return;
	}

	UWorld* World = GEditor->GetEditorWorldContext().World();
	if (!World)
	{
		return;
	}

	GEditor->Exec(World, TEXT("DUPLICATE"));
}

void FWorkflowToolkitActions::ExecuteEditorConsoleCommand(const FString& Command)
{
	if (!GEditor || Command.IsEmpty())
	{
		return;
	}

	UWorld* World = GEditor->GetEditorWorldContext().World();
	if (!World)
	{
		return;
	}

	GEditor->Exec(World, *Command);
}

void FWorkflowToolkitActions::OpenProjectSettingsEngineGeneral()
{
	FModuleManager::LoadModuleChecked<ISettingsModule>(TEXT("Settings")).ShowViewer(TEXT("Project"), TEXT("Engine"), TEXT("General"));
}

void FWorkflowToolkitActions::OpenPluginsEditorTab()
{
	FGlobalTabmanager::Get()->TryInvokeTab(FTabId(TEXT("PluginsEditor")));
}

void FWorkflowToolkitActions::OpenWorldSettingsTab()
{
	FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>(TEXT("LevelEditor"));
	if (const TSharedPtr<FTabManager> TabManager = LevelEditorModule.GetLevelEditorTabManager())
	{
		TabManager->TryInvokeTab(FName(TEXT("WorldSettingsTab")));
	}
}

void FWorkflowToolkitActions::OpenEditorKeyboardShortcutsSettings()
{
	FModuleManager::LoadModuleChecked<ISettingsModule>(TEXT("Settings")).ShowViewer(TEXT("Editor"), TEXT("General"), TEXT("InputBindings"));
}

void FWorkflowToolkitActions::CopySelectedActorPathsToClipboard()
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

	FString Lines;
	for (FSelectionIterator It(*SelectedActors); It; ++It)
	{
		if (AActor* Actor = Cast<AActor>(*It))
		{
			Lines += Actor->GetPathName();
			Lines += LINE_TERMINATOR;
		}
	}

	if (!Lines.IsEmpty())
	{
		FPlatformApplicationMisc::ClipboardCopy(*Lines);
	}
}

void FWorkflowToolkitActions::SnapSelectedActorsRotationToNearestRightAngles()
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

	constexpr float Step = 90.f;
	for (FSelectionIterator It(*SelectedActors); It; ++It)
	{
		AActor* Actor = Cast<AActor>(*It);
		if (!Actor)
		{
			continue;
		}

		FRotator R = Actor->GetActorRotation();
		R.Roll = FMath::GridSnap(R.Roll, Step);
		R.Pitch = FMath::GridSnap(R.Pitch, Step);
		R.Yaw = FMath::GridSnap(R.Yaw, Step);
		Actor->Modify();
		Actor->SetActorRotation(R);
	}

	GEditor->RedrawLevelEditingViewports(true);
}

void FWorkflowToolkitActions::SelectAllActorsUsingSameMaterialAsFirstStaticMeshSelection()
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

	UMaterialInterface* TargetMaterial = nullptr;
	AActor* ReferenceActor = nullptr;

	for (FSelectionIterator It(*SelectedActors); It; ++It)
	{
		AActor* Actor = Cast<AActor>(*It);
		if (!Actor)
		{
			continue;
		}

		TArray<UActorComponent*> Components;
		Actor->GetComponents(Components);
		for (UActorComponent* Component : Components)
		{
			if (UStaticMeshComponent* SMC = Cast<UStaticMeshComponent>(Component))
			{
				if (UMaterialInterface* M = SMC->GetMaterial(0))
				{
					TargetMaterial = M;
					ReferenceActor = Actor;
					break;
				}
			}
		}

		if (TargetMaterial)
		{
			break;
		}
	}

	if (!TargetMaterial || !ReferenceActor)
	{
		return;
	}

	UWorld* World = ReferenceActor->GetWorld();
	if (!World)
	{
		return;
	}

	GEditor->SelectNone(false, true);

	for (TActorIterator<AActor> It(World); It; ++It)
	{
		AActor* Actor = *It;
		if (!Actor)
		{
			continue;
		}

		TArray<UActorComponent*> Components;
		Actor->GetComponents(Components);
		for (UActorComponent* Component : Components)
		{
			if (UStaticMeshComponent* SMC = Cast<UStaticMeshComponent>(Component))
			{
				if (SMC->GetMaterial(0) == TargetMaterial)
				{
					GEditor->SelectActor(Actor, true, false);
					break;
				}
			}
		}
	}
}

void FWorkflowToolkitActions::OpenFirstStaticMeshFromSelectionInAssetEditor()
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

	UStaticMesh* Mesh = nullptr;
	for (FSelectionIterator It(*SelectedActors); It; ++It)
	{
		AActor* Actor = Cast<AActor>(*It);
		if (!Actor)
		{
			continue;
		}

		TArray<UActorComponent*> Components;
		Actor->GetComponents(Components);
		for (UActorComponent* Component : Components)
		{
			if (UStaticMeshComponent* SMC = Cast<UStaticMeshComponent>(Component))
			{
				if (UStaticMesh* M = SMC->GetStaticMesh())
				{
					Mesh = M;
					break;
				}
			}
		}

		if (Mesh)
		{
			break;
		}
	}

	if (!Mesh)
	{
		return;
	}

	if (UAssetEditorSubsystem* AssetEditorSubsystem = GEditor->GetEditorSubsystem<UAssetEditorSubsystem>())
	{
		AssetEditorSubsystem->OpenEditorForAsset(Mesh);
	}
}

void FWorkflowToolkitActions::RunMapCheck()
{
	if (!GEditor)
	{
		return;
	}

	UWorld* World = GEditor->GetEditorWorldContext().World();
	if (!World)
	{
		return;
	}

	GEditor->Exec(World, TEXT("MAP CHECK"));
}
