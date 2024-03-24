// Fill out your copyright notice in the Description page of Project Settings.


#include "DebugMenu/XButtonConsoleCommandWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Kismet/KismetSystemLibrary.h"

void UXButtonConsoleCommandWidget::NativeConstruct()
{
	if (Button_ConsoleCommand)
	{
		Button_ConsoleCommand->OnClicked.AddDynamic(this, &UXButtonConsoleCommandWidget::ExeCommand);
	}
}

void UXButtonConsoleCommandWidget::ExeCommand()
{
	//Ö´ÐÐÃüÁî
	UKismetSystemLibrary::ExecuteConsoleCommand(this, Console_Command);
}

void UXButtonConsoleCommandWidget::SetTextofButton()
{
	if (TextBlock_ConsoleCommand)
	{
		TextBlock_ConsoleCommand->SetText(FText::FromString(Console_Command));
	}
}
