// Copyright (c) Immersive Labs. All Rights Reserved.

using UnrealBuildTool;

public class WorldBuilderTemplatesDemo : ModuleRules
{
	public WorldBuilderTemplatesDemo(ReadOnlyTargetRules Target) : base(Target)
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
