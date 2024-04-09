// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnGrid/XGridVisiual.h"
#include "SpawnGrid/XGridMeshInst.h"
#include "SpawnGrid/XGrid.h"
#include "Components/ChildActorComponent.h"

// Sets default values
AXGridVisiual::AXGridVisiual()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("MyRootComponent"));
	RootComponent = DefaultSceneRoot;

	ChildActor_GridMeshInst = CreateDefaultSubobject<UChildActorComponent>(TEXT("ChildActor_GridMeshInst"));
	ChildActor_GridMeshInst->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AXGridVisiual::BeginPlay()
{
	Super::BeginPlay();
	SetActorTickEnabled(false);
	
}

// Called every frame
void AXGridVisiual::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AXGridVisiual::InitializeGridVisual(AXGrid* XGrid)
{
	if (!ChildActor_GridMeshInst) return;
	XGridIns = XGrid;
	XGridMeshInst = Cast<AXGridMeshInst>(ChildActor_GridMeshInst->GetChildActor());

	if (!XGrid || !XGridMeshInst) return;
	XGridMeshInst->InitializeGridMeshInst(XGridIns->GetCurrentGridShape(XGridIns->GridShape)->FlatMesh,
		XGridIns->GetCurrentGridShape(XGridIns->GridShape)->FlatBorderMaterial,
		FColor::Black,
		ECollisionEnabled::QueryOnly
	);

	FVector loc{ 0.0f,0.0f,0.0f };
	SetActorLocation(loc, false);
	SetOffsetfromGround(Offset);
}

void AXGridVisiual::SetOffsetfromGround(float ofs)
{
	Offset = ofs;
	FVector loc = { GetActorLocation().X,GetActorLocation().Y,Offset };
	SetActorLocation(loc, false);
}

void AXGridVisiual::DestroyGridVisual()
{
	if (!XGridMeshInst) return;
	XGridMeshInst->ClearInstance();
}

void AXGridVisiual::UpdateTileVisual(FTileDataStruct* Data)
{
	if (!XGridMeshInst) return;
	XGridMeshInst->RemoveInstance(Data->Index);
	if (!IsTileTypeWalkAble(Data->Type)) return;
	XGridMeshInst->AddInstance(Data->Index, Data->Transform, Data->States);
}

bool AXGridVisiual::IsTileTypeWalkAble(const ETileType& type)
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

