// Copyright (c) Immersive Labs. All Rights Reserved.

#pragma once

#include "Modules/ModuleManager.h"

class FHarborSuiteEditorModule : public IModuleInterface
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

private:
	TSharedRef<class SDockTab> SpawnHarborSuiteTab(const class FSpawnTabArgs& Args);
};
