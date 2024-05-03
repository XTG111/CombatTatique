// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawn/XSelectTileCalculateMinCost.h"
#include "SpawnGrid/XGrid.h"
#include "Kismet/GameplayStatics.h"
#include "SpawnGrid/XGridPathFinding.h"
#include "Pawn/XSelectorContorlActor.h"

void AXSelectTileCalculateMinCost::ExecuteAction(FIntPoint index)
{
	Super::ExecuteAction(index);
	if (PlayerAction && PlayerAction->GridIns && PlayerAction->GridIns->XGridPathFinding)
	{
		PlayerAction->GridIns->XGridPathFinding->ClearGenerateData();
		if (PlayerAction->GridIns->IsIndexValid(PlayerAction->SelectedTile))
		{
			for (auto& it : PlayerAction->GridIns->GridTiles)
			{
				int mincost = PlayerAction->GridIns->XGridPathFinding->GetMinimumCostBetweenTwoTiles(it.Key, 
					PlayerAction->SelectedTile, 
					bIncludeDiagonals
				);
				FPathFindingData temp;
				temp.Index = it.Key;
				temp.CostToEnterTile = 1;
				temp.CostFromStart = 0;
				temp.MinimumCostToTarget = mincost;
				PlayerAction->GridIns->XGridPathFinding->DiscoverTile(temp);
			}
		}
	}
}
