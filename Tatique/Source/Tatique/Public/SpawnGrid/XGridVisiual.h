// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Pawn/XStructInfo.h"
#include "XGridVisiual.generated.h"

UCLASS()
class TATIQUE_API AXGridVisiual : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AXGridVisiual();
	UPROPERTY(VisibleAnywhere, Category = MySceneComponent)
		class USceneComponent* DefaultSceneRoot;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
		class UChildActorComponent* ChildActor_GridMeshInst;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
public:
	UPROPERTY(VisibleAnywhere)
		class AXGrid* XGridIns;
	UPROPERTY(VisibleAnywhere)
		class AXGridMeshInst* XGridMeshInst;
	float Offset = 2.0f;

public:
	void InitializeGridVisual(AXGrid* XGrid);
	void SetOffsetfromGround(float ofs);
	void DestroyGridVisual();
	void UpdateTileVisual(FTileDataStruct Data);
	bool IsTileTypeWalkAble(const ETileType& type);

};
