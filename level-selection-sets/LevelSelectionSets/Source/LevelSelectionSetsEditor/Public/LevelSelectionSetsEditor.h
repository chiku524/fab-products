// Copyright (c) [PUBLISHER_NAME]. All Rights Reserved.

#pragma once

#include "Modules/ModuleInterface.h"

struct FSpawnTabArgs;

class SDockTab;

class FLevelSelectionSetsEditorModule : public IModuleInterface
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

private:
	TSharedRef<SDockTab> SpawnLevelSelectionSetsTab(const FSpawnTabArgs& Args);
};
