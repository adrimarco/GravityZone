// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class GravityZoneEditorTarget : TargetRules
{
	public GravityZoneEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V4;
		IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_5;
        DefaultBuildSettings = BuildSettingsVersion.V5;
        ExtraModuleNames.Add("GravityZone");
	}
}
