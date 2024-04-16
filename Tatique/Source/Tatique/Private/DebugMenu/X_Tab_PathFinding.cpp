// Fill out your copyright notice in the Description page of Project Settings.


#include "DebugMenu/X_Tab_PathFinding.h"
#include "Components/CheckBox.h"
#include "DebugMenu/XButtonAction.h"
#include "DebugMenu/XDebugTextOnTiles.h"
#include "Kismet/GameplayStatics.h"

void UX_Tab_PathFinding::NativeConstruct()
{
	DebugTextsOnTilesActor = Cast<AXDebugTextOnTiles>(UGameplayStatics::GetActorOfClass(GetWorld(),AXDebugTextOnTiles::StaticClass()));
	CheckBox_ShowIndexesOnTiles->SetIsChecked(DebugTextsOnTilesActor->bShowTileIndexes);

	CheckBox_ShowIndexesOnTiles->OnCheckStateChanged.AddDynamic(this, &UX_Tab_PathFinding::SetShowTileIndexes);
}

void UX_Tab_PathFinding::SetShowTileIndexes(bool bsti)
{
	DebugTextsOnTilesActor->SetShowTileIndexes(bsti);
}