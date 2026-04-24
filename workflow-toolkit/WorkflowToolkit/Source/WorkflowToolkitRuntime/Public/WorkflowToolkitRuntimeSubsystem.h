// Copyright (c) Immersive Labs. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "WorkflowToolkitRuntimeSubsystem.generated.h"

class AActor;

/**
 * Runtime companion for dev/artist workflows in PIE and packaged Development builds.
 * Prefer binding these from debug menus or cheat widgets—not shipping UI.
 */
UCLASS()
class WORKFLOWTOOLKITRUNTIME_API UWorkflowToolkitRuntimeSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	/** Runs a console command on the current world (no-op in UE_BUILD_SHIPPING). */
	UFUNCTION(BlueprintCallable, Category = "Workflow Toolkit|Runtime")
	void ExecuteConsoleCommand(const FString& Command);

	UFUNCTION(BlueprintCallable, Category = "Workflow Toolkit|Runtime")
	void SetGamePaused(bool bPaused);

	UFUNCTION(BlueprintCallable, Category = "Workflow Toolkit|Runtime")
	void SetGlobalTimeDilation(float TimeDilation);

	UFUNCTION(BlueprintCallable, Category = "Workflow Toolkit|Runtime")
	void PrintDebugMessage(const FString& Message, float DurationSeconds = 2.f, FLinearColor TextColor = FLinearColor::White);

	UFUNCTION(BlueprintCallable, Category = "Workflow Toolkit|Runtime")
	void TeleportFirstPlayerPawnToLocation(const FVector& Location);

	/** Smoothly blends the first player's camera to view the given actor (uses default player camera manager blend time if BlendTime <= 0). */
	UFUNCTION(BlueprintCallable, Category = "Workflow Toolkit|Runtime")
	void FocusViewOnActor(AActor* TargetActor, float BlendTime = 0.25f);
};
