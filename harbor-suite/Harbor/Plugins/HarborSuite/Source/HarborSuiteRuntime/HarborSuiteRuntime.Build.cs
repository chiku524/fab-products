// Copyright (c) Immersive Labs. All Rights Reserved.

using UnrealBuildTool;

public class HarborSuiteRuntime : ModuleRules
{
	public HarborSuiteRuntime(ReadOnlyTargetRules Target) : base(Target)
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
	}
}
