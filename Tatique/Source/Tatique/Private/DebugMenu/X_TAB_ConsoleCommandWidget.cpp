// Fill out your copyright notice in the Description page of Project Settings.


#include "DebugMenu/X_TAB_ConsoleCommandWidget.h"
#include "DebugMenu/XButtonConsoleCommandWidget.h"
#include "Components/TextBlock.h"
#include "Components/EditableText.h"
#include "Kismet/KismetSystemLibrary.h"

void UX_TAB_ConsoleCommandWidget::NativeConstruct()
{
	bool ButtonIsvalid = Button_statfps &&	Button_statunit &&	Button_statuobjects
						&& Button_showFlagStaticMeshes0 &&	Button_showFlagStaticMeshes1
		                && Button_ShowFlagWireFrame0 &&	Button_ShowFlagWireFrame1;
	if (!ButtonIsvalid) return;
	Button_statfps->Console_Command = FString("stat fps");
	Button_statfps->SetTextofButton();

	Button_statunit->Console_Command = FString("stat unit");
	Button_statunit->SetTextofButton();

	Button_statuobjects->Console_Command = FString("stat uobjects");
	Button_statunit->SetTextofButton();

	Button_showFlagStaticMeshes0->Console_Command = FString("ShowFlag.StaticMeshes 0");
	Button_showFlagStaticMeshes0->SetTextofButton();

	Button_showFlagStaticMeshes1->Console_Command = FString("ShowFlag.StaticMeshes 1");
	Button_showFlagStaticMeshes1->SetTextofButton();

	Button_ShowFlagWireFrame0->Console_Command = FString("ShowFlag.Wireframe 0");
	Button_ShowFlagWireFrame0->SetTextofButton();

	Button_ShowFlagWireFrame1->Console_Command = FString("ShowFlag.Wireframe 1");
	Button_ShowFlagWireFrame1->SetTextofButton();

	if (!EditableText_ConsoleCommand) return;
	//EditableText_ConsoleCommand->SetHintText(FText::FromString("Comsole Command"));
	EditableText_ConsoleCommand->OnTextCommitted.AddDynamic(this, &UX_TAB_ConsoleCommandWidget::ExeCommand);
}

void UX_TAB_ConsoleCommandWidget::ExeCommand(const FText& Text, ETextCommit::Type CommitMethod)
{
	if (CommitMethod == ETextCommit::OnEnter)
	{
		UKismetSystemLibrary::ExecuteConsoleCommand(this, Text.ToString());
		EditableText_ConsoleCommand->SetFocus();
	}
}
