// Copyright (c) Immersive Labs. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "WorldBuilderTemplatesSettings.generated.h"

/**
 * Project settings: extra content roots to scan for template maps (in addition to this plugin's mount).
 */
UCLASS(Config = EditorPerProjectUserSettings, DefaultConfig, meta = (DisplayName = "World Builder Templates"))
class UWorldBuilderTemplatesSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	UWorldBuilderTemplatesSettings();

	/** Long package path roots (e.g. /Engine/Maps/Templates). Scanned recursively for UWorld assets. */
	UPROPERTY(EditAnywhere, Config, Category = "Template paths", meta = (DisplayName = "Extra package path roots"))
	TArray<FString> ExtraPackagePathRoots;

	virtual FName GetCategoryName() const override;
	virtual FName GetSectionName() const override;
};
