// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "XSpinwithGrid3Param.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMyOnValueChange3, FVector, changevalue);
UCLASS()
class TATIQUE_API UXSpinwithGrid3Param : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
public:
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* TextBlock_Name;
	UPROPERTY(meta = (BindWidget))
		class USpinBox* SpinBox_Value_X;
	UPROPERTY(meta = (BindWidget))
		class USpinBox* SpinBox_Value_Y;
	UPROPERTY(meta = (BindWidget))
		class USpinBox* SpinBox_Value_Z;
	UFUNCTION()
		void SetSpinBox();
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FText Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector2D SliderValue;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector2D ValueBor;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector Value;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector2D FractionalDigits;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool AlwaysDeltaSnap;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Delta;

	UFUNCTION()
		void SelfOnValueChange(float chvalue);

	UPROPERTY(VisibleAnywhere)
		FMyOnValueChange3 MyOnValueChange;
	TArray<USpinBox*> SpinBoxList;
};
