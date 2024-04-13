// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawn/XSetTileTypeAction.h"
#include "Pawn/XSelectorContorlActor.h"
#include "SpawnGrid/XGrid.h"
#include "Kismet/GameplayStatics.h"

void AXSetTileTypeAction::ExecuteAction(FIntPoint index)
{
	PlayerAction = Cast<AXSelectorContorlActor>(UGameplayStatics::GetActorOfClass(GetWorld(), AXSelectorContorlActor::StaticClass()));
	if (!PlayerAction)
	{
		UE_LOG(LogTemp, Warning, TEXT("No PlayerAction!!!!!!!!!!"));
		return;

	}
	bool isvalid = PlayerAction->GridIns->IsIndexValid(index);
	if (isvalid)
	{
		FTileDataStruct* Data = PlayerAction->GridIns->GridTiles.Find(index);
		Data->Type = TileType;
		PlayerAction->GridIns->AddGridTile(Data);
	}
}
