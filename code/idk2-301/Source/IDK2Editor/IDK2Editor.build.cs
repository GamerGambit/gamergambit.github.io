// Copyright (c) Tyler Duffus
using UnrealBuildTool;

public class IDK2Editor : ModuleRules
{
    public IDK2Editor(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
        OverridePackageType = PackageOverrideType.GameUncookedOnly;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" });

        PrivateDependencyModuleNames.AddRange(new string[] {
            "BlueprintGraph",
            "IDK2",
            "KismetCompiler",
            "UnrealEd"
        });
    }
}
