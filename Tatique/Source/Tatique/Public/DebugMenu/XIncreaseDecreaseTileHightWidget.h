// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "XIncreaseDecreaseTileHightWidget.generated.h"

/**
 * 
 */
UCLASS()
class TATIQUE_API UXIncreaseDecreaseTileHightWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;

public:
	UPROPERTY(VisibleAnywhere)
		class AXSelectorContorlActor* PlayerActions;
	UPROPERTY(meta = (BindWidget))
		class UXButtonAction* W_IncreasWidget;

public:
	UFUNCTION()
		void OnSelectedActionsChanged(class AXPlayerActions* leftclickaction, AXPlayerActions* rightclickaction);
	
};
