// Copyright (c) Immersive Labs. All Rights Reserved.

using UnrealBuildTool;

public class Harbor : ModuleRules
{
	public Harbor(ReadOnlyTargetRules Target) : base(Target)
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

		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"HarborSuiteRuntime",
			}
		);
	}
}
