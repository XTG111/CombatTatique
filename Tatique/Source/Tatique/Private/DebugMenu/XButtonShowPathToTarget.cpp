// Fill out your copyright notice in the Description page of Project Settings.


#include "DebugMenu/XButtonShowPathToTarget.h"
#include "Components/TextBlock.h"
#include "Components/CheckBox.h"
#include "DebugMenu/XButtonAction.h"
#include "Pawn/XSelectorContorlActor.h"
#include "Kismet/GameplayStatics.h"
#include "Pawn/XFindingPathToTargetAction.h"
#include "DebugMenu/XSpinwithNameWidget.h"

void UXButtonShowPathToTarget::NativeConstruct()
{
	PlayerActions = Cast<AXSelectorContorlActor>(UGameplayStatics::GetActorOfClass(GetWorld(), AXSelectorContorlActor::StaticClass()));
	if (PlayerActions)
	{
		PlayerActions->OnSelectionActionChange.AddDynamic(this, &UXButtonShowPathToTarget::OnSelectedActionsChanged);
	}
	CheckBox_IncludeDiagonals->OnCheckStateChanged.AddDynamic(this, &UXButtonShowPathToTarget::SelecChange);
	W_SpinBox_Delay->OnValueChangedSelf.AddDynamic(this, &UXButtonShowPathToTarget::SetDelay);
}

void UXButtonShowPathToTarget::OnSelectedActionsChanged(AXPlayerActions* leftclickaction, AXPlayerActions* rightclickaction)
{
	if (PlayerActions)
	{
		AXFindingPathToTargetAction* actor = Cast<AXFindingPathToTargetAction>(PlayerActions->SelecetAction_RightCheck);
		if (actor)
		{
			actor->bIncludeDiagonals = CheckBox_IncludeDiagonals->IsChecked();
			actor->Delay = W_SpinBox_Delay->Value;
			W_SpinBox_Delay->SetVisibility(ESlateVisibility::Visible);
			CheckBox_IncludeDiagonals->SetVisibility(ESlateVisibility::Visible);
		}
		else
		{
			W_SpinBox_Delay->SetVisibility(ESlateVisibility::Collapsed);
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
			actor->Delay = W_SpinBox_Delay->Value;
			W_SpinBox_Delay->SetVisibility(ESlateVisibility::Visible);
			CheckBox_IncludeDiagonals->SetVisibility(ESlateVisibility::Visible);
		}
		else
		{
			W_SpinBox_Delay->SetVisibility(ESlateVisibility::Collapsed);
			CheckBox_IncludeDiagonals->SetVisibility(ESlateVisibility::Collapsed);
		}
	}
}

void UXButtonShowPathToTarget::SetDelay(float delay)
{
	if (PlayerActions)
	{
		AXFindingPathToTargetAction* actor = Cast<AXFindingPathToTargetAction>(PlayerActions->SelecetAction_RightCheck);
		if (actor)
		{
			actor->bIncludeDiagonals = CheckBox_IncludeDiagonals->IsChecked();
			actor->Delay = W_SpinBox_Delay->Value;
			W_SpinBox_Delay->SetVisibility(ESlateVisibility::Visible);
			CheckBox_IncludeDiagonals->SetVisibility(ESlateVisibility::Visible);
		}
		else
		{
			W_SpinBox_Delay->SetVisibility(ESlateVisibility::Collapsed);
			CheckBox_IncludeDiagonals->SetVisibility(ESlateVisibility::Collapsed);
		}
	}
}
