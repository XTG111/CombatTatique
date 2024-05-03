// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawn/XFindingPathToTargetAction.h"
#include "Pawn/XSelectorContorlActor.h"
#include "SpawnGrid/XGrid.h"
#include "Kismet/GameplayStatics.h"
#include "SpawnGrid/XGridPathFinding.h"

void AXFindingPathToTargetAction::ExecuteAction(FIntPoint index)
{
	PlayerAction = Cast<AXSelectorContorlActor>(UGameplayStatics::GetActorOfClass(GetWorld(), AXSelectorContorlActor::StaticClass()));
	if (!PlayerAction)
	{
		UE_LOG(LogTemp, Warning, TEXT("No PlayerAction!!!!!!!!!!"));
		return;
	}
	if (PlayerAction->GridIns && PlayerAction->GridIns->XGridPathFinding)
	{
		PlayerAction->GridIns->ClearStateFromTiles(ETileState::ETT_IsInPath);
		PlayerAction->GridIns->XGridPathFinding->OnPathFindingCompleted.Clear();
		PlayerAction->GridIns->XGridPathFinding->OnPathFindingCompleted.AddDynamic(this, 
				&AXFindingPathToTargetAction::OnPathFindingCompleted
			);
		TArray<FIntPoint> Path = PlayerAction->GridIns->XGridPathFinding->FindPath(PlayerAction->SelectedTile, index, Delay, bIncludeDiagonals);
	}
}

void AXFindingPathToTargetAction::EndPlay(EEndPlayReason::Type EndPlayReason)
{
	ExecuteAction({ -999, -999 });
}

void AXFindingPathToTargetAction::OnPathFindingCompleted(TArray<FIntPoint> Path)
{
	for (auto& it : Path)
	{
		PlayerAction->GridIns->AddStateToTile(it, ETileState::ETT_IsInPath);
	}
}
