// Copyright (c) [PUBLISHER_NAME]. All Rights Reserved.

using UnrealBuildTool;

public class WorldBuilderAuditConvertEditor : ModuleRules
{
	public WorldBuilderAuditConvertEditor(ReadOnlyTargetRules Target) : base(Target)
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
			}
		);
	}
}
