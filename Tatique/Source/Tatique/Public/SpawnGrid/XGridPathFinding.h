// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Pawn/XStructInfo.h"
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

	/*
	* Use For Find Neighbor
	*/
	bool IsTileTypeWalkAble(const ETileType& type);
	bool IsIntEven(int num);
	TArray<FIntPoint> GetNeighborIndexes(FIntPoint index, bool bincludedia);
	TArray<FPathFindingData> GetValidTileNeighbor(FIntPoint index, bool bincludedia);
	TArray<FIntPoint> GetNeighborIndexesforSquare(FIntPoint index, bool bincludedia);
	TArray<FIntPoint> GetNeighborIndexesforTriangle(FIntPoint index, bool bincludedia);
	TArray<FIntPoint> GetNeighborIndexesforHexagon(FIntPoint index);

	/*
	* Use For Path Finding
	*/
	//Ѱ·����
	TArray<FIntPoint> FindPath(const FIntPoint& start, const FIntPoint& target, bool Diagonals);
	//�ж����������Ƿ���Ч start target
	bool IsInputDataValid();
	//����������ӽڵ�
	void DiscoverTile(const FPathFindingData& TilePathData);
	//����������֮������� -- ���ڹ����յ��;���������
	int GetMinimumCostBetweenTwoTiles(const FIntPoint& index1, const FIntPoint& index2, bool Diagonals);
	//�����ڽӵ��Ƿ�����һ��;���㣬�����ж��Ƿ����յ�
	bool AnalyseNextDiscoveredTile();
	//�������·��
	TArray<FIntPoint> GerneratePath();
	//����ǰ������С���ڽӵ�ȡ��������Ϊ��һ�ֵ����
	FPathFindingData PullCheapestTileOutOfDiscoveredList();
	//�����ڽӵ�
	bool DiscoverNextNeighbor();
	//���������ĺ���λ��ѹ�뵱ǰ���ڽӵ�
	void InsertTileInDiscoveredArray(const FPathFindingData& TileData);
	//���֮ǰ������
	void ClearGenerateData();

public:
	//����������յ�
	UPROPERTY(VisibleAnywhere)
		FIntPoint StartIndex;
	UPROPERTY(VisibleAnywhere)
		FIntPoint TargetIndex;
	//�Ƿ��ǶԽ����ƶ�
	bool bIncludeDiagonals;
	//����ʱ���ڽӵ�洢����
	UPROPERTY(VisibleAnywhere)
		TArray<FIntPoint> DiscoveredTileIndexed;
	//���������Ϸ����飬����·��������������
	UPROPERTY(VisibleAnywhere)
		TArray<int> DiscoveredTileSortingCosts;
	//��ǰ���ֵķ���
	UPROPERTY(VisibleAnywhere)
		FPathFindingData CurrentDiscoveredTile;
	//��ǰ����Χ�ڽӵ���ɵ�����
	UPROPERTY(VisibleAnywhere)
		TArray<FPathFindingData> CurrentNeighbors;
	//���յ�·��������飬��ǰ����λ��+��ǰ�����·���ṹ��
	UPROPERTY(VisibleAnywhere)
		TMap<FIntPoint, FPathFindingData> PathFindingData;
	//ÿ�δ�DiscoveredTileIndexed��Ѱ�ҵ��ĺ�������
	UPROPERTY(VisibleAnywhere)
		TArray<FIntPoint> AnalysedTileIndex;
	//��ǰ�ڽӵ�ķ���
	UPROPERTY(VisibleAnywhere)
		FPathFindingData CurrentNeighbor;

};
