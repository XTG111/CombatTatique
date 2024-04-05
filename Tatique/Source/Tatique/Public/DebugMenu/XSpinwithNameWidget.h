// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "XSpinwithNameWidget.generated.h"

/**
 * 
 */

//extern int count = 0;

UCLASS()
class TATIQUE_API UXSpinwithNameWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
	//virtual void NativePreConstruct() override;

public:
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* TextBlock_Name;
	UPROPERTY(meta = (BindWidget))
		class USpinBox* SpinBox_Value;
	UFUNCTION()
		void SetSpinBox();
public:
	//USTRUCT(EditAnywhere, BlueprintReadWrite)
	bool OnCall;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FText Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float MinSliderValue;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float MaxSliderValue;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float MinValue;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float MaxValue;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Value;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int MinFractionalValue;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int MaxFractionalValue;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool AlwaysUsesDeltaSnap = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Delta;

	void SteDefaultValue(const float dvalue);
};
