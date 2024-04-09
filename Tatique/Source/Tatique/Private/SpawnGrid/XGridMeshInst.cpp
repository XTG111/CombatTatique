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
	InstancedMeshComponent->NumCustomDataFloats = 4;
	
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
void AXGridMeshInst::AddInstance(const FIntPoint Index, const FTransform Transform, const TArray<ETileState>& states)
{
	RemoveInstance(Index);
	InstancedMeshComponent->AddInstance(Transform);
	int temp = InstanceIncdexes.Add(Index);
	FLinearColor colorins;
	float isFilled = GetColorFromState(states, colorins);
	UE_LOG(LogTemp, Warning, TEXT("RGB: %f,%f,%f"),colorins.R,colorins.G,colorins.B);
	InstancedMeshComponent->SetCustomDataValue(temp, 0, colorins.R, false);
	InstancedMeshComponent->SetCustomDataValue(temp, 1, colorins.G, false);
	InstancedMeshComponent->SetCustomDataValue(temp, 2, colorins.B, false);
	InstancedMeshComponent->SetCustomDataValue(temp, 3, isFilled, false);
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

float AXGridMeshInst::GetColorFromState(const TArray<ETileState>& states, FLinearColor& color)
{
	if (states.Num() == 0)
	{
		color = FColor::Black;
		return 0.0f;
	}
	TArray<ETileState> temparray = {ETileState::ETT_Selected,ETileState::ETT_Hovered};
	for (auto& temp : temparray)
	{
		if (states.Contains(temp))
		{
			//UE_LOG(LogTemp, Warning, TEXT("ETileState::%s"), temp);
			if (temp == ETileState::ETT_Hovered)
			{
				color =  FColor::Yellow;
				UE_LOG(LogTemp, Warning, TEXT("FColor::Yellow"));
			}
			else if(temp == ETileState::ETT_Selected)
			{
				color = FColor::Red;
				UE_LOG(LogTemp, Warning, TEXT("FColor::Red"));
			}
			
			return 1.0f;
		}
	}
	color = FColor::Black;
	return 0.0f;
}

