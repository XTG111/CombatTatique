// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Pawn/XStructInfo.h"
#include "D:/UnrealProject/CombatTatique_W/CombatTatique/Tatique/Source/Tatique/XHeadFile/GridShapeEnum.h"
#include "XGrid.generated.h"

//����ί�У���Grid�����仯ʱ������ʾText֪ͨ����
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTileDataUpdated, FIntPoint, param1);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGridDestroyed);
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

#if WITH_EDITOR
	virtual void OnConstruction(const FTransform& Transform) override;
#endif

	//����ģ��
	void DestroyGrid();

	//����Grid
	void SpawnGrid(const FVector& pCenterLocation,const FVector& pTileSize, const FIntPoint& pTileCount, const EGridShapEnum& pGridShape, bool bUseEnv);

	//��ȡ��ǰenum��Ӧ��Data����
	struct FGridShapeStruct* GetCurrentGridShape(EGridShapEnum GridShapeIns);

public:

	UPROPERTY(VisibleAnywhere, Category = MySceneComponent)
		class USceneComponent* DefaultSceneRoot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UChildActorComponent* ChildActor_GridVisual;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UChildActorComponent* ChildActor_GridPathFinding;
	UPROPERTY(VisibleAnywhere)
		class AXGridVisiual* XGridVisual;
	UPROPERTY(VisibleAnywhere)
		class AXGridPathFinding* XGridPathFinding;

	//Grid��������
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector CenterLocation = { 0.0f,0.0f,0.0f };
	//Grid�Ĵ�С
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector TileSize = { 100.0f,100.0f,50.0f };
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
	//Map
	TMap<FIntPoint, FTileDataStruct> GridTiles;

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
	ETileType TraceForGround(const FTransform& Location, FTransform& OutLocation);

	//�����������
	FVector GetCursorLocationOnGrid(int playerindex);
	FIntPoint GetTileIndexFromWorldLocation(FVector vetor);
	FIntPoint GetTileIndexUnderCursor(int playerindex);

	//ѡ��������������
	void AddStateToTile(const FIntPoint& index, const ETileState& state);
	//�Ƴ�����ѡ������
	void RemoveStateFromTile(const FIntPoint& index, const ETileState& state);

	void AddGridTile(FTileDataStruct* TileData);

	//��ȡ��ǰ������
	FVector GetTileScale();
	//�жϵ�ǰ��ԣ��Ƿ���������������
	bool IsIndexValid(FIntPoint index);
	//�Ƴ����ڵĸ���
	void RemoveGridTile(FIntPoint index);

	//���ڿ���Ѱ�Ҹ��ӵ���Χ����
	TArray<FIntPoint> GetAllTilesWithState(const ETileState& type);
	void ClearStateFromTiles(const ETileState& type);

//ί��
public:
	UPROPERTY(VisibleAnywhere)
		FOnTileDataUpdated OnTileDataUpdated;
	UPROPERTY(VisibleAnywhere)
		FOnGridDestroyed OnGridDestroyed;

};
