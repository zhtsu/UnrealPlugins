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
		FPyRunnerCommands::Get().Script_01,
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
			Section.AddMenuEntryWithCommandList(FPyRunnerCommands::Get().Script_01, PluginCommands);
		}
	}

	{
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar");
		{
			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("Misc");
			{
				FToolMenuEntry& PyRunnerEntry = Section.AddEntry(FToolMenuEntry::InitComboButton(
					PyRunnerTabName,
					FUIAction(),
					FOnGetContent::CreateLambda([&]()->TSharedRef<SWidget>
					{
						FMenuBuilder MenuBuilder(true, PluginCommands);
				
						MenuBuilder.BeginSection("ScriptsSection", LOCTEXT("PyRunnerScripts", "Scripts"));
						
						MenuBuilder.AddMenuEntry(FPyRunnerCommands::Get().Script_01);
						MenuBuilder.AddMenuEntry(FPyRunnerCommands::Get().Script_02);
						MenuBuilder.AddMenuEntry(FPyRunnerCommands::Get().Script_03);
						MenuBuilder.AddMenuEntry(FPyRunnerCommands::Get().Script_04);
						MenuBuilder.AddMenuEntry(FPyRunnerCommands::Get().Script_05);
						MenuBuilder.AddMenuEntry(FPyRunnerCommands::Get().Script_06);
						MenuBuilder.AddMenuEntry(FPyRunnerCommands::Get().Script_07);
						MenuBuilder.AddMenuEntry(FPyRunnerCommands::Get().Script_08);
						
						MenuBuilder.EndSection();

						MenuBuilder.BeginSection("OptionsSection", LOCTEXT("PyRunnerOptions", "Options"));

						MenuBuilder.AddMenuEntry(FPyRunnerCommands::Get().RefreshScripts);
						MenuBuilder.AddMenuEntry(FPyRunnerCommands::Get().OpenScriptsDirectory);

						MenuBuilder.EndSection();

						return MenuBuilder.MakeWidget();
					}),
					LOCTEXT("PyRunnerMenuLabel", "PyRunner"),
					LOCTEXT("PyRunnerMenuToolTip", "Execute python script"),
					FSlateIcon(FPyRunnerStyle::GetStyleSetName(), "PyRunner.PluginAction")
				));
				
				PyRunnerEntry.SetCommandList(PluginCommands);
			}
		}
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FPyRunnerModule, PyRunner)