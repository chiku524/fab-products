// Copyright (c) Immersive Labs. All Rights Reserved.

#pragma once

#include "Modules/ModuleInterface.h"

class FSpawnTabArgs;
class SDockTab;

class FWorldBuilderTemplatesEditorModule : public IModuleInterface
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

private:
	TSharedRef<SDockTab> SpawnWorldBuilderTemplatesTab(const FSpawnTabArgs& Args);
};
