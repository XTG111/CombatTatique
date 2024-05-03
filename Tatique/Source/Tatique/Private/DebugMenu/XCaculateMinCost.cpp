// Fill out your copyright notice in the Description page of Project Settings.


#include "DebugMenu/XCaculateMinCost.h"
#include "Components/TextBlock.h"
#include "Components/CheckBox.h"
#include "DebugMenu/XButtonAction.h"
#include "Pawn/XSelectorContorlActor.h"
#include "Kismet/GameplayStatics.h"
#include "Pawn/XSelectTileCalculateMinCost.h"

void UXCaculateMinCost::NativeConstruct()
{
	PlayerActions = Cast<AXSelectorContorlActor>(UGameplayStatics::GetActorOfClass(GetWorld(), AXSelectorContorlActor::StaticClass()));
	if (PlayerActions)
	{
		PlayerActions->OnSelectionActionChange.AddDynamic(this, &UXCaculateMinCost::OnSelectedActionsChanged);
	}
	CheckBox_IncludeDiagonals->OnCheckStateChanged.AddDynamic(this, &UXCaculateMinCost::SelecChange);
}

void UXCaculateMinCost::OnSelectedActionsChanged(AXPlayerActions* leftclickaction, AXPlayerActions* rightclickaction)
{
	if (PlayerActions)
	{
		AXSelectTileCalculateMinCost* actor = Cast<AXSelectTileCalculateMinCost>(PlayerActions->SelecetAction_LeftCheck);
		if (actor)
		{
			actor->bIncludeDiagonals = CheckBox_IncludeDiagonals->IsChecked();
			CheckBox_IncludeDiagonals->SetVisibility(ESlateVisibility::Visible);
		}
		else
		{
			CheckBox_IncludeDiagonals->SetVisibility(ESlateVisibility::Collapsed);
		}
	}
}

void UXCaculateMinCost::SelecChange(bool bIsChecked)
{
	AXSelectTileCalculateMinCost* actor = Cast<AXSelectTileCalculateMinCost>(PlayerActions->SelecetAction_LeftCheck);
	if (actor)
	{
		actor->bIncludeDiagonals = CheckBox_IncludeDiagonals->IsChecked();
		CheckBox_IncludeDiagonals->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		CheckBox_IncludeDiagonals->SetVisibility(ESlateVisibility::Collapsed);
	}
}
