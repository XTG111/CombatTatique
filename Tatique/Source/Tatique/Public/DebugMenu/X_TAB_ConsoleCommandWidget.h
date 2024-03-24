// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "X_TAB_ConsoleCommandWidget.generated.h"

/**
 * 
 */
UCLASS()
class TATIQUE_API UX_TAB_ConsoleCommandWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;

	UFUNCTION()
		void ExeCommand(const FText& Text, ETextCommit::Type CommitMethod);
public:
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* TextBlock_ConsoleCommands;
	UPROPERTY(meta = (BindWidget))
		class UEditableText* EditableText_ConsoleCommand;

	UPROPERTY(meta = (BindWidget))
		class UXButtonConsoleCommandWidget* Button_statfps;
	UPROPERTY(meta = (BindWidget))
		UXButtonConsoleCommandWidget* Button_statunit;
	UPROPERTY(meta = (BindWidget))
		UXButtonConsoleCommandWidget* Button_statuobjects;
	UPROPERTY(meta = (BindWidget))
		UXButtonConsoleCommandWidget* Button_showFlagStaticMeshes0;
	UPROPERTY(meta = (BindWidget))
		UXButtonConsoleCommandWidget* Button_showFlagStaticMeshes1;
	UPROPERTY(meta = (BindWidget))
		UXButtonConsoleCommandWidget* Button_ShowFlagWireFrame0;
	UPROPERTY(meta = (BindWidget))
		UXButtonConsoleCommandWidget* Button_ShowFlagWireFrame1;
	
};
