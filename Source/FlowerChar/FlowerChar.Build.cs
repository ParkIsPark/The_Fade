// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class FlowerChar : ModuleRules
{
	public FlowerChar(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
	}
}
