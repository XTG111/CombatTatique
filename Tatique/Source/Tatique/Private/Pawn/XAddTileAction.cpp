// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawn/XAddTileAction.h"
#include "Pawn/XSelectorContorlActor.h"
#include "SpawnGrid/XGrid.h"
#include "Kismet/GameplayStatics.h"

void AXAddTileAction::ExecuteAction(FIntPoint index)
{
	PlayerAction = Cast<AXSelectorContorlActor>(UGameplayStatics::GetActorOfClass(GetWorld(), AXSelectorContorlActor::StaticClass()));
	if (!PlayerAction)
	{
		UE_LOG(LogTemp, Warning, TEXT("No PlayerAction!!!!!!!!!!"));
		return;

	}
	bool isvalid = PlayerAction->GridIns->IsIndexValid(index);
	if (!isvalid)
	{
		FVector loc = PlayerAction->GridIns->GetTileLocationFromGridIndex(index.X, index.Y);
		FTransform TileTransform;
		FTransform curTileTransform;
		TileTransform.SetLocation(loc);
		PlayerAction->GridIns->TraceForGround(TileTransform, curTileTransform);

		FTransform endTileTransform;
		endTileTransform.SetLocation(curTileTransform.GetLocation());
		endTileTransform.SetRotation(FQuat::MakeFromEuler(PlayerAction->GridIns->GetTileRotationFromGridIndex(index.X,index.Y)));
		endTileTransform.SetScale3D(PlayerAction->GridIns->GetTileScale());
		FTileDataStruct data{ index,ETileType::ETT_Normal ,endTileTransform };
		PlayerAction->GridIns->AddGridTile(&data);
	}
}
