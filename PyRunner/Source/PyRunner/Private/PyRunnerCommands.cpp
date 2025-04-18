// Copyright Epic Games, Inc. All Rights Reserved.

#include "PyRunnerCommands.h"

#define LOCTEXT_NAMESPACE "FPyRunnerModule"

void FPyRunnerCommands::RegisterCommands()
{
	UI_COMMAND(PluginAction, "PyRunner", "Manage and execute python scripts", EUserInterfaceActionType::Button, FInputGesture());
}

#undef LOCTEXT_NAMESPACE
