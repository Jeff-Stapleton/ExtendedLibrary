/*
	Rahs Tool Suite 1.0.0
	-----
	SaxonRah - Robert Chubb @ ParabolicLabs - 30/11/2014 - 3:36 AM
*/
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