// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnGrid/XGridMeshInst.h"
#include "Components/InstancedStaticMeshComponent.h"

// Sets default values
AXGridMeshInst::AXGridMeshInst()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	InstancedMeshComponent = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("InstancedMeshComponent"));
	InstancedMeshComponent->SetCollisionObjectType(ECC_WorldStatic);
	InstancedMeshComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	InstancedMeshComponent->SetCollisionResponseToChannel(ECC_GameTraceChannel2, ECR_Block);
	
}

// Called when the game starts or when spawned
void AXGridMeshInst::BeginPlay()
{
	Super::BeginPlay();
	SetActorTickEnabled(false);
	
}

// Called every frame
void AXGridMeshInst::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

//添加新生成的网格
void AXGridMeshInst::AddInstance(const FIntPoint Index, const FTransform Transform)
{
	RemoveInstance(Index);
	InstancedMeshComponent->AddInstance(Transform);
	InstanceIncdexes.Add(Index);
}

//移除一个网格
void AXGridMeshInst::RemoveInstance(const FIntPoint Index)
{
	if (!InstanceIncdexes.Contains(Index)) return;
	InstancedMeshComponent->RemoveInstance(InstanceIncdexes.Find(Index));
	InstanceIncdexes.Remove(Index);
}

//清空网格
void AXGridMeshInst::ClearInstance()
{
	InstancedMeshComponent->ClearInstances();
	InstanceIncdexes.Empty();
}

//初始化所有网格
void AXGridMeshInst::InitializeGridMeshInst(UStaticMesh* Mesh, UMaterialInterface* Material, FLinearColor Color, ECollisionEnabled::Type CollisionType)
{
	InstancedMeshComponent->SetStaticMesh(Mesh);
	InstancedMeshComponent->SetMaterial(0, Material);
	FVector ColorVector = { Color.R,Color.G,Color.B };
	InstancedMeshComponent->SetVectorParameterValueOnMaterials("Color", ColorVector);
	InstancedMeshComponent->SetCollisionEnabled(CollisionType);
}

