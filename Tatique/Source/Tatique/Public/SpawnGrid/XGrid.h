// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/DataTable.h"
#include "D:/UnrealProject/CombatTatique_W/CombatTatique/Tatique/Source/Tatique/XHeadFile/GridShapeEnum.h"
#include "XGrid.generated.h"


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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		UMaterialInterface* FlayFilledMaterial;
};

UCLASS()
class TATIQUE_API AXGrid : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AXGrid();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

//#if WITH_EDITOR
//	virtual void OnConstruction(const FTransform& Transform) override;
//#endif

	//����ģ��
	void DestroyGrid();

	//����Grid
	void SpawnGrid(const FVector& pCenterLocation,const FVector& pTileSize, const FIntPoint& pTileCount, const EGridShapEnum& pGridShape, bool bUseEnv);

	//��ȡ��ǰenum��Ӧ��Data����
	struct FGridShapeStruct* GetCurrentGridShape(EGridShapEnum GridShapeIns);

public:

	UPROPERTY(VisibleAnywhere, Category = MySceneComponent)
		class USceneComponent* DefaultSceneRoot;
	//Grid Static Mesh
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class UInstancedStaticMeshComponent* InstancedMeshComponent;
	//Grid��������
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector CenterLocation = { 0.0f,0.0f,0.0f };
	//Grid�Ĵ�С
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector TileSize = { 100.0f,100.0f,100.0f };
	//���ɸ�����x��y�ֱ��¼
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FIntPoint TileCount = { 10,10 };
	//ö������ Grid��Shape
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EGridShapEnum GridShape = EGridShapEnum::EGS_Square;
	//����λ�õ���ʼ�㣬Ĭ������Ϊ���½�
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		FVector GridBottomLeftCornerLoc;
	//ƫ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Offset = 2.0f;

	//��ʹ�õ�DataTable
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UDataTable* DT_GridDateTable;
	//��ʹ�õ�Enum
	UEnum* MyEnumPtr;

public:
	//��V1��V2��ֵ�ӽ�������GridȺ�����ĺ�Grid�Ĵ�Сһ��
	FVector SnapVectorToVector(const FVector& V1, const FVector& V2);
	//�ж��Ƿ�2����
	bool IsFloatEven(float value);
	bool IsIntEven(int value);

	//��ȡGrid��Ⱥ������λ�ú����½Ǳ������
	void CalculateCenterAndBottomLeft(FVector& CenterLoc, FVector& BottomLeftLoc);
	//��ȡĳ��Grid��λ��
	FVector GetTileLocationFromGridIndex(int x, int y);
	//��ȡĳ��Grid����תƫ��
	FVector GetTileRotationFromGridIndex(int x, int y);
	//����
	void SetTileGrid(int x, int y, const FGridShapeStruct* curGrid, bool bUseEnv);
	//�жϷ���
	bool TraceForGround(const FTransform& Location, FTransform& OutLocation);
	//����ƫ��
	UFUNCTION()
		void SetGridOffset(float ofs);
	
};
