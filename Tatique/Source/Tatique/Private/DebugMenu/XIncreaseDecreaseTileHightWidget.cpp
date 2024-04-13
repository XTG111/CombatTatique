// Fill out your copyright notice in the Description page of Project Settings.


#include "DebugMenu/XIncreaseDecreaseTileHightWidget.h"
#include "Pawn/XSelectorContorlActor.h"
#include "Kismet/GameplayStatics.h"
#include "Pawn/XIncreasDecreasTileAction.h"

void UXIncreaseDecreaseTileHightWidget::NativeConstruct()
{
	PlayerActions = Cast<AXSelectorContorlActor>(UGameplayStatics::GetActorOfClass(GetWorld(), AXSelectorContorlActor::StaticClass()));
	if (PlayerActions)
	{
		PlayerActions->OnSelectionActionChange.AddDynamic(this, &UXIncreaseDecreaseTileHightWidget::OnSelectedActionsChanged);
	}
}

void UXIncreaseDecreaseTileHightWidget::OnSelectedActionsChanged(AXPlayerActions* leftclickaction, AXPlayerActions* rightclickaction)
{
		AXIncreasDecreasTileAction* idapl = Cast<AXIncreasDecreasTileAction>(PlayerActions->SelecetAction_LeftCheck);
		if(idapl) idapl->Increase = true;
		AXIncreasDecreasTileAction* idapr = Cast<AXIncreasDecreasTileAction>(PlayerActions->SelecetAction_RightCheck);
		if(idapr) idapr->Increase = false;
}
