using UnrealBuildTool;

public class ExtendedLibrary : ModuleRules
{
    public ExtendedLibrary(TargetInfo target)
    {
        PrivateIncludePaths.AddRange(new[] { "ExtendedLibrary/Private" });
		
		PublicIncludePaths.AddRange(new[] { "ExtendedLibrary/Public" });

        PublicDependencyModuleNames.AddRange(
            new[]
            {
                "Core",
                "CoreUObject",
                "Engine",
                "InputCore",
                "HTTP",
                "OnlineSubsystem",
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