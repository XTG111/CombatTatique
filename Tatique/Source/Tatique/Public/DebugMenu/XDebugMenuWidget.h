// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "XDebugMenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class TATIQUE_API UXDebugMenuWidget : public UUserWidget
{
	GENERATED_BODY()
public:

	virtual void NativeConstruct() override;

	UFUNCTION()
		void SetChoose1();
	UFUNCTION()
		void SetChoose2();
	UFUNCTION()
		void SetChoose3();

public:
	UPROPERTY(meta = (BindWidget))
		class UButton* Button_Tab1;
	UPROPERTY(meta = (BindWidget))
		UButton* Button_Tab2;
	UPROPERTY(meta = (BindWidget))
		UButton* Button_Tab3;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* TextBlock_Tab1;
	UPROPERTY(meta = (BindWidget))
		UTextBlock* TextBlock_Tab2;
	UPROPERTY(meta = (BindWidget))
		UTextBlock* TextBlock_Tab3;

	UPROPERTY(meta = (BindWidget))
		class UWidgetSwitcher* WidgetSwitcher_TabContent;
	UPROPERTY(meta = (BindWidget))
		UTextBlock* TextBlock_0Info;
	UPROPERTY(meta = (BindWidget))
		UTextBlock* TextBlock_Tab1Info;
	UPROPERTY(meta = (BindWidget))
		UTextBlock* TextBlock_Tab2Info;
	UPROPERTY(meta = (BindWidget))
		UTextBlock* TextBlock_Tab3Info;

	FLinearColor BackgroudColor;
	FLinearColor BackgroundColorOther;
	
};
