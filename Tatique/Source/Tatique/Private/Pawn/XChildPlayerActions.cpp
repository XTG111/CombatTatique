// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawn/XChildPlayerActions.h"
#include "Pawn/XSelectorContorlActor.h"
#include "SpawnGrid/XGrid.h"
#include "Kismet/GameplayStatics.h"

void AXChildPlayerActions::ExecuteAction(FIntPoint index)
{
	PlayerAction = Cast<AXSelectorContorlActor>(UGameplayStatics::GetActorOfClass(GetWorld(), AXSelectorContorlActor::StaticClass()));
	if (!PlayerAction)
	{
		UE_LOG(LogTemp, Warning, TEXT("No PlayerAction!!!!!!!!!!"));
		return;
	
	}
	bool check = PlayerAction->SelectedTile != index;
	//当此时选择的不是之前记录的，那么先消除之前记录的然后在记录当前的
	if (check && PlayerAction->GridIns)
	{
		
		PlayerAction->GridIns->RemoveStateFromTile(PlayerAction->SelectedTile, ETileState::ETT_Selected);
		PlayerAction->SelectedTile = index;
		PlayerAction->GridIns->AddStateToTile(PlayerAction->SelectedTile, ETileState::ETT_Selected);
	}
	//如果是之前记录的，则只需要删除
	else
	{
		PlayerAction->GridIns->RemoveStateFromTile(PlayerAction->SelectedTile, ETileState::ETT_Selected);
		PlayerAction->SelectedTile = (-999, -999);
	}
}

void AXChildPlayerActions::Destroyed()
{
	FIntPoint temp = (-999, -999);
	ExecuteAction(temp);
}
