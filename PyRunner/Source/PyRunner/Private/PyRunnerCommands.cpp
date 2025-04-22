// Copyright Epic Games, Inc. All Rights Reserved.

#include "PyRunnerCommands.h"

#define LOCTEXT_NAMESPACE "FPyRunnerModule"

void FPyRunnerCommands::RegisterCommands()
{
	UI_COMMAND(Script_01, "Script_01", "", EUserInterfaceActionType::Button, FInputGesture());
	UI_COMMAND(Script_02, "Script_02", "", EUserInterfaceActionType::Button, FInputGesture());
	UI_COMMAND(Script_03, "Script_03", "", EUserInterfaceActionType::Button, FInputGesture());
	UI_COMMAND(Script_04, "Script_04", "", EUserInterfaceActionType::Button, FInputGesture());
	UI_COMMAND(Script_05, "Script_05", "", EUserInterfaceActionType::Button, FInputGesture());
	UI_COMMAND(Script_06, "Script_06", "", EUserInterfaceActionType::Button, FInputGesture());
	UI_COMMAND(Script_07, "Script_07", "", EUserInterfaceActionType::Button, FInputGesture());
	UI_COMMAND(Script_08, "Script_08", "", EUserInterfaceActionType::Button, FInputGesture());
	UI_COMMAND(RefreshScripts, "Refresh Scripts", "", EUserInterfaceActionType::Button, FInputGesture());
	UI_COMMAND(OpenScriptsDirectory, "Open Scripts Directory", "", EUserInterfaceActionType::Button, FInputGesture());
}

#undef LOCTEXT_NAMESPACE
