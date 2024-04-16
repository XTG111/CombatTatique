// Fill out your copyright notice in the Description page of Project Settings.


#include "DebugMenu/XDebugTextOnTiles.h"
#include "Components/TextRenderComponent.h"
#include "Engine/TextRenderActor.h"
#include "SpawnGrid/XGrid.h"
#include "Kismet/GameplayStatics.h"
#include "Pawn/XStructInfo.h"

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
	ATextRenderActor* Actor = *(SpawnedTexts.Find(index));
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
			ATextRenderActor* TextActor = GetTextActor(index);
			FString text = FString::Printf(TEXT("%d.%d"), index.X, index.Y);
			TextActor->GetTextRender()->SetText(FText::FromString(text));
			FTransform trans;
			trans.SetLocation(Data->Transform.GetLocation() + FVector(0.0f, 0.0f, 1.0f));
			trans.SetRotation(FQuat(FRotator{ 90.0f,0.0f,180.0f }));
			trans.SetScale3D(FVector{ 2.0f,2.0f,2.0f });
			TextActor->SetActorTransform(trans, false);
		}
	}
	else
	{
		DestroyTextActor(index);
	}
	
}

void AXDebugTextOnTiles::SetShowTileIndexes(bool bstl)
{
	bShowTileIndexes = bstl;
	if (bShowTileIndexes)
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

bool AXDebugTextOnTiles::IsTileWalkAble(ETileType type)
{
	if (type == ETileType::ETT_Normal) return true;
	return false;
}

