// Copyright (c) Immersive Labs. All Rights Reserved.

using UnrealBuildTool;

public class LevelSelectionSetsEditor : ModuleRules
{
	public LevelSelectionSetsEditor(ReadOnlyTargetRules Target) : base(Target)
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
				"UnrealEd",
				"Slate",
				"SlateCore",
				"ToolMenus",
				"EditorStyle",
				"EditorWidgets",
				"Projects",
				"LevelEditor",
				"WorkspaceMenu",
			}
		);
	}
}
