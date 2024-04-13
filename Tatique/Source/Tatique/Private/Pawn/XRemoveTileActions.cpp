// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawn/XRemoveTileActions.h"
#include "Pawn/XSelectorContorlActor.h"
#include "SpawnGrid/XGrid.h"
#include "Kismet/GameplayStatics.h"

void AXRemoveTileActions::ExecuteAction(FIntPoint index)
{
	PlayerAction = Cast<AXSelectorContorlActor>(UGameplayStatics::GetActorOfClass(GetWorld(), AXSelectorContorlActor::StaticClass()));
	if (!PlayerAction)
	{
		UE_LOG(LogTemp, Warning, TEXT("No PlayerAction!!!!!!!!!!"));
		return;

	}
	UE_LOG(LogTemp, Warning, TEXT("Go Remove!!!!!!!!!!"));
	PlayerAction->GridIns->RemoveGridTile(index);
}
