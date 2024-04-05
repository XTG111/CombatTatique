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
		class UXSpinwithNameWidget* W_SpinBox_Offset;
	UPROPERTY(meta = (BindWidget))
		class UXSpinwithGrid3Param* W_GridControl_Location;
	UPROPERTY(meta = (BindWidget))
		UXSpinwithGrid3Param* W_GridControl_TileSize;
	UPROPERTY(meta = (BindWidget))
		class UXSpinwithGrid2Param* W_GridControl_TileCount;
	UPROPERTY(meta = (BindWidget))
		class  UComboBoxString* ComboBoxString_GridShape;

	//For Debug

	//Delay Time
	FTimerHandle DebugDelayTime;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* TextBlock_Debug;
	UPROPERTY(meta = (BindWidget))
		UTextBlock* TextBlock_DrawLines;
	UPROPERTY(meta = (BindWidget))
		UTextBlock* TextBlock_Bounds;
	UPROPERTY(meta = (BindWidget))
		UTextBlock* TextBlock_Center;
	UPROPERTY(meta = (BindWidget))
		UTextBlock* TextBlock_GridCenter;
	UPROPERTY(meta = (BindWidget))
		UTextBlock* TextBlock_Bottom_Left;
	UPROPERTY(meta = (BindWidget))
		UTextBlock* TextBlock_BottomLeft;


	UPROPERTY(meta = (BindWidget))
		class UCheckBox* CheckBox_Center;
	UPROPERTY(meta = (BindWidget))
		UCheckBox* CheckBox_Bottom_Left;
	UPROPERTY(meta = (BindWidget))
		UCheckBox* CheckBox_Bounds;

	UPROPERTY(meta = (BindWidget))
		UCheckBox* CheckBox_UseEnv;

	UFUNCTION()
		void DrawDebugLines();

	//Enviorment
	UPROPERTY(VisibleAnywhere)
		class AXLevelLoadActor* LLevelIns;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* TextBlock_Enviorment;
	UPROPERTY(meta = (BindWidget))
		UComboBoxString* ComboBoxString_LevelMap;
	UFUNCTION()
		void LoadLevel(FString SelectedItem, ESelectInfo::Type SelectionType);

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
		void CheckChanged(bool bIsChecked);
	UFUNCTION()
		void SetGridOffset(float value);
	UFUNCTION()
		void SpawnGrid();

	//do once
	int bHasExecuted = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float DTime = 1.0f;

	TArray<AActor*> GridInsList;

	FTimerHandle DelayTimer;
	FString GetStringByEnum(int EnumValue);

};
