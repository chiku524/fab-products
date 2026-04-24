// Copyright (c) Immersive Labs. All Rights Reserved.

#include "HarborSuiteRuntimeSubsystem.h"

#include "Engine/Engine.h"
#include "Engine/GameInstance.h"
#include "Engine/World.h"
#include "EngineUtils.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/PlayerStart.h"
#include "GameFramework/Pawn.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

void UHarborSuiteRuntimeSubsystem::ResetPlayerToFirstPlayerStart()
{
	UWorld* World = GetGameInstance() ? GetGameInstance()->GetWorld() : nullptr;
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
		PrintHarborMessage(TEXT("Harbor Shakedown: No PlayerStart found in this world."), 3.f);
		return;
	}

	if (APawn* Pawn = UGameplayStatics::GetPlayerPawn(World, 0))
	{
		Pawn->SetActorTransform(FirstStart->GetActorTransform(), false, nullptr, ETeleportType::TeleportPhysics);
		PrintHarborMessage(TEXT("Harbor Shakedown: Player moved to first PlayerStart."), 2.f);
	}
}

void UHarborSuiteRuntimeSubsystem::SetGlobalTimeDilationSafe(float TimeDilation)
{
	UWorld* World = GetGameInstance() ? GetGameInstance()->GetWorld() : nullptr;
	if (!World)
	{
		return;
	}

	const float Clamped = FMath::Clamp(TimeDilation, 0.0001f, 20.f);
	UGameplayStatics::SetGlobalTimeDilation(World, Clamped);
}

void UHarborSuiteRuntimeSubsystem::SetGamePausedSafe(bool bPaused)
{
	UWorld* World = GetGameInstance() ? GetGameInstance()->GetWorld() : nullptr;
	if (!World)
	{
		return;
	}

	if (APlayerController* PC = World->GetFirstPlayerController())
	{
		PC->SetPause(bPaused);
	}
}

void UHarborSuiteRuntimeSubsystem::FocusViewOnActorSafe(AActor* TargetActor, float BlendTimeSeconds)
{
	if (!TargetActor)
	{
		return;
	}

	UWorld* World = GetGameInstance() ? GetGameInstance()->GetWorld() : nullptr;
	if (!World)
	{
		return;
	}

	if (APlayerController* PC = World->GetFirstPlayerController())
	{
		const float UseBlend = BlendTimeSeconds > 0.f ? BlendTimeSeconds : 0.25f;
		PC->SetViewTargetWithBlend(TargetActor, UseBlend);
	}
}

void UHarborSuiteRuntimeSubsystem::PrintHarborMessage(const FString& Message, float DurationSeconds)
{
	UWorld* World = GetGameInstance() ? GetGameInstance()->GetWorld() : nullptr;
	if (!World)
	{
		return;
	}

	UKismetSystemLibrary::PrintString(World, Message, true, true, FLinearColor(0.2f, 0.85f, 0.95f, 1.f), DurationSeconds);
}
