using UnrealBuildTool;

public class ExtendedLibrary : ModuleRules
{
	public ExtendedLibrary(ReadOnlyTargetRules Target) : base(Target)
    {
        PrivatePCHHeaderFile = "ExtendedLibraryPCH.h";

        PrivateIncludePaths.AddRange(new[] { "ExtendedLibrary/Private" });
		
		PublicDependencyModuleNames.AddRange(
			new[]
			{
				"Core",
				"CoreUObject",
				"Engine",
				"HTTP",
				"InputCore",
                "NavigationSystem",
                "OnlineSubsystem",
                "PhysXVehicles",
            }
        );

		PrivateDependencyModuleNames.AddRange(
			new[]
			{
				"AIModule",
				"Core",
				"CoreUObject",
				"Engine",
				"GameplayTasks",
				"InputCore",
				"HTTP",
				"OnlineSubsystem",
				"OnlineSubsystemNull",
				"OnlineSubsystemUtils",
				"Sockets",
				"Networking",
				"AssetRegistry",
				"UMG",
			}
		);
	}
}