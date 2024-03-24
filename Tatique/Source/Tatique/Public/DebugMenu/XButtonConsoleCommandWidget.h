// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "XButtonConsoleCommandWidget.generated.h"

/**
 * 
 */
UCLASS()
class TATIQUE_API UXButtonConsoleCommandWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;

	UFUNCTION()
		void ExeCommand();

	void SetTextofButton();

public:
	UPROPERTY(meta = (BindWidget))
		class UButton* Button_ConsoleCommand;
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* TextBlock_ConsoleCommand;

	FString Console_Command;
	
};
