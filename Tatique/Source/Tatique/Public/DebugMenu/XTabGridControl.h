// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "XTabGridControl.generated.h"

/**
 * 
 */
UCLASS()
class TATIQUE_API UXTabGridControl : public UUserWidget
{
	GENERATED_BODY()
public:
	//virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;

	UFUNCTION()
		void BindFunction();
public:
	UPROPERTY(VisibleAnywhere)
		class AXGrid* GridIns;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* TextBlock_GridGeneration;
	UPROPERTY(meta = (BindWidget))
		class UXSpinwithNameWidget* W_SpinBox_ReGenDelay;
	UPROPERTY(meta = (BindWidget))
		class UXSpinwithGrid3Param* W_GridControl_Location;
	UPROPERTY(meta = (BindWidget))
		UXSpinwithGrid3Param* W_GridControl_TileSize;
	UPROPERTY(meta = (BindWidget))
		class UXSpinwithGrid2Param* W_GridControl_TileCount;
	UPROPERTY(meta = (BindWidget))
		class  UComboBoxString* ComboBoxString_GridShape;
public:
	UFUNCTION()
		void OnValueChange2(FVector2D value);
	UFUNCTION()
		void OnValueChange3(FVector value);
	UFUNCTION()
		void OnSelectionChange(FString SelectedItem, ESelectInfo::Type SelectionType);
	UFUNCTION()
		void SetDelatValue(float value);
	UFUNCTION()
		void SetDefaultValue();
	UFUNCTION()
		void SpawnGrid();

	//do once
	int bHasExecuted = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float DTime = 1.0f;

	TArray<AActor*> GridInsList;

	FTimerHandle DelayTimer;
	FString GetStringByEnum(int EnumValue);

public:
	UFUNCTION()
		void LocXValue(float value);
	UFUNCTION()
		void LocYValue(float value);
	UFUNCTION()
		void LocZValue(float value);
	UFUNCTION()
		void SizeXValue(float value);
	UFUNCTION()
		void SizeYValue(float value);
	UFUNCTION()
		void SizeZValue(float value);
	UFUNCTION()
		void CountXValue(float value);
	UFUNCTION()
		void CountYValue(float value);

};
