// Copyright (c) Immersive Labs. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "EditorSubsystem.h"
#include "HarborSuiteEditorSubsystem.generated.h"

/**
 * Persists Charts (runbook) completion per project under Saved/HarborSuite/ChartsState.json.
 */
UCLASS()
class UHarborSuiteEditorSubsystem : public UEditorSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	static FName DefaultRunbookId() { return FName(TEXT("VerticalSlice")); }

	int32 GetStepCount() const;

	FText GetStepTitle(int32 Index) const;
	FText GetStepHint(int32 Index) const;

	bool IsStepDone(int32 Index) const;
	void SetStepDone(int32 Index, bool bDone);

	void ResetActiveRunbook();

private:
	void LoadFromDisk();
	void SaveToDisk();
	FString GetStateFilePath() const;

	void EnsureCompletionMatchesDefinition();

	TArray<bool> StepCompletion;
};
