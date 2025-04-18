// Copyright Epic Games, Inc. All Rights Reserved.

#include "PyRunner.h"
#include "PyRunnerStyle.h"
#include "PyRunnerCommands.h"
#include "Misc/MessageDialog.h"
#include "ToolMenus.h"

static const FName PyRunnerTabName("PyRunner");

#define LOCTEXT_NAMESPACE "FPyRunnerModule"

void FPyRunnerModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FPyRunnerStyle::Initialize();
	FPyRunnerStyle::ReloadTextures();

	FPyRunnerCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FPyRunnerCommands::Get().PluginAction,
		FExecuteAction::CreateRaw(this, &FPyRunnerModule::PluginButtonClicked),
		FCanExecuteAction());

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FPyRunnerModule::RegisterMenus));
}

void FPyRunnerModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FPyRunnerStyle::Shutdown();

	FPyRunnerCommands::Unregister();
}

void FPyRunnerModule::PluginButtonClicked()
{
	// Put your "OnButtonClicked" stuff here
	FText DialogText = FText::Format(
							LOCTEXT("PluginButtonDialogText", "Add code to {0} in {1} to override this button's actions"),
							FText::FromString(TEXT("FPyRunnerModule::PluginButtonClicked()")),
							FText::FromString(TEXT("PyRunner.cpp"))
					   );
	FMessageDialog::Open(EAppMsgType::Ok, DialogText);
}

void FPyRunnerModule::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);

	{
		UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
		{
			FToolMenuSection& Section = Menu->FindOrAddSection("WindowLayout");
			Section.AddMenuEntryWithCommandList(FPyRunnerCommands::Get().PluginAction, PluginCommands);
		}
	}

	{
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar");
		{
			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("Game");
			{
				// FToolMenuEntry& PyRunnerEntry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FPyRunnerCommands::Get().PluginAction));

				FToolMenuEntry& PyRunnerEntry = Section.AddEntry(FToolMenuEntry::InitComboButton(
					PyRunnerTabName,
					FUIAction(),
					FOnGetContent::CreateLambda([&]()->TSharedRef<SWidget>
					{
						FMenuBuilder MenuBuilder(true, PluginCommands);
				
						MenuBuilder.BeginSection("A");
						
						MenuBuilder.AddMenuEntry(FPyRunnerCommands::Get().PluginAction);
						MenuBuilder.AddMenuEntry(FPyRunnerCommands::Get().PluginAction);
						
						MenuBuilder.EndSection();

						return MenuBuilder.MakeWidget();
					})
				));
				
				PyRunnerEntry.SetCommandList(PluginCommands);
			}
		}
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FPyRunnerModule, PyRunner)