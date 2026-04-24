// Copyright (c) Immersive Labs. All Rights Reserved.

using UnrealBuildTool;

public class HarborSuiteEditor : ModuleRules
{
	public HarborSuiteEditor(ReadOnlyTargetRules Target) : base(Target)
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
				"Json",
				"InputCore",
				"HarborSuiteRuntime",
			}
		);
	}
}
