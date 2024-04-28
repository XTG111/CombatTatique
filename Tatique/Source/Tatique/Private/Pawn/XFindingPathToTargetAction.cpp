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
	if (PlayerAction->GridIns)
	{
		PlayerAction->GridIns->ClearStateFromTiles(ETileState::ETT_IsInPath);
		TArray<FIntPoint> Path = PlayerAction->GridIns->XGridPathFinding->FindPath(PlayerAction->SelectedTile, index, bIncludeDiagonals);
		if(Path.Num() == 0) UE_LOG(LogTemp, Warning, TEXT("No Path"));
		for (auto& it : Path)
		{
			UE_LOG(LogTemp, Warning, TEXT("PathFind"));
			PlayerAction->GridIns->AddStateToTile(it, ETileState::ETT_IsInPath);
		}
	}
	
}
