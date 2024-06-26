// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "XSpinwithGrid2Param.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMyOnValueChange2, FVector2D, changevalue);
UCLASS()
class TATIQUE_API UXSpinwithGrid2Param : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
public:
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* TextBlock_Name;
	UPROPERTY(meta = (BindWidget))
		class USpinBox* SpinBox_Value_X;
	UPROPERTY(meta = (BindWidget))
		class USpinBox* SpinBox_Value_Y;
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
		FVector2D Value;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector2D FractionalDigits;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool AlwaysDeltaSnap;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Delta;

	UFUNCTION()
		void SelfOnValueChange(float chvalue);

	void SetDefauleValue(const FVector2D& dvalue);

	UPROPERTY(VisibleAnywhere)
		FMyOnValueChange2 MyOnValueChange;

	FTimerHandle DelayTime;

	TArray<USpinBox*> SpinBoxList;
	
};
