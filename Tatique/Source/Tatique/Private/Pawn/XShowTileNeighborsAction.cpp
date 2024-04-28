// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawn/XShowTileNeighborsAction.h"
#include "Pawn/XSelectorContorlActor.h"
#include "SpawnGrid/XGrid.h"
#include "Kismet/GameplayStatics.h"
#include "SpawnGrid/XGridPathFinding.h"

void AXShowTileNeighborsAction::ExecuteAction(FIntPoint index)
{
	PlayerAction = Cast<AXSelectorContorlActor>(UGameplayStatics::GetActorOfClass(GetWorld(), AXSelectorContorlActor::StaticClass()));
	if (!PlayerAction)
	{
		UE_LOG(LogTemp, Warning, TEXT("No PlayerAction!!!!!!!!!!"));
		return;
	}
	if (PlayerAction->GridIns)
	{
		PlayerAction->GridIns->ClearStateFromTiles(ETileState::ETT_IsNeighbored);
		if (PlayerAction->GridIns->ChildActor_GridPathFinding)
		{
			TArray<FPathFindingData> nerighbors = PlayerAction->GridIns->XGridPathFinding->GetValidTileNeighbor(index, bIncludeDiagonals);
			for (auto& it : nerighbors)
			{
				PlayerAction->GridIns->AddStateToTile(it.Index,ETileState::ETT_IsNeighbored);
			}
		}
	}
}
