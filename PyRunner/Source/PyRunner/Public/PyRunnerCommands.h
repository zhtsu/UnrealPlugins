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
	TSharedPtr< FUICommandInfo > PluginAction;
};
