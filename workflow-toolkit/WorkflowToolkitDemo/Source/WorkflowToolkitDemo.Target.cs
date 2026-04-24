// Copyright (c) Immersive Labs. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class WorkflowToolkitDemoTarget : TargetRules
{
	public WorkflowToolkitDemoTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V6;
		IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_7;
		ExtraModuleNames.AddRange(new string[] { "WorkflowToolkitDemo" });
	}
}
