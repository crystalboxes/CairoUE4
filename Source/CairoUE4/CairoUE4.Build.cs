using UnrealBuildTool;
using System.IO;
public class CairoUE4 : ModuleRules
{
    protected string ThirdPartyPath
    {
        get { return Path.GetFullPath(Path.Combine(ModuleDirectory, "..", "..", "ThirdParty")); }
    }
    public CairoUE4(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
        PrivateIncludePaths.AddRange(new string[] { Path.Combine(ThirdPartyPath, "cairo", "include") });
        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore"});
        bEnableExceptions = true;
        if (LoadCairo(Target)) 
        {
            PublicDefinitions.Add(string.Format("WITH_CAIRO=1"));
            PublicDefinitions.Add("CAIRO_WIN32_STATIC_BUILD");
        } 
        else 
        {
            PublicDefinitions.Add(string.Format("WITH_CAIRO=0"));
        }
    }

    private bool LoadCairo(ReadOnlyTargetRules Target) 
    {
        string LibrariesPath = Path.Combine(ThirdPartyPath, "cairo", "lib");
        if (Target.Platform == UnrealTargetPlatform.Win64)
        {
            LibrariesPath = Path.Combine(LibrariesPath, "Win64");
            PublicAdditionalLibraries.Add(Path.Combine(LibrariesPath, "cairo.lib"));
            return true;
        }
        else if (Target.Platform == UnrealTargetPlatform.Mac)
        {
            LibrariesPath = Path.Combine(LibrariesPath, "Mac");
            PublicAdditionalLibraries.Add(Path.Combine(LibrariesPath, "cairo.a"));
            return true;
        }
        return false;
    }
}
