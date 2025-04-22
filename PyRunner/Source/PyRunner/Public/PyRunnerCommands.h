// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "PyRunnerStyle.h"

class FPyRunnerCommands : public TCommands<FPyRunnerCommands>
{
public:

	FPyRunnerCommands()
		: TCommands<FPyRunnerCommands>(TEXT("PyRunner"), NSLOCTEXT("Contexts", "PyRunner", "PyRunner Plugin"), NAME_None, FPyRunnerStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > Script_01;
	TSharedPtr< FUICommandInfo > Script_02;
	TSharedPtr< FUICommandInfo > Script_03;
	TSharedPtr< FUICommandInfo > Script_04;
	TSharedPtr< FUICommandInfo > Script_05;
	TSharedPtr< FUICommandInfo > Script_06;
	TSharedPtr< FUICommandInfo > Script_07;
	TSharedPtr< FUICommandInfo > Script_08;

	TSharedPtr< FUICommandInfo > RefreshScripts;
	TSharedPtr< FUICommandInfo > OpenScriptsDirectory;
};
