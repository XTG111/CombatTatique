// Fill out your copyright notice in the Description page of Project Settings.


#include "DebugMenu/XButtonShowTileNeighbor.h"
#include "Components/TextBlock.h"
#include "Components/CheckBox.h"
#include "DebugMenu/XButtonAction.h"
#include "Pawn/XSelectorContorlActor.h"
#include "Kismet/GameplayStatics.h"
#include "Pawn/XShowTileNeighborsAction.h"

void UXButtonShowTileNeighbor::NativeConstruct()
{
	PlayerActions = Cast<AXSelectorContorlActor>(UGameplayStatics::GetActorOfClass(GetWorld(), AXSelectorContorlActor::StaticClass()));
	if (PlayerActions)
	{
		PlayerActions->OnSelectionActionChange.AddDynamic(this, &UXButtonShowTileNeighbor::OnSelectedActionsChanged);
	}
	CheckBox_IncludeDiagonals->OnCheckStateChanged.AddDynamic(this, &UXButtonShowTileNeighbor::SelecChange);
}

void UXButtonShowTileNeighbor::OnSelectedActionsChanged(AXPlayerActions* leftclickaction, AXPlayerActions* rightclickaction)
{
	if (PlayerActions)
	{
		AXShowTileNeighborsAction* actor = Cast<AXShowTileNeighborsAction>(PlayerActions->SelecetAction_LeftCheck);
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

void UXButtonShowTileNeighbor::SelecChange(bool bIsChecked)
{
	AXShowTileNeighborsAction* actor = Cast<AXShowTileNeighborsAction>(PlayerActions->SelecetAction_LeftCheck);
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
