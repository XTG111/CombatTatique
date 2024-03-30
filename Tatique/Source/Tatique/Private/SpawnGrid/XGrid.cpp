// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnGrid/XGrid.h"
#include "Components/InstancedStaticMeshComponent.h"

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
	CenterLocation = CenterLocation;
	TileSize = TileSize;
	TileCount = TileCount;
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
	FVector2D Temp1 = TileCount / 2.0f;
	FVector2D Temp2 = { TileSize.X,TileSize.Y };
	Temp1 = Temp1 * Temp2;
	FVector F = { Temp1.X, Temp1.Y, 0.0f };
	GridBottomLeftCornerLoc = CenterLocation - F;

	//x,y方向循环生成
	for (int i = 0; i < TileCount.X - 1; i++)
	{
		for (int j = 0; j < TileCount.Y - 1; j++)
		{
			FTransform TileTransform;
			FVector c = { i * 1.0f,j * 1.0f,0.0f };
			TileTransform.SetLocation(GridBottomLeftCornerLoc + TileSize * c);
			TileTransform.SetScale3D(TileSize / (curGrid->MeshSize));

			InstancedMeshComponent->AddInstance(TileTransform);
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

