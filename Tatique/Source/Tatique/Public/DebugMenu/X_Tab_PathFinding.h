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
	UFUNCTION()
		void SetShowCostToEnterTile(bool bsctet);
	UFUNCTION()
		void SetShowMinCostToTarget(bool bsmctt);
	UFUNCTION()
		void SetShowCostFromStart(bool bscfs);
	UFUNCTION()
		void SetShowSortOrder(bool bsso);
	UFUNCTION()
		void SetShowDiscoveredTiles(bool bsdt);
	UFUNCTION()
		void SetShowAnalysedTiles(bool bsat);
public:
	UPROPERTY(VisibleAnywhere)
		class AXDebugTextOnTiles* DebugTextsOnTilesActor;
	UPROPERTY(meta = (BindWidget))
		class UXButtonAction* W_XButtonActions;
	UPROPERTY(meta = (BindWidget))
		class UXButtonShowTileNeighbor* W_Button_Action_ShowTileNeighbor;
	UPROPERTY(meta = (BindWidget))
		class UXButtonShowPathToTarget* W_Button_Action_ShowPathToTarget;
	UPROPERTY(meta = (BindWidget))
		class UXCaculateMinCost* W_Button_Action_CaculateMinCost;


	UPROPERTY(meta = (BindWidget))
		class UCheckBox* CheckBox_ShowIndexesOnTiles;
	UPROPERTY(meta = (BindWidget))
		class UCheckBox* CheckBox_ShowCostToEnterTile;
	UPROPERTY(meta = (BindWidget))
		class UCheckBox* CheckBox_ShowMinCostToTarget;
	UPROPERTY(meta = (BindWidget))
		class UCheckBox* CheckBox_ShowCostFromStart;
	UPROPERTY(meta = (BindWidget))
		class UCheckBox* CheckBox_ShowSortOrder;
	UPROPERTY(meta = (BindWidget))
		class UCheckBox* CheckBox_ShowDiscoveredTiles;
	UPROPERTY(meta = (BindWidget))
		class UCheckBox* CheckBox_ShowAnalysedTiles;

	bool bShowIndexesOnTiles = false;
	bool bShowCostToEnterTile = false;
	bool bShowMinCostToTarget = false;
	bool bShowCostFromStart = false;
	bool bShowSortOrder = false;
	bool bShowDiscoveredTiles = false;
	bool bShowAnalysedTiles = false;
	
};
