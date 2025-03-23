// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class GravityZone : ModuleRules
{
	public GravityZone(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "Niagara" });
	}
}
