// Copyright (c) Immersive Labs. All Rights Reserved.

using UnrealBuildTool;

public class LevelSelectionSetsDemo : ModuleRules
{
	public LevelSelectionSetsDemo(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"CoreUObject",
				"Engine",
				"InputCore",
			}
		);
	}
}
