// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "D:/UnrealProject/CombatTatique_W/CombatTatique/Tatique/Source/Tatique/XHeadFile/GridShapeEnum.h"
#include "XGridMeshInst.generated.h"

UCLASS()
class TATIQUE_API AXGridMeshInst : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AXGridMeshInst();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class UInstancedStaticMeshComponent* InstancedMeshComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(VisibleAnywhere)
		TArray<FIntPoint> InstanceIncdexes;

public:
	void AddInstance(const FIntPoint Index, const FTransform Transform, const TArray<ETileState>& states);
	void RemoveInstance(const FIntPoint Index);
	void ClearInstance();
	void InitializeGridMeshInst(class UStaticMesh* Mesh, class UMaterialInterface* Material, FLinearColor Color, ECollisionEnabled::Type CollisionType);
	//设置鼠标悬浮或者点击时的颜色
	float GetColorFromState(const TArray<ETileState>& states, FLinearColor& color);
};
