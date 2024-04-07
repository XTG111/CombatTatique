// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnGrid/XGrid.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/ChildActorComponent.h"
#include "SpawnGrid/XGridModifier.h"
#include "SpawnGrid/XGridVisiual.h"


// Sets default values
AXGrid::AXGrid()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("MyRootComponent"));
	RootComponent = DefaultSceneRoot;

	ChildActor_GridVisual = CreateDefaultSubobject<UChildActorComponent>(TEXT("ChildActor_GridVisual"));
	ChildActor_GridVisual->SetupAttachment(RootComponent);

	//InstancedMeshComponent = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("InstancedMeshComponent"));

	MyEnumPtr = FindObject<UEnum>(ANY_PACKAGE, TEXT("EGridShapEnum"), true);
}


// Called when the game starts or when spawned
void AXGrid::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AXGrid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AXGrid::OnConstruction(const FTransform& Transform)
{
	if (!ChildActor_GridVisual) return;
	XGridVisual = Cast<AXGridVisiual>(ChildActor_GridVisual->GetChildActor());
	if (!XGridVisual) return;
	SpawnGrid(GetActorLocation(), TileSize, TileCount, GridShape, true);

}

void AXGrid::AddGridTile(FTileDataStruct TileData)
{
	GridTiles.Add(TileData.Index, TileData);
	if (!XGridVisual) return;
	XGridVisual->UpdateTileVisual(TileData);
}

void AXGrid::DestroyGrid()
{
	if (!XGridVisual) return;
	GridTiles.Empty();
	XGridVisual->DestroyGridVisual();
}

void AXGrid::SpawnGrid(const FVector& pCenterLocation, const FVector& pTileSize, const FIntPoint& pTileCount, const EGridShapEnum& pGridShape, bool bUseEnv)
{
	if (!XGridVisual) return;
	this->CenterLocation = pCenterLocation;
	this->TileSize = pTileSize;
	this->TileCount.X = pTileCount.X;
	this->TileCount.Y = pTileCount.Y;
	this->GridShape = pGridShape;

	DestroyGrid();
	XGridVisual->InitializeGridVisual(this);

	FGridShapeStruct* curGrid = GetCurrentGridShape(pGridShape);

	if (!curGrid)
	{
		UE_LOG(LogTemp, Warning, TEXT("No curGrid"));
		return;
	}

	//Ѱ��������㣬���½�
	CalculateCenterAndBottomLeft(this->CenterLocation, GridBottomLeftCornerLoc);

	//x,y����ѭ������
	for (int i = 0; i < TileCount.X - 1; i++)
	{
		if (GridShape == EGridShapEnum::EGS_Hexagon)
		{
			int k = IsIntEven(i) ? 0 : 1;
			int bor = TileCount.Y * 2 - 1;
			for (int j = k; j < bor;)
			{
				SetTileGrid(i, j, curGrid, bUseEnv);
				j += 2;
			}
		}
		else
		{
			for (int j = 0; j < TileCount.Y - 1; j++)
			{
				SetTileGrid(i, j, curGrid, bUseEnv);
			}
		}
	}
}

FGridShapeStruct* AXGrid::GetCurrentGridShape(EGridShapEnum GridShapeIns)
{
	if (!MyEnumPtr || !DT_GridDateTable) return nullptr;
	FName Name = FName(*(MyEnumPtr->GetDisplayNameTextByValue(static_cast<int32>(GridShapeIns)).ToString()));
	FGridShapeStruct* Row = DT_GridDateTable->FindRow<FGridShapeStruct>(Name, TEXT(""));
	return	Row;
}

FVector AXGrid::SnapVectorToVector(const FVector& V1, const FVector& V2)
{
	FVector Res;
	Res.X = FMath::RoundToFloat(V1.X / V2.X) * V2.X;
	Res.Y = FMath::RoundToFloat(V1.Y / V2.Y) * V2.Y;
	Res.Z = FMath::RoundToFloat(V1.Z / V2.Z) * V2.Z;
	return Res;
}

bool AXGrid::IsFloatEven(float value)
{
	float temp = FMath::Fmod(value, 2.0f);
	return temp == 0.0f;
}

bool AXGrid::IsIntEven(int value)
{
	int temp = FMath::Fmod(value, 2);
	return temp == 0;
}

