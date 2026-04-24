// Copyright (c) Immersive Labs. All Rights Reserved.

using UnrealBuildTool;

public class WorkflowToolkitRuntime : ModuleRules
{
	public WorkflowToolkitRuntime(ReadOnlyTargetRules Target) : base(Target)
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
