// Copyright (c) Immersive Labs. All Rights Reserved.

#pragma once

#include "Modules/ModuleInterface.h"

class FSpawnTabArgs;

class FUICommandList;

class SDockTab;

class FWorkflowToolkitEditorModule : public IModuleInterface
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

private:
	void RegisterWorkflowToolkitInput();
	void UnregisterWorkflowToolkitInput();

	TSharedRef<SDockTab> SpawnWorkflowToolkitTab(const FSpawnTabArgs& Args);

	TSharedPtr<FUICommandList> WorkflowToolkitPluginCommands;
};
