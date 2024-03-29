// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "XCameraDebugWidget.generated.h"

/**
 * 
 */
UCLASS()
class TATIQUE_API UXCameraDebugWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	//virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;

	UFUNCTION()
		void BindFunction();

	UFUNCTION()
		void SetLocSpeed(float value);
	UFUNCTION()
		void SetLocInterp(float value);
	UFUNCTION()
		void SetRotSpeed(float value);
	UFUNCTION()
		void SetRotInterp(float value);
	UFUNCTION()
		void SetZoomSpeed(float value);
	UFUNCTION()
		void SetZoomInterp(float value);
	UFUNCTION()
		void SetZoomMin(float value);
	UFUNCTION()
		void SetZoomMax(float value);

public:

	UPROPERTY()
		class AXPawn* MyPawn;
	//操作介绍说明
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* TextBlock_Introduce;
	UPROPERTY(meta = (BindWidget))
		UTextBlock* TextBlock_Move;
	UPROPERTY(meta = (BindWidget))
		UTextBlock* TextBlock_ZoomWay;
	UPROPERTY(meta = (BindWidget))
		UTextBlock* TextBlock_Rotate;

	//每个操作框
	UPROPERTY(meta = (BindWidget))
		UTextBlock* TextBlock_CameraControl;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* TextBlock_Location;
	UPROPERTY(meta = (BindWidget))
		class UXSpinwithNameWidget* W_SpinBox_WithName_LocSpeed;
	UPROPERTY(meta = (BindWidget))
		UXSpinwithNameWidget* W_SpinBox_WithName_LocInterp;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* TextBlock_Rotation;
	UPROPERTY(meta = (BindWidget))
		UXSpinwithNameWidget* W_SpinBox_WithName_RotSpeed;
	UPROPERTY(meta = (BindWidget))
		UXSpinwithNameWidget* W_SpinBox_WithName_RotInterp;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* TextBlock_Zoom;
	UPROPERTY(meta = (BindWidget))
		UXSpinwithNameWidget* W_SpinBox_WithName_ZoomSpeed;
	UPROPERTY(meta = (BindWidget))
		UXSpinwithNameWidget* W_SpinBox_WithName_ZoomInterp;
	UPROPERTY(meta = (BindWidget))
		UXSpinwithNameWidget* W_SpinBox_WithName_ZoomMin;
	UPROPERTY(meta = (BindWidget))
		UXSpinwithNameWidget* W_SpinBox_WithName_ZoomMax;
};
