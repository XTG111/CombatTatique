// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "XSetTileTypeWidget.generated.h"

/**
 * 
 */
UCLASS()
class TATIQUE_API UXSetTileTypeWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;

public:
	UPROPERTY(meta = (BindWidget))
		class UXButtonAction* W_SetTileTypeWidget;
	UPROPERTY(VisibleAnywhere)
		class AXSelectorContorlActor* PlayerActions;
	UPROPERTY(meta = (BindWidget))
		class  UComboBoxString* ComboBoxString_SetTileType;
public:
	UFUNCTION()
		void OnSelectedActionsChanged(class AXPlayerActions* leftclickaction, AXPlayerActions* rightclickaction);
	UFUNCTION()
		void SelecChange(FString SelectedItem, ESelectInfo::Type type);

};
