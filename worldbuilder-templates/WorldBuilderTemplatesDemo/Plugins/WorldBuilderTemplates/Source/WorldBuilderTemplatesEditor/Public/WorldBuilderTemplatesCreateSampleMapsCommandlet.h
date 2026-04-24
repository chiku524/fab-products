// Copyright (c) Immersive Labs. All Rights Reserved.

#pragma once

#include "Commandlets/Commandlet.h"
#include "WorldBuilderTemplatesCreateSampleMapsCommandlet.generated.h"

/**
 * Editor commandlet: creates starter .umap assets under the plugin Content folder.
 * Run: UnrealEditor-Cmd.exe Your.uproject -run=WorldBuilderTemplatesCreateSampleMaps -unattended -log
 */
UCLASS()
class UWorldBuilderTemplatesCreateSampleMapsCommandlet : public UCommandlet
{
	GENERATED_BODY()

public:
	UWorldBuilderTemplatesCreateSampleMapsCommandlet();

	virtual int32 Main(const FString& Params) override;
};
