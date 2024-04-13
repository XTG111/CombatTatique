// Fill out your copyright notice in the Description page of Project Settings.


#include "DebugMenu/XButtonAction.h"
#include "Pawn/XSelectorContorlActor.h"
#include "Kismet/GameplayStatics.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "Pawn/XPlayerActions.h"

void UXButtonAction::NativePreConstruct()
{
	TextBlock_Actions->SetText(nameintro);
}

void UXButtonAction::NativeConstruct()
{
	
	PlayerActions = Cast<AXSelectorContorlActor>(UGameplayStatics::GetActorOfClass(GetWorld(), AXSelectorContorlActor::StaticClass()));
	if (PlayerActions)
	{
		PlayerActions->OnSelectionActionChange.AddDynamic(this, &UXButtonAction::OnSelectedActionsChanged);
	}
	if (Button_Actions)
	{
		Button_Actions->OnClicked.AddDynamic(this, &UXButtonAction::SetActions);
	}
}

void UXButtonAction::SetActions()
{
	//UE_LOG(LogTemp, Warning, TEXT("SetActions"));
	if (Button_Actions && PlayerActions)
	{
		
		bool temp = UGameplayStatics::GetObjectClass(PlayerActions->SelecetAction_LeftCheck) == LeftAction;
		if (temp)
		{
			PlayerActions->SetSelectedActions(nullptr, nullptr);
		}
		else
		{
			//UE_LOG(LogTemp, Warning, TEXT("PlayerActions->SelecetAction_LeftCheck"));
			PlayerActions->SetSelectedActions(LeftAction, RightAction);
		}
	}

}

void UXButtonAction::OnSelectedActionsChanged(AXPlayerActions* leftclickaction, AXPlayerActions* rightclickaction)
{
	//UE_LOG(LogTemp, Warning, TEXT("PlayerActions->SelecetAction_LeftCheck"));

	if (Button_Actions && PlayerActions)
	{
		
		bool temp = UGameplayStatics::GetObjectClass(PlayerActions->SelecetAction_LeftCheck) == LeftAction;
		FColor color = temp ? FColor::Cyan : FColor::Black;
		//UE_LOG(LogTemp, Warning, TEXT("OnSelectedActionsChanged,%d"),temp);
		Button_Actions->SetBackgroundColor(color);
	}
}
