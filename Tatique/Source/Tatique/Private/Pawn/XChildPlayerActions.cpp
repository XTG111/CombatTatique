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
	//����ʱѡ��Ĳ���֮ǰ��¼�ģ���ô������֮ǰ��¼��Ȼ���ڼ�¼��ǰ��
	if (check && PlayerAction->GridIns)
	{
		
		PlayerAction->GridIns->RemoveStateFromTile(PlayerAction->SelectedTile, ETileState::ETT_Selected);
		PlayerAction->SelectedTile = index;
		PlayerAction->GridIns->AddStateToTile(PlayerAction->SelectedTile, ETileState::ETT_Selected);
	}
	//�����֮ǰ��¼�ģ���ֻ��Ҫɾ��
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
