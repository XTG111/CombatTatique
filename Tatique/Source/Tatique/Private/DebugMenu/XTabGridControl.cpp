// Fill out your copyright notice in the Description page of Project Settings.


#include "DebugMenu/XTabGridControl.h"
#include "Components/ComboBox.h" // ComboBox组件头文件
#include "Components/ComboBoxString.h" // ComboBoxString组件头文件（用于字符串类型的ComboBox）
#include "Blueprint/UserWidget.h" // UserWidget头文件（如果ComboBox位于用户界面蓝图中）
#include "Components/TextBlock.h"
#include "DebugMenu/XSpinwithGrid3Param.h"
#include "DebugMenu/XSpinwithGrid2Param.h"
#include "DebugMenu/XSpinwithNameWidget.h"
#include "SpawnGrid/XGrid.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SpinBox.h"

void UXTabGridControl::NativeConstruct()
{
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AXGrid::StaticClass(), GridInsList);
	GridIns = Cast<AXGrid>(GridInsList[0]);
	if (!GridIns)
	{
		UE_LOG(LogTemp, Warning, TEXT("No GridIns!!!!!!!"));
		return;
	}

	
	SetDefaultValue();
	SpawnGrid();

	BindFunction();
}

void UXTabGridControl::BindFunction()
{
	ComboBoxString_GridShape->OnSelectionChanged.AddDynamic(this, &UXTabGridControl::OnSelectionChange);
	

	W_GridControl_Location->Value = GridIns->CenterLocation;
	W_GridControl_Location->SetSpinBox();
	W_GridControl_Location->MyOnValueChange.AddDynamic(this, &UXTabGridControl::OnValueChange3);
	//if (W_GridControl_Location)
	//{
	//	W_GridControl_Location->Value = GridIns->CenterLocation;
	//	W_GridControl_Location->SetSpinBox();
	//	//W_GridControl_Location->MyOnValueChange.AddDynamic(this, &UXTabGridControl::OnValueChange3);
	//	W_GridControl_Location->SpinBox_Value_X->OnValueChanged.AddDynamic(this, &UXTabGridControl::LocXValue);
	//	W_GridControl_Location->SpinBox_Value_Y->OnValueChanged.AddDynamic(this, &UXTabGridControl::LocYValue);
	//	W_GridControl_Location->SpinBox_Value_Z->OnValueChanged.AddDynamic(this, &UXTabGridControl::LocZValue);
	//}
	W_GridControl_TileSize->Value = GridIns->TileSize;
	W_GridControl_TileSize->SetSpinBox();
	W_GridControl_TileSize->MyOnValueChange.AddDynamic(this, &UXTabGridControl::OnValueChange3);
	//if (W_GridControl_TileSize)
	//{
	//	W_GridControl_TileSize->Value = GridIns->TileSize;
	//	//UE_LOG(LogTemp, Warning, TEXT("TileSize,%f,%f,%f"), W_GridControl_TileSize->Value.X, W_GridControl_TileSize->Value.Y, W_GridControl_TileSize->Value.Z);

	//	W_GridControl_TileSize->SetSpinBox();
	//	//W_GridControl_TileSize->MyOnValueChange.AddDynamic(this, &UXTabGridControl::OnValueChange3);
	//	W_GridControl_TileSize->SpinBox_Value_X->OnValueChanged.AddDynamic(this, &UXTabGridControl::SizeXValue);
	//	W_GridControl_TileSize->SpinBox_Value_Y->OnValueChanged.AddDynamic(this, &UXTabGridControl::SizeYValue);
	//	W_GridControl_TileSize->SpinBox_Value_Z->OnValueChanged.AddDynamic(this, &UXTabGridControl::SizeZValue);
	//}

	W_GridControl_TileCount->Value = GridIns->TileCount;
	W_GridControl_TileCount->SetSpinBox();
	W_GridControl_TileCount->MyOnValueChange.AddDynamic(this, &UXTabGridControl::OnValueChange2);
	//if(W_GridControl_TileCount)
	//{
	//	W_GridControl_TileCount->Value = GridIns->TileCount;
	//	W_GridControl_TileCount->SetSpinBox();
	//	//W_GridControl_TileCount->MyOnValueChange.AddDynamic(this, &UXTabGridControl::OnValueChange2);
	//	W_GridControl_TileCount->SpinBox_Value_X->OnValueChanged.AddDynamic(this, &UXTabGridControl::CountXValue);
	//	W_GridControl_TileCount->SpinBox_Value_Y->OnValueChanged.AddDynamic(this, &UXTabGridControl::CountYValue);
	//}
	
	if(W_SpinBox_ReGenDelay)
	{
		W_SpinBox_ReGenDelay->Value = DTime;
		W_SpinBox_ReGenDelay->SetSpinBox();
		W_SpinBox_ReGenDelay->SpinBox_Value->OnValueChanged.AddDynamic(this, &UXTabGridControl::SetDelatValue);
	}
}

