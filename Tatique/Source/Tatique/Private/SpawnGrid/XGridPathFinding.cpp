// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnGrid/XGridPathFinding.h"
#include "SpawnGrid/XGrid.h"
#include "Pawn/XStructInfo.h"

// Sets default values
AXGridPathFinding::AXGridPathFinding()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AXGridPathFinding::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AXGridPathFinding::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


bool AXGridPathFinding::IsTileTypeWalkAble(const ETileType& type)
{
	if (type == ETileType::ETT_Normal)
	{
		//UE_LOG(LogTemp, Warning, TEXT("ETileType::ETT_Normal"));
		return true;
	}
	else
	{
		return false;
	}
}

bool AXGridPathFinding::IsIntEven(int num)
{
	if (num % 2 == 0) return true;
	return false;
}

TArray<FIntPoint> AXGridPathFinding::GetNeighborIndexes(FIntPoint index, bool bincludedia)
{
	TArray<FIntPoint> Res;
	if (!GridIns) return TArray<FIntPoint>();
	switch (GridIns->GridShape)
	{
	case EGridShapEnum::EGS_None:
		break;
	case EGridShapEnum::EGS_Square:
		Res = GetNeighborIndexesforSquare(index, bincludedia);
		break;
	case EGridShapEnum::EGS_Triangle:
		Res = GetNeighborIndexesforTriangle(index, bincludedia);
		break;
	case EGridShapEnum::EGS_Hexagon:
		Res = GetNeighborIndexesforHexagon(index);
		break;
	}
	return Res;
}

TArray<FIntPoint> AXGridPathFinding::GetValidTileNeighbor(FIntPoint index, bool bincludedia)
{
	TArray<FIntPoint> Res;
	if (!GridIns) return TArray<FIntPoint>();
	FTileDataStruct InputData = GridIns->GridTiles.FindRef(index);
	TArray<FIntPoint> temp = GetNeighborIndexes(index, bincludedia);
	for (auto& it : temp)
	{
		FTileDataStruct Data = GridIns->GridTiles.FindRef(it);
		if (IsTileTypeWalkAble(Data.Type))
		{
			float deltaZ = abs(Data.Transform.GetLocation().Z - InputData.Transform.GetLocation().Z);
			bool check = deltaZ <= GridIns->TileSize.Z;
			if (check)
			{
				Res.Add(Data.Index);
			}
		}
	}
	return Res;
}

TArray<FIntPoint> AXGridPathFinding::GetNeighborIndexesforSquare(FIntPoint index, bool bincludedia)
{
	TArray<FIntPoint> Res;
	FIntPoint param1 = index + FIntPoint(1, 0);
	FIntPoint param2 = index + FIntPoint(-1, 0);
	FIntPoint param3 = index + FIntPoint(0, 1);
	FIntPoint param4 = index + FIntPoint(0, -1);
	Res.Add(param1);
	Res.Add(param2);
	Res.Add(param3);
	Res.Add(param4);
	if (!bincludedia)
	{
		return Res;
	}
	else
	{
		param1 = index + FIntPoint(1, 1);
		param2 = index + FIntPoint(-1, -1);
		param3 = index + FIntPoint(-1, 1);
		param4 = index + FIntPoint(1, -1);
		Res.Add(param1);
		Res.Add(param2);
		Res.Add(param3);
		Res.Add(param4);
	}
	return Res;
}

TArray<FIntPoint> AXGridPathFinding::GetNeighborIndexesforTriangle(FIntPoint index, bool bincludedia)
{
	TArray<FIntPoint> Res;
	FIntPoint param1 = index + FIntPoint(0, 1);
	FIntPoint param2 = index + FIntPoint(0, -1);
	Res.Add(param1);
	Res.Add(param2);
	bool temp = IsIntEven(index.X) == IsIntEven(index.Y);
	if (temp)
	{
		Res.Add(index + FIntPoint(-1, 0));
	}
	else
	{
		Res.Add(index + FIntPoint(1, 0));
	}
	if (!bincludedia)
	{
		return Res;
	}
	else
	{
		if (temp)
		{
			Res.Add(index + FIntPoint(1, 0));
			Res.Add(index + FIntPoint(-1, -2));
			Res.Add(index + FIntPoint(-1, 2));
		}
		else
		{
			Res.Add(index + FIntPoint(-1, 0));
			Res.Add(index + FIntPoint(1, -2));
			Res.Add(index + FIntPoint(1, 2));
		}
	}
	return Res;
}

TArray<FIntPoint> AXGridPathFinding::GetNeighborIndexesforHexagon(FIntPoint index)
{
	TArray<FIntPoint> Res;
	FIntPoint param1 = index + FIntPoint(1, 1);
	FIntPoint param2 = index + FIntPoint(0, 2);
	FIntPoint param3 = index + FIntPoint(-1, 1);
	FIntPoint param4 = index + FIntPoint(-1, -1);
	FIntPoint param5 = index + FIntPoint(0, -2);
	FIntPoint param6 = index + FIntPoint(1, -1);
	Res.Add(param1);
	Res.Add(param2);
	Res.Add(param3);
	Res.Add(param4);
	Res.Add(param5);
	Res.Add(param6);
	return Res;
}

