using UnrealBuildTool;

public class ExtendedLibrary : ModuleRules
{
    public ExtendedLibrary(TargetInfo target)
    {
        PrivateIncludePaths.AddRange(new[] { "ExtendedLibrary/Private" });
		
		PublicIncludePaths.AddRange(new[] { "ExtendedLibrary/Public" });

        PrivateDependencyModuleNames.AddRange(
            new[]
            {
                "Engine",
                "InputCore",
                "Core",
                "Slate",
                "SlateCore",
                "EditorStyle",
                "CoreUObject"
            }
        );
    }
}