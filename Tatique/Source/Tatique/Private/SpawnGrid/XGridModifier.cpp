// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnGrid/XGridModifier.h"

// Sets default values
AXGridModifier::AXGridModifier()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("MyRootComponent"));
	RootComponent = DefaultSceneRoot;
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(RootComponent);

	GridShape = FindObject<UEnum>(ANY_PACKAGE, TEXT("EGridShapEnum"), true);
	TileType = FindObject<UEnum>(ANY_PACKAGE, TEXT("ETileType"), true);
}

// Called when the game starts or when spawned
void AXGridModifier::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AXGridModifier::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AXGridModifier::OnConstruction(const FTransform& Transform)
{
	if (!GetShape(GridShapeIns))
	{
		UE_LOG(LogTemp, Warning, TEXT("No GetShape(GridShapeIns)"));
		return;
	}
	StaticMesh->SetStaticMesh(GetShape(GridShapeIns)->Mesh);
	FLinearColor transtemp;
	switch (TileTypeIns)
	{
	case ETileType::ETT_None:
		transtemp = FColor::Black;
		break;
	case ETileType::ETT_Normal:
		transtemp = FColor::White;
		break;
	case ETileType::ETT_Obstacle:
		transtemp = FColor::Red;
		break;
	default:
		break;
	}
	FVector ParamValue = { transtemp.R,transtemp.G,transtemp.B };
	StaticMesh->SetVectorParameterValueOnMaterials("Color", ParamValue);
	StaticMesh->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECollisionResponse::ECR_Overlap);
	SetActorHiddenInGame(true);
}

FGridShapeStruct* AXGridModifier::GetShape(const EGridShapEnum shape)
{
	if (!GridShape || !DT_GridDateTable) return nullptr;
	FName Name = FName(*(GridShape->GetDisplayNameTextByValue(static_cast<int32>(shape)).ToString()));
	FGridShapeStruct* Row = DT_GridDateTable->FindRow<FGridShapeStruct>(Name, TEXT(""));
	return	Row;
}

