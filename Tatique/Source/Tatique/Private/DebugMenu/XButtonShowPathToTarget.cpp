// Fill out your copyright notice in the Description page of Project Settings.


#include "DebugMenu/XButtonShowPathToTarget.h"
#include "Components/TextBlock.h"
#include "Components/CheckBox.h"
#include "DebugMenu/XButtonAction.h"
#include "Pawn/XSelectorContorlActor.h"
#include "Kismet/GameplayStatics.h"
#include "Pawn/XFindingPathToTargetAction.h"

void UXButtonShowPathToTarget::NativeConstruct()
{
	PlayerActions = Cast<AXSelectorContorlActor>(UGameplayStatics::GetActorOfClass(GetWorld(), AXSelectorContorlActor::StaticClass()));
	if (PlayerActions)
	{
		PlayerActions->OnSelectionActionChange.AddDynamic(this, &UXButtonShowPathToTarget::OnSelectedActionsChanged);
	}
	CheckBox_IncludeDiagonals->OnCheckStateChanged.AddDynamic(this, &UXButtonShowPathToTarget::SelecChange);
}

void UXButtonShowPathToTarget::OnSelectedActionsChanged(AXPlayerActions* leftclickaction, AXPlayerActions* rightclickaction)
{
	if (PlayerActions)
	{
		AXFindingPathToTargetAction* actor = Cast<AXFindingPathToTargetAction>(PlayerActions->SelecetAction_RightCheck);
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

void UXButtonShowPathToTarget::SelecChange(bool bIsChecked)
{
	if (PlayerActions)
	{
		AXFindingPathToTargetAction* actor = Cast<AXFindingPathToTargetAction>(PlayerActions->SelecetAction_RightCheck);
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
