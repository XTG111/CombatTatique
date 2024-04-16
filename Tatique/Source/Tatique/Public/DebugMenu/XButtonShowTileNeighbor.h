// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "XButtonShowTileNeighbor.generated.h"

/**
 * 
 */
UCLASS()
class TATIQUE_API UXButtonShowTileNeighbor : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;

public:
	UPROPERTY(meta = (BindWidget))
		class UXButtonAction* W_ShowTileNeighbors;
	UPROPERTY(meta = (BindWidget))
		class  UTextBlock* TextBlock_IncludeDiagonals;
	UPROPERTY(meta = (BindWidget))
		class UCheckBox* CheckBox_IncludeDiagonals;
	UPROPERTY(VisibleAnywhere)
		class AXSelectorContorlActor* PlayerActions;
public:
	UFUNCTION()
		void OnSelectedActionsChanged(class AXPlayerActions* leftclickaction, AXPlayerActions* rightclickaction);
	UFUNCTION()
		void SelecChange(bool bIsChecked);
	
};
