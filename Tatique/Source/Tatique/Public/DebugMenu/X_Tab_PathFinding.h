// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "X_Tab_PathFinding.generated.h"

/**
 * 
 */
UCLASS()
class TATIQUE_API UX_Tab_PathFinding : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
	UFUNCTION()
		void SetShowTileIndexes(bool bsti);
public:
	UPROPERTY(VisibleAnywhere)
		class AXDebugTextOnTiles* DebugTextsOnTilesActor;
	UPROPERTY(meta = (BindWidget))
		class UXButtonAction* W_XButtonActions;
	UPROPERTY(meta = (BindWidget))
		class UCheckBox* CheckBox_ShowIndexesOnTiles;
	
};
