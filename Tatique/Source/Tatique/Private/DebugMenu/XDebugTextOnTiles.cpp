// Fill out your copyright notice in the Description page of Project Settings.


#include "DebugMenu/XDebugTextOnTiles.h"
#include "Components/TextRenderComponent.h"
#include "Engine/TextRenderActor.h"
#include "SpawnGrid/XGrid.h"
#include "Kismet/GameplayStatics.h"
#include "Pawn/XStructInfo.h"
#include "SpawnGrid/XGridPathFinding.h"
#include "Kismet/KismetStringLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values
AXDebugTextOnTiles::AXDebugTextOnTiles()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AXDebugTextOnTiles::BeginPlay()
{
	Super::BeginPlay();
	GridIns = Cast<AXGrid>(UGameplayStatics::GetActorOfClass(GetWorld(),AXGrid::StaticClass()));
	if (GridIns)
	{
		GridIns->OnTileDataUpdated.AddDynamic(this, &AXDebugTextOnTiles::UpdateTextOnTile);
		GridIns->OnGridDestroyed.AddDynamic(this, &AXDebugTextOnTiles::ClearAllTextActors);
		if (GridIns->XGridPathFinding)
		{
			GridIns->XGridPathFinding->OnPathFindingDataUpdated.AddDynamic(this, &AXDebugTextOnTiles::ReUpdateAllTextAfterDelay);
			GridIns->XGridPathFinding->OnPathFindingDataCleared.AddDynamic(this, &AXDebugTextOnTiles::ReUpdateAllTextAndColorAfterDelay_NoInput);
		}
	}
}

// Called every frame
void AXDebugTextOnTiles::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

ATextRenderActor* AXDebugTextOnTiles::GetTextActor(FIntPoint index)
{
	
	ATextRenderActor* Actor = SpawnedTexts.FindRef(index);
	if(Actor)
	{
		return Actor;
	}
	else
	{
		FTransform trans;
		FActorSpawnParameters spawnparameters;
		spawnparameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		Actor = GetWorld()->SpawnActor<ATextRenderActor>(spawnparameters);
		SpawnedTexts.Add(index, Actor);
		Actor->SetActorTickEnabled(false);
		Actor->SetActorEnableCollision(false);
		Actor->GetTextRender()->SetHorizontalAlignment(EHTA_Center);
		Actor->GetTextRender()->SetVerticalAlignment(EVRTA_TextCenter);
		return Actor;
	}
}

void AXDebugTextOnTiles::DestroyTextActor(FIntPoint index)
{
	ATextRenderActor* Actor = SpawnedTexts.FindRef(index);
	if (Actor)
	{
		Actor->Destroy();
		SpawnedTexts.Remove(index);
	}
}

void AXDebugTextOnTiles::ClearAllTextActors()
{
	for (auto& it : SpawnedTexts)
	{
		it.Value->Destroy();
	}
	SpawnedTexts.Empty();
}

void AXDebugTextOnTiles::UpdateTextOnTile(FIntPoint index)
{
	if (!bShowTileIndexes || !GridIns) return;
	if (!WantToDisplayAnyText()) return;
	FTileDataStruct* Data = GridIns->GridTiles.Find(index);
	if (Data)
	{
		bool temp = IsTileWalkAble(Data->Type);
		if (!temp)
		{
			DestroyTextActor(index);
		}
		else
		{
			TArray<FString> Text;
			TArray<int> TextLength;
			if (bShowTileIndexes)
			{
				FString text = FString::Printf(TEXT("%d.%d"), index.X, index.Y);
				Text.Add(text);
				TextLength.Add(text.Len());
			}
			if (bShowCostToEnterTile || bShowMinCostToTarget || bShowCostFromStart || bShowSortOrder)
			{
				if (GridIns->XGridPathFinding->PathFindingData.Find(index))
				{
					FPathFindingData PathFindingData = *(GridIns->XGridPathFinding->PathFindingData.Find(index));

					if (bShowCostToEnterTile)
					{
						FString text = FString::Printf(TEXT("Enter:%d"), PathFindingData.CostToEnterTile);
						Text.Add(text);
						TextLength.Add(text.Len());
					}
					if (bShowMinCostToTarget)
					{
						if (PathFindingData.MinimumCostToTarget != 999999)
						{
							FString text = FString::Printf(TEXT("Min:%d"), PathFindingData.MinimumCostToTarget);
							Text.Add(text);
							TextLength.Add(text.Len());
						}
					}
					if (bShowCostFromStart)
					{
						if (PathFindingData.CostFromStart != 999999)
						{
							FString text = FString::Printf(TEXT("Start:%d"), PathFindingData.CostFromStart);
							Text.Add(text);
							TextLength.Add(text.Len());
						}
					}
					if (bShowSortOrder)
					{
						if (GridIns->XGridPathFinding->DiscoveredTileIndexed.Find(index) != -1)
						{
							int param1 = GridIns->XGridPathFinding->DiscoveredTileIndexed.Find(index);
							int sort = GridIns->XGridPathFinding->DiscoveredTileSortingCosts[param1];
							FString text = FString::Printf(TEXT("Sort:%d(%d)"), param1, sort);
							Text.Add(text);
							TextLength.Add(text.Len());
						}
					}
				}
			}
			if (Text.Num() > 0)
			{
				ATextRenderActor* TextActor = GetTextActor(index);
				TextActor->GetTextRender()->SetText(FText::FromString(UKismetStringLibrary::JoinStringArray(Text,"\n")));
				FTransform trans;
				trans.SetLocation(Data->Transform.GetLocation() + FVector(0.0f, 0.0f, 1.0f));
				trans.SetRotation(FQuat(FRotator{ 90.0f,0.0f,180.0f }));

				float scalecontorl;
				if (GridIns->GridShape == EGridShapEnum::EGS_Triangle)
				{
					scalecontorl = 30.0f;
				}
				else
				{
					scalecontorl = 15.0f;
				}
				int indexmax;
				int maxvalue;
				UKismetMathLibrary::MaxOfIntArray(TextLength, indexmax, maxvalue);
				
				float midval = GridIns->TileSize.Y / ( maxvalue * scalecontorl);
				FVector scale{ midval,midval,midval };
				trans.SetScale3D(scale);
				TextActor->SetActorTransform(trans, false);
			}
			else
			{
				DestroyTextActor(index);
			}
		}
	}
	else
	{
		DestroyTextActor(index);
	}
}

