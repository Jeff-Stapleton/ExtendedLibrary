using UnrealBuildTool;

public class ExtendedLibrary : ModuleRules
{
    public ExtendedLibrary(TargetInfo target)
    {
        PrivateIncludePaths.AddRange(new[] { "ExtendedLibrary/Private" });
		
		PublicIncludePaths.AddRange(new[] { "ExtendedLibrary/Public" });

        PublicDependencyModuleNames.AddRange(
            new string[] 
            {
                "Core",
                "CoreUObject",
                "Engine",
                "InputCore",
                "HTTP",
                "OnlineSubsystem"
            }
        );

        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "AIModule",
                "Core",
                "CoreUObject",
                "Engine",
                "GameplayTasks",
                "InputCore",
                "Slate",
                "SlateCore",
                "HTTP",
                "OnlineSubsystem",
                "OnlineSubsystemNull",
                "OnlineSubsystemUtils",
                "Sockets",
                "Networking",
                "AssetRegistry",
                "MoviePlayer",
                "UMG"
            }
        );
    }
}