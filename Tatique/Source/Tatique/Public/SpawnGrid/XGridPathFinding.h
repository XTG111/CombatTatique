// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "D:/UnrealProject/CombatTatique_W/CombatTatique/Tatique/Source/Tatique/XHeadFile/GridShapeEnum.h"
#include "XGridPathFinding.generated.h"

UCLASS()
class TATIQUE_API AXGridPathFinding : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AXGridPathFinding();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
public:
	UPROPERTY(VisibleAnywhere)
		class AXGrid* GridIns;
public:
	bool IsTileTypeWalkAble(const ETileType& type);
	bool IsIntEven(int num);
	TArray<FIntPoint> GetNeighborIndexes(FIntPoint index, bool bincludedia);
	TArray<FIntPoint> GetValidTileNeighbor(FIntPoint index, bool bincludedia);
	TArray<FIntPoint> GetNeighborIndexesforSquare(FIntPoint index, bool bincludedia);
	TArray<FIntPoint> GetNeighborIndexesforTriangle(FIntPoint index, bool bincludedia);
	TArray<FIntPoint> GetNeighborIndexesforHexagon(FIntPoint index);


};
