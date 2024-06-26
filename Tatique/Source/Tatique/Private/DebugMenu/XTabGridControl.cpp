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
#include "Components/CheckBox.h"
#include "LevelLoad/XLevelLoadActor.h"
#include "SpawnGrid/XGridVisiual.h"

#include "DrawDebugHelpers.h"

void UXTabGridControl::NativePreConstruct()
{
	SetDefaultValue();
}

void UXTabGridControl::NativeConstruct()
{
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AXGrid::StaticClass(), GridInsList);
	GridIns = Cast<AXGrid>(GridInsList[0]);
	if (!GridIns)
	{
		UE_LOG(LogTemp, Warning, TEXT("No GridIns!!!!!!!"));
		return;
	}

	LLevelIns = Cast<AXLevelLoadActor>(UGameplayStatics::GetActorOfClass(GetWorld(), AXLevelLoadActor::StaticClass()));
	if (!LLevelIns)
	{
		UE_LOG(LogTemp, Warning, TEXT("No LLevelIns!!!!!!!"));
		return;
	}
	
	//SetDefaultValue();
	SpawnGrid();
	GetWorld()->GetTimerManager().SetTimer(DebugDelayTime, this, &UXTabGridControl::DrawDebugLines, 0.5f, true);
	BindFunction();
}

void UXTabGridControl::BindFunction()
{
	ComboBoxString_GridShape->OnSelectionChanged.AddDynamic(this, &UXTabGridControl::OnSelectionChange);
	
	ComboBoxString_LevelMap->OnSelectionChanged.AddDynamic(this, &UXTabGridControl::LoadLevel);

	/*W_GridControl_Location->Value = GridIns->CenterLocation;
	W_GridControl_Location->SetSpinBox();*/
	W_GridControl_Location->MyOnValueChange.AddDynamic(this, &UXTabGridControl::OnValueChange3);

	/*W_GridControl_TileSize->Value = GridIns->TileSize;
	W_GridControl_TileSize->SetSpinBox();*/
	W_GridControl_TileSize->MyOnValueChange.AddDynamic(this, &UXTabGridControl::OnValueChange3);


	/*W_GridControl_TileCount->Value = GridIns->TileCount;
	W_GridControl_TileCount->SetSpinBox();*/
	W_GridControl_TileCount->MyOnValueChange.AddDynamic(this, &UXTabGridControl::OnValueChange2);

	CheckBox_UseEnv->OnCheckStateChanged.AddDynamic(this, &UXTabGridControl::CheckChanged);
	
	/*W_SpinBox_Offset->Value = GridIns->Offset;
	W_SpinBox_Offset->SetSpinBox();*/
	W_SpinBox_Offset->SpinBox_Value->OnValueChanged.AddDynamic(this, &UXTabGridControl::SetGridOffset);

	if(W_SpinBox_ReGenDelay)
	{
		/*W_SpinBox_ReGenDelay->Value = DTime;
		W_SpinBox_ReGenDelay->SetSpinBox();*/
		W_SpinBox_ReGenDelay->SpinBox_Value->OnValueChanged.AddDynamic(this, &UXTabGridControl::SetDelatValue);
	}
}

