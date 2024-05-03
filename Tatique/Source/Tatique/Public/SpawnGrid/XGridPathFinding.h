// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Pawn/XStructInfo.h"
#include "XGridPathFinding.generated.h"


//两个委托，分别用于在显示数据时进行广播
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
	//寻路函数
	TArray<FIntPoint> FindPath(const FIntPoint& start, const FIntPoint& target, bool Diagonals);
	//判断输入数据是否有效 start target
	bool IsInputDataValid();
	//向结果数组添加节点
	void DiscoverTile(const FPathFindingData& TilePathData);
	//计算两个点之间的消耗 -- 用于估计终点和途径点的消耗
	int GetMinimumCostBetweenTwoTiles(const FIntPoint& index1, const FIntPoint& index2, bool Diagonals);
	int CaculateCostForSquare(const FIntPoint& index1, const FIntPoint& index2, bool Diagonals);
	int CaculateCostForHexagon(const FIntPoint& index1, const FIntPoint& index2);
	int CaculateCostForTriangle(const FIntPoint& index1, const FIntPoint& index2, bool Diagonals);
	//分析邻接点是否是下一个途径点，并且判断是否是终点
	bool AnalyseNextDiscoveredTile();
	//生成最短路径
	TArray<FIntPoint> GerneratePath();
	//将当前消耗最小的邻接点取出，并作为下一轮的起点
	FPathFindingData PullCheapestTileOutOfDiscoveredList();
	//分析邻接点
	bool DiscoverNextNeighbor();
	//向遍历数组的合适位置压入当前的邻接点
	void InsertTileInDiscoveredArray(const FPathFindingData& TileData);
	//清除之前的数据
	void ClearGenerateData();
	//判断点是否为斜路径上的点
	bool IsDiagonal(FIntPoint index1, FIntPoint index2);
	//计算消耗
	int GetTileSortingData(const FPathFindingData& TileData);

public:
	//传入的起点和终点
	UPROPERTY(VisibleAnywhere)
		FIntPoint StartIndex;
	UPROPERTY(VisibleAnywhere)
		FIntPoint TargetIndex;
	//是否考虑对角线移动
	bool bIncludeDiagonals;
	//遍历时的邻接点存储数组
	UPROPERTY(VisibleAnywhere)
		TArray<FIntPoint> DiscoveredTileIndexed;
	//用于排序上方数组，按照路径消耗升序排序
	UPROPERTY(VisibleAnywhere)
		TArray<int> DiscoveredTileSortingCosts;
	//当前发现的方格
	UPROPERTY(VisibleAnywhere)
		FPathFindingData CurrentDiscoveredTile;
	//当前点周围邻接点组成的数组
	UPROPERTY(VisibleAnywhere)
		TArray<FPathFindingData> CurrentNeighbors;
	//最终的路径结果数组，当前方格位置+当前方格的路径结构体
	UPROPERTY(VisibleAnywhere)
		TMap<FIntPoint, FPathFindingData> PathFindingData;
	//每次从DiscoveredTileIndexed中寻找到的合理点放入
	UPROPERTY(VisibleAnywhere)
		TArray<FIntPoint> AnalysedTileIndex;
	//当前邻接点的方格
	UPROPERTY(VisibleAnywhere)
		FPathFindingData CurrentNeighbor;
public:
	UPROPERTY(VisibleAnywhere)
		FOnPathFindingDataUpdated OnPathFindingDataUpdated;
	UPROPERTY(VisibleAnywhere)
		FOnPathFindingDataCleared OnPathFindingDataCleared;
};