void UXTabGridControl::OnValueChange2(FVector2D value)
{
	//if (!FPlatformAtomics::InterlockedCompareExchange(&bHasExecuted, 1, 0))
	//{
	//	float Time = W_SpinBox_ReGenDelay->Value;
	//	GetWorld()->GetTimerManager().SetTimer(DelayTimer, this, &UXTabGridControl::SpawnGrid, Time);
	//	if (bHasExecuted) bHasExecuted = 0;
	//	else bHasExecuted = 1;
	//}
	SpawnGrid();
}

void UXTabGridControl::OnValueChange3(FVector value)
{
	//if (!FPlatformAtomics::InterlockedCompareExchange(&bHasExecuted, 1, 0))
	//{
	//	float Time = W_SpinBox_ReGenDelay->Value;
	//	GetWorld()->GetTimerManager().SetTimer(DelayTimer, this, &UXTabGridControl::SpawnGrid, Time);
	//	if (bHasExecuted) bHasExecuted = 0;
	//	else bHasExecuted = 1;
	//}
	SpawnGrid();
}

void UXTabGridControl::OnSelectionChange(FString SelectedItem, ESelectInfo::Type SelectionType)
{
	//if (!FPlatformAtomics::InterlockedCompareExchange(&bHasExecuted, 1, 0))
	//{
	//	float Time = W_SpinBox_ReGenDelay->Value;
	//	GetWorld()->GetTimerManager().SetTimer(DelayTimer, this, &UXTabGridControl::SpawnGrid, Time);
	//	if (bHasExecuted) bHasExecuted = 0;
	//	else bHasExecuted = 1;
	//}
	SpawnGrid();
}

void UXTabGridControl::SetDelatValue(float value)
{
	DTime = value;
}

void UXTabGridControl::SetDefaultValue()
{
	if (!GridIns) return;
	W_GridControl_Location->Value = GridIns->CenterLocation;
	W_GridControl_TileSize->Value = GridIns->TileSize;
	W_GridControl_TileCount->Value = GridIns->TileCount;
	const UEnum* EnumPtr = FindObject<UEnum>(ANY_PACKAGE, TEXT("EGridShapEnum"), true);
	if (!EnumPtr)
	{
		return ;
	}
	ComboBoxString_GridShape->SetSelectedOption(EnumPtr->GetDisplayNameTextByValue((int64)GridIns->GridShape).ToString());
	//UE_LOG(LogTemp, Warning, TEXT("GridIns!!!!!!!,%s"), *(EnumPtr->GetDisplayNameTextByValue((int64)GridIns->GridShape).ToString()));
}

void UXTabGridControl::SpawnGrid()
{
	int curEnumNum = ComboBoxString_GridShape->GetSelectedIndex();
	auto curEnum = static_cast<EGridShapEnum>(curEnumNum);
	if (curEnum == EGridShapEnum::EGS_None)
	{
		UE_LOG(LogTemp, Warning, TEXT("GridIns!!!!!!!,%d"), curEnumNum);
		GridIns->DestroyGrid();
		return;
	}
	else
	{
		FVector CenterLocation = W_GridControl_Location->Value;
		FVector TileSize = W_GridControl_TileSize->Value;
		FVector2D TileCount = W_GridControl_TileCount->Value;
		EGridShapEnum GridShape = curEnum;
		GridIns->SpawnGrid(CenterLocation, TileSize, TileCount, GridShape);
	}
}

FString UXTabGridControl::GetStringByEnum(int EnumValue)
{
	const UEnum* EnumPtr = FindObject<UEnum>(ANY_PACKAGE, TEXT("EGridShapEnum"), true);
	if (!EnumPtr)
	{
		return FString("Invalid");
	}

	return EnumPtr->GetDisplayNameTextByValue(EnumValue).ToString();
}

void UXTabGridControl::LocXValue(float value)
{
	GridIns->CenterLocation.X = value;
	SpawnGrid();
}

void UXTabGridControl::LocYValue(float value)
{
	GridIns->CenterLocation.Y = value;
	SpawnGrid();
}

void UXTabGridControl::LocZValue(float value)
{
	GridIns->CenterLocation.Z = value;
	SpawnGrid();
}

void UXTabGridControl::SizeXValue(float value)
{
	GridIns->TileSize.X = value;
	SpawnGrid();
}

void UXTabGridControl::SizeYValue(float value)
{
	GridIns->TileSize.Y = value;
	SpawnGrid();
}

void UXTabGridControl::SizeZValue(float value)
{
	GridIns->TileSize.Z = value;
	SpawnGrid();
}

void UXTabGridControl::CountXValue(float value)
{
	GridIns->TileCount.X = value;
	SpawnGrid();
}

void UXTabGridControl::CountYValue(float value)
{
	GridIns->TileCount.Y = value;
	SpawnGrid();
}
