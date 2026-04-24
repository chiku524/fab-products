// Copyright (c) Immersive Labs. All Rights Reserved.

#include "HarborSuiteEditorSubsystem.h"

#include "Dom/JsonObject.h"
#include "HAL/PlatformFileManager.h"
#include "Misc/FileHelper.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"
#include "Serialization/JsonWriter.h"

#define LOCTEXT_NAMESPACE "HarborSuiteEditorSubsystem"

namespace HarborSuiteRunbook
{
	struct FStepDef
	{
		FName Id;
		FText Title;
		FText Hint;
	};

	static const TArray<FStepDef>& VerticalSlice()
	{
		static const TArray<FStepDef> Steps = {
			{
				FName(TEXT("SaveDirty")),
				LOCTEXT("StepSaveDirtyTitle", "Save dirty packages"),
				LOCTEXT("StepSaveDirtyHint", "Hero action: save maps and content without a modal prompt. Use before you share a build or end the day."),
			},
			{
				FName(TEXT("ClearanceScan")),
				LOCTEXT("StepClearanceTitle", "Run a Clearance scan"),
				LOCTEXT("StepClearanceHint", "Open the Clearance pillar and review counts/outliers so surprises surface early."),
			},
			{
				FName(TEXT("ShakedownLoop")),
				LOCTEXT("StepShakedownTitle", "Shorten your PIE loop"),
				LOCTEXT("StepShakedownHint", "Use Shakedown: reset to PlayerStart or adjust time dilation while PIE is running."),
			},
			{
				FName(TEXT("StowagePass")),
				LOCTEXT("StepStowageTitle", "Tidy labels you touch most"),
				LOCTEXT("StepStowageHint", "Use Stowage to prefix actor labels in your current selection for readable Outliner hygiene."),
			},
			{
				FName(TEXT("ShipNotes")),
				LOCTEXT("StepNotesTitle", "Capture ship notes"),
				LOCTEXT("StepNotesHint", "Jot what changed in your vertical slice (paper, Notion, issue tracker—Harbor does not replace your notes)."),
			},
		};
		return Steps;
	}
}

void UHarborSuiteEditorSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	LoadFromDisk();
	EnsureCompletionMatchesDefinition();
}

FString UHarborSuiteEditorSubsystem::GetStateFilePath() const
{
	return FPaths::ProjectSavedDir() / TEXT("HarborSuite") / TEXT("ChartsState.json");
}

void UHarborSuiteEditorSubsystem::EnsureCompletionMatchesDefinition()
{
	const int32 DefCount = HarborSuiteRunbook::VerticalSlice().Num();
	if (StepCompletion.Num() < DefCount)
	{
		const int32 OldCount = StepCompletion.Num();
		StepCompletion.SetNum(DefCount);
		for (int32 i = OldCount; i < DefCount; ++i)
		{
			StepCompletion[i] = false;
		}
	}
	else if (StepCompletion.Num() > DefCount)
	{
		StepCompletion.SetNum(DefCount);
	}
}

int32 UHarborSuiteEditorSubsystem::GetStepCount() const
{
	return HarborSuiteRunbook::VerticalSlice().Num();
}

FText UHarborSuiteEditorSubsystem::GetStepTitle(int32 Index) const
{
	const TArray<HarborSuiteRunbook::FStepDef>& Steps = HarborSuiteRunbook::VerticalSlice();
	if (!Steps.IsValidIndex(Index))
	{
		return FText::GetEmpty();
	}
	return Steps[Index].Title;
}

FText UHarborSuiteEditorSubsystem::GetStepHint(int32 Index) const
{
	const TArray<HarborSuiteRunbook::FStepDef>& Steps = HarborSuiteRunbook::VerticalSlice();
	if (!Steps.IsValidIndex(Index))
	{
		return FText::GetEmpty();
	}
	return Steps[Index].Hint;
}

bool UHarborSuiteEditorSubsystem::IsStepDone(int32 Index) const
{
	return StepCompletion.IsValidIndex(Index) && StepCompletion[Index];
}

void UHarborSuiteEditorSubsystem::SetStepDone(int32 Index, bool bDone)
{
	EnsureCompletionMatchesDefinition();
	if (!StepCompletion.IsValidIndex(Index))
	{
		return;
	}
	StepCompletion[Index] = bDone;
	SaveToDisk();
}

void UHarborSuiteEditorSubsystem::ResetActiveRunbook()
{
	EnsureCompletionMatchesDefinition();
	for (bool& Flag : StepCompletion)
	{
		Flag = false;
	}
	SaveToDisk();
}

void UHarborSuiteEditorSubsystem::LoadFromDisk()
{
	const FString Path = GetStateFilePath();
	StepCompletion.Reset();

	if (!FPaths::FileExists(Path))
	{
		EnsureCompletionMatchesDefinition();
		return;
	}

	FString JsonString;
	if (!FFileHelper::LoadFileToString(JsonString, *Path))
	{
		EnsureCompletionMatchesDefinition();
		return;
	}

	TSharedPtr<FJsonObject> Root;
	const TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(JsonString);
	if (!FJsonSerializer::Deserialize(Reader, Root) || !Root.IsValid())
	{
		EnsureCompletionMatchesDefinition();
		return;
	}

	const FString Key = DefaultRunbookId().ToString();
	const TArray<TSharedPtr<FJsonValue>>* Arr = nullptr;
	if (!Root->TryGetArrayField(Key, Arr) || !Arr)
	{
		EnsureCompletionMatchesDefinition();
		return;
	}

	for (const TSharedPtr<FJsonValue>& V : *Arr)
	{
		StepCompletion.Add(V.IsValid() && V->Type == EJson::Boolean && V->AsBool());
	}

	EnsureCompletionMatchesDefinition();
}

void UHarborSuiteEditorSubsystem::SaveToDisk()
{
	EnsureCompletionMatchesDefinition();

	const FString Dir = FPaths::GetPath(GetStateFilePath());
	FPlatformFileManager::Get().GetPlatformFile().CreateDirectoryTree(*Dir);

	TSharedPtr<FJsonObject> Root = MakeShared<FJsonObject>();
	TArray<TSharedPtr<FJsonValue>> Arr;
	for (bool b : StepCompletion)
	{
		Arr.Add(MakeShared<FJsonValueBoolean>(b));
	}
	Root->SetArrayField(DefaultRunbookId().ToString(), Arr);

	FString Out;
	const TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&Out);
	FJsonSerializer::Serialize(Root.ToSharedRef(), Writer);

	FFileHelper::SaveStringToFile(Out, *GetStateFilePath());
}

#undef LOCTEXT_NAMESPACE
