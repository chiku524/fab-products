// Copyright (c) Immersive Labs. All Rights Reserved.

#include "WorkflowToolkitRuntimeSubsystem.h"

#include "Engine/Engine.h"
#include "Engine/GameInstance.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Pawn.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

void UWorkflowToolkitRuntimeSubsystem::ExecuteConsoleCommand(const FString& Command)
{
	if (Command.IsEmpty())
	{
		return;
	}

#if UE_BUILD_SHIPPING
	return;
#else
	if (UWorld* World = GetGameInstance() ? GetGameInstance()->GetWorld() : nullptr)
	{
		if (GEngine)
		{
			GEngine->Exec(World, *Command);
		}
	}
#endif
}

void UWorkflowToolkitRuntimeSubsystem::SetGamePaused(bool bPaused)
{
	if (UWorld* World = GetGameInstance() ? GetGameInstance()->GetWorld() : nullptr)
	{
		APlayerController* PC = World->GetFirstPlayerController();
		if (PC)
		{
			PC->SetPause(bPaused);
		}
	}
}

void UWorkflowToolkitRuntimeSubsystem::SetGlobalTimeDilation(float TimeDilation)
{
	if (UWorld* World = GetGameInstance() ? GetGameInstance()->GetWorld() : nullptr)
	{
		UGameplayStatics::SetGlobalTimeDilation(World, TimeDilation);
	}
}

void UWorkflowToolkitRuntimeSubsystem::PrintDebugMessage(const FString& Message, float DurationSeconds, FLinearColor TextColor)
{
	if (UWorld* World = GetGameInstance() ? GetGameInstance()->GetWorld() : nullptr)
	{
		UKismetSystemLibrary::PrintString(World, Message, true, true, TextColor, DurationSeconds);
	}
}

void UWorkflowToolkitRuntimeSubsystem::TeleportFirstPlayerPawnToLocation(const FVector& Location)
{
	if (UWorld* World = GetGameInstance() ? GetGameInstance()->GetWorld() : nullptr)
	{
		if (APawn* Pawn = UGameplayStatics::GetPlayerPawn(World, 0))
		{
			Pawn->SetActorLocation(Location, false, nullptr, ETeleportType::TeleportPhysics);
		}
	}
}

void UWorkflowToolkitRuntimeSubsystem::FocusViewOnActor(AActor* TargetActor, float BlendTime)
{
	if (!TargetActor)
	{
		return;
	}

	if (UWorld* World = GetGameInstance() ? GetGameInstance()->GetWorld() : nullptr)
	{
		if (APlayerController* PC = World->GetFirstPlayerController())
		{
			const float UseBlend = BlendTime > 0.f ? BlendTime : 0.25f;
			PC->SetViewTargetWithBlend(TargetActor, UseBlend);
		}
	}
}
