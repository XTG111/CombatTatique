// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawn/XIncreasDecreasTileAction.h"
#include "Pawn/XSelectorContorlActor.h"
#include "SpawnGrid/XGrid.h"
#include "Kismet/GameplayStatics.h"

void AXIncreasDecreasTileAction::ExecuteAction(FIntPoint index)
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
		FVector loc = Data->Transform.GetLocation();
		loc.Z += (Increase ? 1.0f : -1.0f) * PlayerAction->GridIns->TileSize.Z;
		Data->Transform.SetLocation(loc);
		PlayerAction->GridIns->AddGridTile(Data);
	}
}
