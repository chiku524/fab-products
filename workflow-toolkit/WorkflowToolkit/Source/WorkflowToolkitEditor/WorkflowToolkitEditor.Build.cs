// Copyright (c) Immersive Labs. All Rights Reserved.

using UnrealBuildTool;

public class WorkflowToolkitEditor : ModuleRules
{
	public WorkflowToolkitEditor(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"CoreUObject",
				"Engine",
			}
		);

		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"ApplicationCore",
				"UnrealEd",
				"Slate",
				"SlateCore",
				"ToolMenus",
				"EditorStyle",
				"EditorWidgets",
				"Projects",
				"LevelEditor",
				"WorkspaceMenuStructure",
				"EditorSubsystem",
				"ContentBrowser",
				"Settings",
				"InputCore",
			}
		);
	}
}
