// Copyright (c) Immersive Labs. All Rights Reserved.

using UnrealBuildTool;

public class WorldBuilderTemplatesEditor : ModuleRules
{
	public WorldBuilderTemplatesEditor(ReadOnlyTargetRules Target) : base(Target)
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
				"InputCore",
				"UnrealEd",
				"Slate",
				"SlateCore",
				"ToolMenus",
				"EditorStyle",
				"EditorWidgets",
				"Projects",
				"LevelEditor",
				"WorkspaceMenuStructure",
				"AssetRegistry",
				"DeveloperSettings",
			}
		);
	}
}