void UXTabGridControl::DrawDebugLines()
{
	//Set Text
	TextBlock_GridCenter->SetText(FText::FromString(GridIns->CenterLocation.ToString()));
	TextBlock_BottomLeft->SetText(FText::FromString(GridIns->GridBottomLeftCornerLoc.ToString()));

	FVector GridInsCenterLoc = GridIns->CenterLocation;
	FVector GridInsBottomLeftLoc = GridIns->GridBottomLeftCornerLoc;
	FVector WCenterLoc = W_GridControl_Location->Value;


	if (CheckBox_Center->IsChecked())
	{
		DrawDebugSphere(GetWorld(), GridInsCenterLoc, 50.0f, 12, FColor::Red, false, 0.5f, 0, 10.0f);
		DrawDebugSphere(GetWorld(), WCenterLoc, 50.0f, 12, FColor::Orange, false, 0.5f, 0, 10.0f);
	}
	if (CheckBox_Bottom_Left->IsChecked())
	{
		DrawDebugSphere(GetWorld(), GridInsBottomLeftLoc, 50.0f, 12, FColor::Green, false, 0.5f, 0, 10.0f);
	}
	if (CheckBox_Bounds->IsChecked())
	{
		DrawDebugBox(GetWorld(), GridInsCenterLoc, GridInsCenterLoc-GridInsBottomLeftLoc, FColor::Green, false, 0.5f, 0, 10.0f);
	}
	FVector loc = GridIns->GetCursorLocationOnGrid(0);
	TextBlock_MouseLocation->SetText(FText::FromString(FString::Printf(TEXT("%f, %f, %f"), loc.X, loc.Y, loc.Z)));
	if (CheckBox_Mouse_Location->IsChecked())
	{
		DrawDebugSphere(GetWorld(), loc, 10.0f, 5, FColor::Green, false, 0.1f, 5.0f);
	}
	FIntPoint ip = GridIns->GetTileIndexUnderCursor(0);
	TextBlock_HoveredTile->SetText(FText::FromString(FString::Printf(TEXT("%d, %d"), ip.X, ip.Y)));
	if (CheckBox_Hovered_Tile->IsChecked() && GridIns->GridTiles.Find(ip))
	{
		FVector Extent = { 35.0f,35.0f,5.0f };
		DrawDebugBox(GetWorld(), GridIns->GridTiles.Find(ip)->Transform.GetLocation(), Extent, FColor::Purple, false, 0.1f, 5.0f);
	}
}

void UXTabGridControl::LoadLevel(FString SelectedItem, ESelectInfo::Type SelectionType)
{
	LLevelIns->LoadLevel(SelectedItem, true);
}

void UXTabGridControl::OnValueChange2(FVector2D value)
{
	SpawnGrid();
}

void UXTabGridControl::OnValueChange3(FVector value)
{
	SpawnGrid();
}

void UXTabGridControl::OnSelectionChange(FString SelectedItem, ESelectInfo::Type SelectionType)
{
	SpawnGrid();
}

void UXTabGridControl::SetDelatValue(float value)
{
	DTime = value;
}

void UXTabGridControl::SetDefaultValue()
{
	if (!GridIns) return;
	W_GridControl_Location->Value = FVector{0.0f,0.0f,0.0f};
	W_GridControl_TileSize->Value = FVector{ 100.0f,100.0f,50.0f };
	W_GridControl_TileCount->Value = FIntPoint(10, 10);
	const UEnum* EnumPtr = FindObject<UEnum>(ANY_PACKAGE, TEXT("EGridShapEnum"), true);
	if (!EnumPtr)
	{
		return ;
	}
	ComboBoxString_GridShape->SetSelectedOption(EnumPtr->GetDisplayNameTextByValue((int64)GridIns->GridShape).ToString());
	//UE_LOG(LogTemp, Warning, TEXT("GridIns!!!!!!!,%s"), *(EnumPtr->GetDisplayNameTextByValue((int64)GridIns->GridShape).ToString()));
	ComboBoxString_LevelMap->SetSelectedOption(LLevelIns->LevelLoaded);
}

void UXTabGridControl::CheckChanged(bool bIsChecked)
{
	SpawnGrid();
}

void UXTabGridControl::SetGridOffset(float value)
{
	if (GridIns && GridIns->XGridVisual)
	{
		GridIns->XGridVisual->Offset = value;
	}
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
		FIntPoint TileCount;
		TileCount.X = FMath::RoundToInt(W_GridControl_TileCount->Value.X);
		TileCount.Y = FMath::RoundToInt(W_GridControl_TileCount->Value.Y);
		EGridShapEnum GridShape = curEnum;
		GridIns->SpawnGrid(CenterLocation, TileSize, TileCount, GridShape, CheckBox_UseEnv->IsChecked());
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

