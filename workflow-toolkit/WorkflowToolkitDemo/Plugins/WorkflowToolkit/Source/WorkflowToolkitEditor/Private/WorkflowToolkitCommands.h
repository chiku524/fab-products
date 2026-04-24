// Copyright (c) Immersive Labs. All Rights Reserved.

#pragma once

#include "Framework/Commands/Commands.h"

class FUICommandInfo;

/**
 * Editor commands for Workflow Toolkit. Defaults can be changed in
 * Editor Preferences → General → Keyboard Shortcuts (search "Workflow Toolkit").
 */
class FWorkflowToolkitCommands : public TCommands<FWorkflowToolkitCommands>
{
public:
	FWorkflowToolkitCommands();

	virtual void RegisterCommands() override;

	TSharedPtr<FUICommandInfo> OpenWorkflowToolkitPanel;
	TSharedPtr<FUICommandInfo> FrameSelectionInViewport;
	TSharedPtr<FUICommandInfo> SelectAllActorsSameClass;
	TSharedPtr<FUICommandInfo> SnapActorLocationsIntegerGrid;
	TSharedPtr<FUICommandInfo> SelectAllActorsSameStaticMesh;
	TSharedPtr<FUICommandInfo> SetStaticMeshMobilityStatic;
	TSharedPtr<FUICommandInfo> AlignSelectionBottomToFloor;
	TSharedPtr<FUICommandInfo> DuplicateSelection;
	TSharedPtr<FUICommandInfo> SaveAllDirtyPackages;
	TSharedPtr<FUICommandInfo> SyncContentBrowserToSelection;
	TSharedPtr<FUICommandInfo> OpenProjectSettingsEngineGeneral;
	TSharedPtr<FUICommandInfo> OpenPluginsEditor;
	TSharedPtr<FUICommandInfo> OpenWorldSettings;
	TSharedPtr<FUICommandInfo> OpenOutputLog;
	TSharedPtr<FUICommandInfo> OpenMessageLog;
	TSharedPtr<FUICommandInfo> OpenKeyboardShortcutsSettings;
	TSharedPtr<FUICommandInfo> CopyActorPathsToClipboard;
	TSharedPtr<FUICommandInfo> SnapRotationTo90DegreeGrid;
	TSharedPtr<FUICommandInfo> SelectAllActorsSameMaterial;
	TSharedPtr<FUICommandInfo> OpenStaticMeshAssetFromSelection;
	TSharedPtr<FUICommandInfo> RunMapCheck;
};
