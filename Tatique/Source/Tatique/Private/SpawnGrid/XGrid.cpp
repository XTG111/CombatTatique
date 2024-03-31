// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnGrid/XGrid.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AXGrid::AXGrid()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("MyRootComponent"));
	RootComponent = DefaultSceneRoot;
	InstancedMeshComponent = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("InstancedMeshComponent"));

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
	Super::OnConstruction(Transform);
	SpawnGrid();
}

void AXGrid::DestroyGrid()
{
	if (InstancedMeshComponent)
	{
		InstancedMeshComponent->ClearInstances();
	}
}

void AXGrid::SpawnGrid()
{
	CenterLocation = GetActorLocation();
	TileSize = TileSize;
	TileCount.X = UKismetMathLibrary::Round(TileCount.X);
	TileCount.Y = UKismetMathLibrary::Round(TileCount.Y);

	GridShape = GridShape;

	DestroyGrid();

	FGridShapeStruct* curGrid = GetCurrentGridShape(GridShape);

	if (!curGrid)
	{
		UE_LOG(LogTemp, Warning, TEXT("No curGrid"));
		return;
	}

	InstancedMeshComponent->SetStaticMesh(curGrid->FlatMesh);
	InstancedMeshComponent->SetMaterial(0, curGrid->FlatBorderMaterial);
	
	//寻找生成起点，左下角
	CalculateCenterAndBottomLeft(CenterLocation, GridBottomLeftCornerLoc);

	//x,y方向循环生成
	for (int i = 0; i < TileCount.X - 1; i++)
	{
		if (GridShape == EGridShapEnum::EGS_Hexagon)
		{
			int k = IsIntEven(i) ? 0 : 1;
			int bor = UKismetMathLibrary::Round(TileCount.Y) * 2 - 1;
			for (int j = k; j < bor;)
			{
				SetTileGrid(i, j, curGrid);
				j += 2;
			}
		}
		else
		{
			for (int j = 0; j < TileCount.Y - 1; j++)
			{
				SetTileGrid(i, j, curGrid);
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
	float tempx;
	float tempy;
	FVector div;
	switch (GridShape)
	{
	case EGridShapEnum::EGS_Squard:

		//中心点需要与Grid的大小匹配
		CenterLoc = SnapVectorToVector(CenterLoc, TileSize);

		//计算左下角起始位置，中心点先左下方向回退x/2 和 y/2个Grid大小
		//1. 首先判断当前x,y方向上个数是否为偶数
		tempx = IsFloatEven(TileCount.X) ? TileCount.X : TileCount.X - 1.0f;
		tempy = IsFloatEven(TileCount.Y) ? TileCount.Y : TileCount.Y - 1.0f;
		div = { TileSize.X * tempx / 2,TileSize.Y * tempy / 2,0.0f };

		BottomLeftLoc = CenterLoc - div;

		break;
	case EGridShapEnum::EGS_Triangle:
		//正三角形，沿x,y,z移动的倍数导致Center离开某个三角形
		multemp = { 2.0f,1.0f,1.0f };
		CenterLoc = SnapVectorToVector(CenterLoc, TileSize * multemp);
		//计算左下角起始位置
		tempx = TileCount.X - 1.0f;
		tempy = TileCount.Y - 1.0f;
		div = { TileSize.X * tempx / 2.0f,TileSize.Y * tempy / 4.0f,0.0f };
		BottomLeftLoc = CenterLoc - SnapVectorToVector(div, TileSize*multemp);
		break;
	case EGridShapEnum::EGS_Hexagon:
		//正六边形，沿x,y,z移动的倍数导致Center离开某个三角形
		multemp = { 1.5f,1.0f,1.0f };
		CenterLoc = SnapVectorToVector(CenterLoc, TileSize * multemp);
		//计算左下角起始位置
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
	case EGridShapEnum::EGS_Squard:
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

void AXGrid::SetTileGrid(int x, int y, const FGridShapeStruct* curGrid)
{
	FTransform TileTransform;
	TileTransform.SetLocation(GetTileLocationFromGridIndex(x,y));
	TileTransform.SetRotation(FQuat::MakeFromEuler(GetTileRotationFromGridIndex(x, y)));
	TileTransform.SetScale3D(TileSize / (curGrid->MeshSize));

	InstancedMeshComponent->AddInstanceWorldSpace(TileTransform);
}

