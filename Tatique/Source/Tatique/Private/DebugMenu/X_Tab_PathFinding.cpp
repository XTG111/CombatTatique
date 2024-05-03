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
	CheckBox_ShowCostToEnterTile->SetIsChecked(DebugTextsOnTilesActor->bShowCostToEnterTile);
	CheckBox_ShowMinCostToTarget->SetIsChecked(DebugTextsOnTilesActor->bShowMinCostToTarget);
	CheckBox_ShowCostFromStart->SetIsChecked(DebugTextsOnTilesActor->bShowCostFromStart);
	CheckBox_ShowSortOrder->SetIsChecked(DebugTextsOnTilesActor->bShowSortOrder);
	CheckBox_ShowDiscoveredTiles->SetIsChecked(DebugTextsOnTilesActor->bShowDiscoveredTiles);
	CheckBox_ShowAnalysedTiles->SetIsChecked(DebugTextsOnTilesActor->bShowAnalysedTiles);


	CheckBox_ShowIndexesOnTiles->OnCheckStateChanged.AddDynamic(this, &UX_Tab_PathFinding::SetShowTileIndexes);
	CheckBox_ShowCostToEnterTile->OnCheckStateChanged.AddDynamic(this, &UX_Tab_PathFinding::SetShowCostToEnterTile);
	CheckBox_ShowMinCostToTarget->OnCheckStateChanged.AddDynamic(this, &UX_Tab_PathFinding::SetShowMinCostToTarget);
	CheckBox_ShowCostFromStart->OnCheckStateChanged.AddDynamic(this, &UX_Tab_PathFinding::SetShowCostFromStart);
	CheckBox_ShowSortOrder->OnCheckStateChanged.AddDynamic(this, &UX_Tab_PathFinding::SetShowSortOrder);
	CheckBox_ShowDiscoveredTiles->OnCheckStateChanged.AddDynamic(this, &UX_Tab_PathFinding::SetShowDiscoveredTiles);
	CheckBox_ShowAnalysedTiles->OnCheckStateChanged.AddDynamic(this, &UX_Tab_PathFinding::SetShowAnalysedTiles);
}	

void UX_Tab_PathFinding::SetShowTileIndexes(bool bsti)
{
	bShowIndexesOnTiles = bsti;
	DebugTextsOnTilesActor->SetShowTileIndexes(bShowIndexesOnTiles, 
		bShowCostToEnterTile,
		bShowMinCostToTarget,
		bShowCostFromStart,
		bShowSortOrder
	);
}

void UX_Tab_PathFinding::SetShowCostToEnterTile(bool bsctet)
{
	bShowCostToEnterTile = bsctet;
	DebugTextsOnTilesActor->SetShowTileIndexes(bShowIndexesOnTiles,
		bShowCostToEnterTile,
		bShowMinCostToTarget,
		bShowCostFromStart,
		bShowSortOrder
	);
}

void UX_Tab_PathFinding::SetShowMinCostToTarget(bool bsmctt)
{
	bShowMinCostToTarget = bsmctt;
	DebugTextsOnTilesActor->SetShowTileIndexes(bShowIndexesOnTiles,
		bShowCostToEnterTile,
		bShowMinCostToTarget,
		bShowCostFromStart,
		bShowSortOrder
	);
}

void UX_Tab_PathFinding::SetShowCostFromStart(bool bscfs)
{
	bShowCostFromStart = bscfs;
	DebugTextsOnTilesActor->SetShowTileIndexes(bShowIndexesOnTiles,
		bShowCostToEnterTile,
		bShowMinCostToTarget,
		bShowCostFromStart,
		bShowSortOrder
	);
}

void UX_Tab_PathFinding::SetShowSortOrder(bool bsso)
{
	bShowSortOrder = bsso;
	DebugTextsOnTilesActor->SetShowTileIndexes(bShowIndexesOnTiles,
		bShowCostToEnterTile,
		bShowMinCostToTarget,
		bShowCostFromStart,
		bShowSortOrder
	);
}

void UX_Tab_PathFinding::SetShowDiscoveredTiles(bool bsdt)
{
	bShowDiscoveredTiles = bsdt;
	DebugTextsOnTilesActor->SetShowTileStates(bShowDiscoveredTiles, bShowAnalysedTiles);
}

void UX_Tab_PathFinding::SetShowAnalysedTiles(bool bsat)
{
	bShowAnalysedTiles = bsat;
	DebugTextsOnTilesActor->SetShowTileStates(bShowDiscoveredTiles, bShowAnalysedTiles);
}
