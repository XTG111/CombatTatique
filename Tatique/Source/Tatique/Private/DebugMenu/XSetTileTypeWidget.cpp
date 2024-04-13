// Fill out your copyright notice in the Description page of Project Settings.


#include "DebugMenu/XSetTileTypeWidget.h"
#include "Components/ComboBox.h" // ComboBox组件头文件
#include "Components/ComboBoxString.h" // ComboBoxString组件头文件（用于字符串类型的ComboBox）
#include "Blueprint/UserWidget.h" // UserWidget头文件（如果ComboBox位于用户界面蓝图中）
#include "Pawn/XSelectorContorlActor.h"
#include "Kismet/GameplayStatics.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Pawn/XPlayerActions.h"
#include "Pawn/XSetTileTypeAction.h"
#include "D:/UnrealProject/CombatTatique_W/CombatTatique/Tatique/Source/Tatique/XHeadFile/GridShapeEnum.h"


void UXSetTileTypeWidget::NativePreConstruct()
{
	ComboBoxString_SetTileType->ClearOptions();
	UEnum* MyEnum = StaticEnum<ETileType>();
	for (int32 i = 0; i < MyEnum->NumEnums() - 1; i++)
	{
		ComboBoxString_SetTileType->AddOption(MyEnum->GetNameStringByIndex(i));
	}
	ComboBoxString_SetTileType->SetSelectedIndex(1);
}

void UXSetTileTypeWidget::NativeConstruct()
{
	PlayerActions = Cast<AXSelectorContorlActor>(UGameplayStatics::GetActorOfClass(GetWorld(), AXSelectorContorlActor::StaticClass()));
	if (PlayerActions)
	{
		PlayerActions->OnSelectionActionChange.AddDynamic(this, &UXSetTileTypeWidget::OnSelectedActionsChanged);
	}
	if (ComboBoxString_SetTileType)
	{
		ComboBoxString_SetTileType->OnSelectionChanged.AddDynamic(this, &UXSetTileTypeWidget::SelecChange);
	}
}

void UXSetTileTypeWidget::OnSelectedActionsChanged(AXPlayerActions* leftclickaction, AXPlayerActions* rightclickaction)
{
		AXSetTileTypeAction* idapl = Cast<AXSetTileTypeAction>(PlayerActions->SelecetAction_LeftCheck);
		if(idapl) idapl->TileType = static_cast<ETileType>(ComboBoxString_SetTileType->GetSelectedIndex());
		AXSetTileTypeAction* idapr = Cast<AXSetTileTypeAction>(PlayerActions->SelecetAction_RightCheck);
		if(idapr) idapr->TileType = ETileType::ETT_Normal;
}

void UXSetTileTypeWidget::SelecChange(FString SelectedItem, ESelectInfo::Type type)
{
	AXSetTileTypeAction* idapl = Cast<AXSetTileTypeAction>(PlayerActions->SelecetAction_LeftCheck);
	if (idapl) idapl->TileType = static_cast<ETileType>(ComboBoxString_SetTileType->GetSelectedIndex());
	AXSetTileTypeAction* idapr = Cast<AXSetTileTypeAction>(PlayerActions->SelecetAction_RightCheck);
	if (idapr) idapr->TileType = ETileType::ETT_Normal;
}
