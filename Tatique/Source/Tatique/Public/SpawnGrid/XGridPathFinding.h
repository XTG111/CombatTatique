// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Pawn/XStructInfo.h"
#include "XGridPathFinding.generated.h"


//����ί�У��ֱ���������ʾ����ʱ���й㲥
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPathFindingDataUpdated, FIntPoint, param1);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPathFindingDataCleared);

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
	int CaculateCostForSquare(const FIntPoint& index1, const FIntPoint& index2, bool Diagonals);
	int CaculateCostForHexagon(const FIntPoint& index1, const FIntPoint& index2);
	int CaculateCostForTriangle(const FIntPoint& index1, const FIntPoint& index2, bool Diagonals);
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
	//�жϵ��Ƿ�Ϊб·���ϵĵ�
	bool IsDiagonal(FIntPoint index1, FIntPoint index2);
	//��������
	int GetTileSortingData(const FPathFindingData& TileData);

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
public:
	UPROPERTY(VisibleAnywhere)
		FOnPathFindingDataUpdated OnPathFindingDataUpdated;
	UPROPERTY(VisibleAnywhere)
		FOnPathFindingDataCleared OnPathFindingDataCleared;
};
