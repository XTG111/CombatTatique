// Fill out your copyright notice in the Description page of Project Settings.


#include "DebugMenu/XCameraDebugWidget.h"
#include "Pawn/XPawn.h"
#include "Components/SpinBox.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "DebugMenu/XSpinwithNameWidget.h"
#include "PlayerController/XPlayerController.h"


void UXCameraDebugWidget::NativeConstruct()
{
	AXPlayerController* PlayerController = GetOwningPlayer<AXPlayerController>();
	if (PlayerController)
	{
		// 获取PlayerController当前控制的Pawn
		MyPawn = Cast<AXPawn>(PlayerController->GetPawn());
	}
	if (MyPawn == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("No Pawn!!!!!!!"));
		return;
	}
	//UE_LOG(LogTemp, Warning, TEXT("The XCameraDebugWidget"));
	BindFunction();
}

void UXCameraDebugWidget::BindFunction()
{
	if (W_SpinBox_WithName_LocSpeed)
	{
		//UE_LOG(LogTemp, Warning, TEXT("W_SpinBox_WithName_LocSpeed"));
		W_SpinBox_WithName_LocSpeed->Value = MyPawn->LocationSpeed;
		W_SpinBox_WithName_LocSpeed->SetSpinBox();
		W_SpinBox_WithName_LocSpeed->SpinBox_Value->OnValueChanged.AddDynamic(this, &UXCameraDebugWidget::SetLocSpeed);
	}
	if (W_SpinBox_WithName_LocInterp)
	{
		W_SpinBox_WithName_LocInterp->Value = MyPawn->LocationInterp;
		W_SpinBox_WithName_LocInterp->SetSpinBox();
		W_SpinBox_WithName_LocInterp->SpinBox_Value->OnValueChanged.AddDynamic(this, &UXCameraDebugWidget::SetLocInterp);
	}

	if (W_SpinBox_WithName_RotSpeed)
	{
		W_SpinBox_WithName_RotSpeed->Value = MyPawn->RotationSpeed;
		W_SpinBox_WithName_RotSpeed->SetSpinBox();
		W_SpinBox_WithName_RotSpeed->SpinBox_Value->OnValueChanged.AddDynamic(this, &UXCameraDebugWidget::SetRotSpeed);
	}
	if (W_SpinBox_WithName_RotInterp)
	{
		W_SpinBox_WithName_RotInterp->Value = MyPawn->RotationInterp;
		W_SpinBox_WithName_RotSpeed->SetSpinBox();
		W_SpinBox_WithName_RotInterp->SpinBox_Value->OnValueChanged.AddDynamic(this, &UXCameraDebugWidget::SetRotInterp);
	}

	if (W_SpinBox_WithName_ZoomSpeed)
	{
		W_SpinBox_WithName_ZoomSpeed->Value = MyPawn->ZoomSpeed;
		W_SpinBox_WithName_ZoomSpeed->SetSpinBox();
		W_SpinBox_WithName_ZoomSpeed->SpinBox_Value->OnValueChanged.AddDynamic(this, &UXCameraDebugWidget::SetZoomSpeed);
	}
	if (W_SpinBox_WithName_ZoomInterp)
	{
		W_SpinBox_WithName_ZoomInterp->Value = MyPawn->ZoomInterp;
		W_SpinBox_WithName_ZoomInterp->SetSpinBox();
		W_SpinBox_WithName_ZoomInterp->SpinBox_Value->OnValueChanged.AddDynamic(this, &UXCameraDebugWidget::SetZoomInterp);
	}
	if (W_SpinBox_WithName_ZoomMin)
	{
		W_SpinBox_WithName_ZoomMin->Value = MyPawn->ZoomMin;
		W_SpinBox_WithName_ZoomMin->SetSpinBox();
		W_SpinBox_WithName_ZoomMin->SpinBox_Value->OnValueChanged.AddDynamic(this, &UXCameraDebugWidget::SetZoomMin);
	}
	if (W_SpinBox_WithName_ZoomMax)
	{
		W_SpinBox_WithName_ZoomMax->Value = MyPawn->ZoomMax;
		W_SpinBox_WithName_ZoomMax->SetSpinBox();
		W_SpinBox_WithName_ZoomMax->SpinBox_Value->OnValueChanged.AddDynamic(this, &UXCameraDebugWidget::SetZoomMax);
	}
}

void UXCameraDebugWidget::SetLocSpeed(float value)
{
	if (MyPawn)
	{
		MyPawn->LocationSpeed = value;
	}
}

void UXCameraDebugWidget::SetLocInterp(float value)
{
	if (MyPawn)
	{
		MyPawn->LocationInterp = value;
	}
}

void UXCameraDebugWidget::SetRotSpeed(float value)
{
	if (MyPawn)
	{
		MyPawn->RotationSpeed = value;
	}
}

void UXCameraDebugWidget::SetRotInterp(float value)
{
	if (MyPawn)
	{
		MyPawn->RotationInterp = value;
	}
}

void UXCameraDebugWidget::SetZoomSpeed(float value)
{
	if (MyPawn)
	{
		MyPawn->ZoomSpeed = value;
	}
}

void UXCameraDebugWidget::SetZoomInterp(float value)
{
	if (MyPawn)
	{
		MyPawn->ZoomInterp = value;
	}
}

void UXCameraDebugWidget::SetZoomMin(float value)
{
	if (MyPawn)
	{
		MyPawn->ZoomMin = value;
	}
}

void UXCameraDebugWidget::SetZoomMax(float value)
{
	if (MyPawn)
	{
		MyPawn->ZoomMax = value;
	}
}
