// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ServerTestProject : ModuleRules
{
	public ServerTestProject(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" });
	}
}
