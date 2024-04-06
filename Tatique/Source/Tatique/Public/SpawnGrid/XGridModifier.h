// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Pawn/XStructInfo.h"
#include "D:/UnrealProject/CombatTatique_W/CombatTatique/Tatique/Source/Tatique/XHeadFile/GridShapeEnum.h"
#include "XGridModifier.generated.h"


UCLASS()
class TATIQUE_API AXGridModifier : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AXGridModifier();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

#if WITH_EDITOR
	virtual void OnConstruction(const FTransform& Transform) override;
#endif

public:
	UPROPERTY(VisibleAnywhere, Category = MySceneComponent)
		class USceneComponent* DefaultSceneRoot;
	UPROPERTY(VisibleAnywhere)
		class UStaticMeshComponent* StaticMesh;
public:
	UPROPERTY(VisibleAnywhere)
		UEnum* GridShape;
	UPROPERTY(VisibleAnywhere)
		UEnum* TileType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EGridShapEnum GridShapeIns = EGridShapEnum::EGS_Square;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
		ETileType TileTypeIns = ETileType::ETT_Obstacle;

	//所使用的DataTable
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UDataTable* DT_GridDateTable;

	FGridShapeStruct* GetShape(const EGridShapEnum shape);

};
