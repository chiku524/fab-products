// Copyright (c) Immersive Labs. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "HarborSuiteRuntimeSubsystem.generated.h"

class AActor;

/**
 * Optional runtime helpers for Shakedown-style playtest loops (PIE / packaged dev builds).
 * Editor hero actions also call equivalent logic when a PIE world is active.
 */
UCLASS()
class HARBORSUITERUNTIME_API UHarborSuiteRuntimeSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Harbor Suite|Shakedown")
	void ResetPlayerToFirstPlayerStart();

	UFUNCTION(BlueprintCallable, Category = "Harbor Suite|Shakedown")
	void SetGlobalTimeDilationSafe(float TimeDilation);

	UFUNCTION(BlueprintCallable, Category = "Harbor Suite|Shakedown")
	void SetGamePausedSafe(bool bPaused);

	UFUNCTION(BlueprintCallable, Category = "Harbor Suite|Shakedown")
	void FocusViewOnActorSafe(AActor* TargetActor, float BlendTimeSeconds);

	UFUNCTION(BlueprintCallable, Category = "Harbor Suite|Shakedown")
	void PrintHarborMessage(const FString& Message, float DurationSeconds = 2.f);
};
