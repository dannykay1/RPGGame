// Copyright Danny Kay 2021.

using UnrealBuildTool;
using System.Collections.Generic;

public class RPGGameEditorTarget : TargetRules
{
	public RPGGameEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		ExtraModuleNames.AddRange( new string[] { "RPGGame" } );
	}
}