void AXDebugTextOnTiles::UpdateTextOnAllTiles()
{
	if (WantToDisplayAnyText())
	{
		for (auto& it : GridIns->GridTiles)
		{
			UpdateTextOnTile(it.Key);
		}
	}
	else
	{
		ClearAllTextActors();
	}
}

void AXDebugTextOnTiles::ReUpdateAllTextAfterDelay(FIntPoint index)
{
	GetWorld()->GetTimerManager().SetTimer(UpdateAllTextTimer, this, &AXDebugTextOnTiles::DelayFunc, 0.1f, false);
}

void AXDebugTextOnTiles::ReUpdateAllTextAndColorAfterDelay_NoInput()
{
	GetWorld()->GetTimerManager().SetTimer(UpdateAllTextNoInputTimer, this, &AXDebugTextOnTiles::DelayFunc, 0.1f, false);
}

void AXDebugTextOnTiles::DelayFunc()
{
	GetWorld()->GetTimerManager().ClearTimer(UpdateAllTextTimer);
	GetWorld()->GetTimerManager().ClearTimer(UpdateAllTextNoInputTimer);
	UpdateTextOnAllTiles();
	UpdateStateOnAllTile();
}

bool AXDebugTextOnTiles::WantToDisplayAnyText()
{
	return bShowTileIndexes || 
		bShowCostToEnterTile  || 
		bShowMinCostToTarget || 
		bShowCostFromStart || 
		bShowSortOrder;
}

void AXDebugTextOnTiles::SetShowTileIndexes(bool bstl, bool bsctet, bool bsmctt, bool bcfs, bool bsso)
{
	bShowTileIndexes = bstl;
	bShowCostToEnterTile = bsctet;
	bShowMinCostToTarget = bsmctt;
	bShowCostFromStart = bcfs;
	bShowSortOrder = bsso;
	UpdateTextOnAllTiles();
}

void AXDebugTextOnTiles::UpdateStateOnTile(FIntPoint index)
{
	if (!GridIns || !GridIns->XGridPathFinding) return;
	if (bShowDiscoveredTiles)
	{
		if (GridIns->XGridPathFinding->DiscoveredTileIndexed.Contains(index))
		{
			GridIns->AddStateToTile(index, ETileState::ETT_IsDiscovered);
		}
		else
		{
			GridIns->RemoveStateFromTile(index, ETileState::ETT_IsDiscovered);
		}
	}
	else
	{
		GridIns->RemoveStateFromTile(index, ETileState::ETT_IsDiscovered);
	}

	if (bShowAnalysedTiles)
	{
		if (GridIns->XGridPathFinding->DiscoveredTileIndexed.Contains(index))
		{
			GridIns->AddStateToTile(index, ETileState::ETT_IsAnalysed);
		}
		else
		{
			GridIns->RemoveStateFromTile(index, ETileState::ETT_IsAnalysed);
		}
	}
	else
	{
		GridIns->RemoveStateFromTile(index, ETileState::ETT_IsAnalysed);
	}
}
	

void AXDebugTextOnTiles::UpdateStateOnAllTile()
{
	if (!GridIns) return;
	bool check = bShowDiscoveredTiles || bShowAnalysedTiles;
	if (check)
	{
		for (auto& it : GridIns->GridTiles)
		{
			UpdateStateOnTile(it.Key);
		}
	}
	else
	{
		GridIns->ClearStateFromTiles(ETileState::ETT_IsDiscovered);
		GridIns->ClearStateFromTiles(ETileState::ETT_IsAnalysed);
	}
}

void AXDebugTextOnTiles::SetShowTileStates(bool bsdt, bool bsat)
{
	bShowDiscoveredTiles = bsdt;
	bShowAnalysedTiles = bsat;
	UpdateStateOnAllTile();
}



bool AXDebugTextOnTiles::IsTileWalkAble(ETileType type)
{
	if (type == ETileType::ETT_Normal) return true;
	return false;
}

