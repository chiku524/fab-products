// Copyright (c) Immersive Labs. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class WorkflowToolkitDemoEditorTarget : TargetRules
{
	public WorkflowToolkitDemoEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V6;
		IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_7;
		ExtraModuleNames.AddRange(new string[] { "WorkflowToolkitDemo" });
	}
}
