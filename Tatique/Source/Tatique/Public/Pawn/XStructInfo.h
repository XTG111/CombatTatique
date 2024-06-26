// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/DataTable.h"
#include "D:/UnrealProject/CombatTatique_W/CombatTatique/Tatique/Source/Tatique/XHeadFile/GridShapeEnum.h"
#include "XStructInfo.generated.h"


USTRUCT(BlueprintType)
struct FGridShapeStruct : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		FVector MeshSize;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		class UStaticMesh* Mesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		class UMaterialInterface* MeshMaterial;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		UStaticMesh* FlatMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		UMaterialInterface* FlatBorderMaterial;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	//	UMaterialInterface* FlayFilledMaterial;
};

USTRUCT(BlueprintType)
struct FTileDataStruct : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
	FTileDataStruct(){}
	FTileDataStruct(FIntPoint index, ETileType type, FTransform transform):
		Index(index),Type(type),Transform(transform)
	{}
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		FIntPoint Index;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		ETileType Type;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		FTransform Transform;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		TArray<ETileState> States;
};

USTRUCT(BlueprintType)
struct FPathFindingData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
	FPathFindingData() {}
	FPathFindingData(FIntPoint index, int costtoentertile, int costfromstart, int minimumcosttotarget, FIntPoint previousindex) :
		Index(index), CostToEnterTile(costtoentertile), CostFromStart(costfromstart),MinimumCostToTarget(minimumcosttotarget),PreviousIndex(previousindex)
	{}
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		FIntPoint Index = { -999, -999 };
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		int CostToEnterTile = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		int CostFromStart = 999999;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		int MinimumCostToTarget = 99999;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		FIntPoint PreviousIndex = { -999, -999 };
};

UCLASS()
class TATIQUE_API AXStructInfo : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AXStructInfo();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