void AXGrid::CalculateCenterAndBottomLeft(FVector& CenterLoc, FVector& BottomLeftLoc)
{
	FVector multemp;
	int tempx;
	int tempy;
	FVector div;
	switch (GridShape)
	{
	case EGridShapEnum::EGS_Square:

		//���ĵ���Ҫ��Grid�Ĵ�Сƥ��
		CenterLoc = SnapVectorToVector(CenterLoc, TileSize);

		//�������½���ʼλ�ã����ĵ������·������x/2 �� y/2��Grid��С
		//1. �����жϵ�ǰx,y�����ϸ����Ƿ�Ϊż��
		tempx = IsIntEven(TileCount.X) ? TileCount.X : TileCount.X - 1;
		tempy = IsIntEven(TileCount.Y) ? TileCount.Y : TileCount.Y - 1;
		div = { TileSize.X * tempx / 2,TileSize.Y * tempy / 2,0.0f };

		BottomLeftLoc = CenterLoc - div;

		break;
	case EGridShapEnum::EGS_Triangle:
		//�������Σ���x,y,z�ƶ��ı�������Center�뿪ĳ��������
		multemp = { 2.0f,1.0f,1.0f };
		CenterLoc = SnapVectorToVector(CenterLoc, TileSize * multemp);
		//�������½���ʼλ��
		tempx = TileCount.X - 1.0f;
		tempy = TileCount.Y - 1.0f;
		div = { TileSize.X * tempx / 2.0f,TileSize.Y * tempy / 4.0f,0.0f };
		BottomLeftLoc = CenterLoc - SnapVectorToVector(div, TileSize*multemp);
		break;
	case EGridShapEnum::EGS_Hexagon:
		//�������Σ���x,y,z�ƶ��ı�������Center�뿪ĳ��������
		multemp = { 1.5f,1.0f,1.0f };
		CenterLoc = SnapVectorToVector(CenterLoc, TileSize * multemp);
		//�������½���ʼλ��
		tempx = TileCount.X;
		tempy = TileCount.Y;
		div = { TileSize.X * tempx / 3.0f,TileSize.Y * tempy / 2.0f,0.0f };
		BottomLeftLoc = CenterLoc - SnapVectorToVector(div, TileSize * multemp);
		break;
	case EGridShapEnum::EGS_None:
		break;
	default:
		break;
	}
}

FVector AXGrid::GetTileLocationFromGridIndex(int x, int y)
{
	FVector multemp;
	switch (GridShape)
	{
	case EGridShapEnum::EGS_Square:
		multemp = { x * 1.0f,y * 1.0f,0.0f };
		break;
	case EGridShapEnum::EGS_Triangle:
		multemp = { x * 1.0f,y * 0.5f,0.0f };
		break;
	case EGridShapEnum::EGS_Hexagon:
		multemp = { x * 0.75f,y * 0.5f,0.0f };
		break;
	case EGridShapEnum::EGS_None:
		break;
	default:
		break;
	}
	FVector res = TileSize * multemp + GridBottomLeftCornerLoc;
	return res;
}

FVector AXGrid::GetTileRotationFromGridIndex(int x, int y)
{
	if (GridShape != EGridShapEnum::EGS_Triangle) return { 0.0f,0.0f,0.0f };
	else
	{
		float tempx = IsFloatEven(x) ? 180.0f : 0.0f;
		float tempy = IsFloatEven(y) ? 180.0f : 0.0f;
		return { 0.0f,0.0f,tempx + tempy };
	}
}

void AXGrid::SetTileGrid(int x, int y, const FGridShapeStruct* curGrid, bool bUseEnv)
{
	FTransform TileTransform;
	FIntPoint index = { x,y };
	TileTransform.SetLocation(GetTileLocationFromGridIndex(x,y));
	TileTransform.SetRotation(FQuat::MakeFromEuler(GetTileRotationFromGridIndex(x, y)));
	TileTransform.SetScale3D(TileSize / (curGrid->MeshSize));

	if (!bUseEnv)
	{
		FTileDataStruct data{ index,ETileType::ETT_Normal ,TileTransform };
		AddGridTile(data);
	}
	else
	{
		FTransform curTileTransform;
		ETileType type = TraceForGround(TileTransform, curTileTransform);
		FTileDataStruct data{ index,type,curTileTransform };
		AddGridTile(data);
		
	}
	
}

ETileType AXGrid::TraceForGround(const FTransform& Location, FTransform& OutLocation)
{
	float Radius;
	float divtemp;
	if (GridShape != EGridShapEnum::EGS_Triangle) divtemp = 3.0f;
	else divtemp = 5.0f;
	Radius = TileSize.X / divtemp;

	TArray<FHitResult> HitResults;
	FVector temp = { 0.0f,0.0f,500.0f };
	FVector Start = Location.GetLocation() + temp;
	FVector End = Location.GetLocation() - temp;

	FName TraceChannelName = "Ground";
	UKismetSystemLibrary::SphereTraceMulti(
		GetWorld(),
		Start,
		End,
		Radius,
		UEngineTypes::ConvertToTraceType(ECC_GameTraceChannel1),
		false,
		TArray<AActor*>(),
		EDrawDebugTrace::None,
		HitResults,
		true
	);

	if (HitResults.Num() <= 0)
	{
		OutLocation = Location;
		return ETileType::ETT_None;
	}
	else
	{
		ETileType RetType = ETileType::ETT_Normal;
		FVector res;
		for (auto hit : HitResults)
		{
			AXGridModifier* XGMActor = Cast<AXGridModifier>(hit.Actor);
			if (XGMActor == nullptr)
			{
				FVector curLoc = hit.Location;
				res.Z = UKismetMathLibrary::GridSnap_Float(curLoc.Z - Radius, TileSize.Z);
				OutLocation.SetRotation(Location.GetRotation());
				OutLocation.SetScale3D(Location.GetScale3D());
				res.X = hit.Location.X;
				res.Y = hit.Location.Y;
				OutLocation.SetLocation(res);
			}
			else
			{
				
				RetType = XGMActor->TileTypeIns;
			}
		}
		return RetType;
	}
}


