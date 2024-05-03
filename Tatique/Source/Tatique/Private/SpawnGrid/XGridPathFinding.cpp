// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnGrid/XGridPathFinding.h"
#include "SpawnGrid/XGrid.h"
#include "D:/UnrealProject/CombatTatique_W/CombatTatique/Tatique/Source/Tatique/XHeadFile/GridShapeEnum.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values
AXGridPathFinding::AXGridPathFinding()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AXGridPathFinding::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AXGridPathFinding::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


bool AXGridPathFinding::IsTileTypeWalkAble(const ETileType& type)
{
	if (type == ETileType::ETT_Normal)
	{
		//UE_LOG(LogTemp, Warning, TEXT("ETileType::ETT_Normal"));
		return true;
	}
	else
	{
		return false;
	}
}

bool AXGridPathFinding::IsIntEven(int num)
{
	if (num % 2 == 0) return true;
	return false;
}

TArray<FIntPoint> AXGridPathFinding::GetNeighborIndexes(FIntPoint index, bool bincludedia)
{
	TArray<FIntPoint> Res;
	if (!GridIns) return TArray<FIntPoint>();
	switch (GridIns->GridShape)
	{
	case EGridShapEnum::EGS_None:
		break;
	case EGridShapEnum::EGS_Square:
		Res = GetNeighborIndexesforSquare(index, bincludedia);
		break;
	case EGridShapEnum::EGS_Triangle:
		Res = GetNeighborIndexesforTriangle(index, bincludedia);
		break;
	case EGridShapEnum::EGS_Hexagon:
		Res = GetNeighborIndexesforHexagon(index);
		break;
	}
	return Res;
}

TArray<FPathFindingData> AXGridPathFinding::GetValidTileNeighbor(FIntPoint index, bool bincludedia)
{
	TArray<FPathFindingData> Res;
	if (!GridIns) return TArray<FPathFindingData>();
	FTileDataStruct InputData = GridIns->GridTiles.FindRef(index);
	TArray<FIntPoint> temp = GetNeighborIndexes(index, bincludedia);
	for (auto& it : temp)
	{
		FTileDataStruct Data = GridIns->GridTiles.FindRef(it);
		if (IsTileTypeWalkAble(Data.Type))
		{
			float deltaZ = abs(Data.Transform.GetLocation().Z - InputData.Transform.GetLocation().Z);
			bool check = deltaZ <= GridIns->TileSize.Z;
			if (check)
			{
				FPathFindingData PFD(Data.Index, 1, 999999, 999999, index);
				Res.Add(PFD);
			}
		}
	}
	return Res;
}

TArray<FIntPoint> AXGridPathFinding::GetNeighborIndexesforSquare(FIntPoint index, bool bincludedia)
{
	TArray<FIntPoint> Res;
	FIntPoint param1 = index + FIntPoint(1, 0);
	FIntPoint param2 = index + FIntPoint(-1, 0);
	FIntPoint param3 = index + FIntPoint(0, 1);
	FIntPoint param4 = index + FIntPoint(0, -1);
	Res.Add(param1);
	Res.Add(param2);
	Res.Add(param3);
	Res.Add(param4);
	if (!bincludedia)
	{
		return Res;
	}
	else
	{
		param1 = index + FIntPoint(1, 1);
		param2 = index + FIntPoint(-1, -1);
		param3 = index + FIntPoint(-1, 1);
		param4 = index + FIntPoint(1, -1);
		Res.Add(param1);
		Res.Add(param2);
		Res.Add(param3);
		Res.Add(param4);
	}
	return Res;
}

TArray<FIntPoint> AXGridPathFinding::GetNeighborIndexesforTriangle(FIntPoint index, bool bincludedia)
{
	TArray<FIntPoint> Res;
	FIntPoint param1 = index + FIntPoint(0, 1);
	FIntPoint param2 = index + FIntPoint(0, -1);
	Res.Add(param1);
	Res.Add(param2);
	bool temp = IsIntEven(index.X) == IsIntEven(index.Y);
	if (temp)
	{
		Res.Add(index + FIntPoint(-1, 0));
	}
	else
	{
		Res.Add(index + FIntPoint(1, 0));
	}
	if (!bincludedia)
	{
		return Res;
	}
	else
	{
		if (temp)
		{
			Res.Add(index + FIntPoint(1, 0));
			Res.Add(index + FIntPoint(-1, -2));
			Res.Add(index + FIntPoint(-1, 2));
		}
		else
		{
			Res.Add(index + FIntPoint(-1, 0));
			Res.Add(index + FIntPoint(1, -2));
			Res.Add(index + FIntPoint(1, 2));
		}
	}
	return Res;
}

TArray<FIntPoint> AXGridPathFinding::GetNeighborIndexesforHexagon(FIntPoint index)
{
	TArray<FIntPoint> Res;
	FIntPoint param1 = index + FIntPoint(1, 1);
	FIntPoint param2 = index + FIntPoint(0, 2);
	FIntPoint param3 = index + FIntPoint(-1, 1);
	FIntPoint param4 = index + FIntPoint(-1, -1);
	FIntPoint param5 = index + FIntPoint(0, -2);
	FIntPoint param6 = index + FIntPoint(1, -1);
	Res.Add(param1);
	Res.Add(param2);
	Res.Add(param3);
	Res.Add(param4);
	Res.Add(param5);
	Res.Add(param6);
	return Res;
}

TArray<FIntPoint> AXGridPathFinding::FindPath(const FIntPoint& start, const FIntPoint& target, float delay, bool Diagonals)
{
	StartIndex = start;
	TargetIndex = target;
	Delay = delay;
	bIncludeDiagonals = Diagonals;

	//清除之前的路径
	ClearGenerateData();
	//判断输入的合理性
	if (!IsInputDataValid())
	{
		UE_LOG(LogTemp, Warning, TEXT("Input No Valid"));
		OnPathFindingCompleted.Broadcast(TArray<FIntPoint>());
		return TArray<FIntPoint>();
	}

	int MinCostToEnd = GetMinimumCostBetweenTwoTiles(StartIndex, TargetIndex, bIncludeDiagonals);
	FPathFindingData StartData;
	StartData.Index = StartIndex;
	StartData.CostToEnterTile = 1;
	StartData.CostFromStart = 0;
	StartData.MinimumCostToTarget = MinCostToEnd;
	//为起点寻找可到的点
	DiscoverTile(StartData);
	if (Delay > 0.0f)
	{
		FindPathWithDelay();
		return TArray<FIntPoint>();
	}
	while (DiscoveredTileIndexed.Num() > 0)
	{
		//寻路
		if (AnalyseNextDiscoveredTile())
		{
			UE_LOG(LogTemp, Warning, TEXT("Find Way"));
			OnPathFindingCompleted.Broadcast(GerneratePath());
			return GerneratePath();
		}
	}
	OnPathFindingCompleted.Broadcast(TArray<FIntPoint>());
	return TArray<FIntPoint>();
}

bool AXGridPathFinding::IsInputDataValid()
{
	if (StartIndex == TargetIndex)
	{
		UE_LOG(LogTemp, Warning, TEXT("StartIndex == TargetIndex"));
		return false;
	}
	if (!GridIns->IsTileWalkable(StartIndex))
	{
		UE_LOG(LogTemp, Warning, TEXT("StartIndex No WalkAble"));
		return false;
	}
	if (!GridIns->IsTileWalkable(TargetIndex))
	{
		UE_LOG(LogTemp, Warning, TEXT("TargetIndex No WalkAble"));
		return false;
	}
	return true;
}

void AXGridPathFinding::DiscoverTile(const FPathFindingData& TilePathData)
{
	PathFindingData.Add(TilePathData.Index, TilePathData);
	//PathFindingData[TilePathData.Index] =  TilePathData;
	InsertTileInDiscoveredArray(TilePathData);
	//进行广播，该方格使得在显示文字的类中进行调用对应函数
	OnPathFindingDataUpdated.Broadcast(TilePathData.Index);

}

int AXGridPathFinding::GetMinimumCostBetweenTwoTiles(const FIntPoint& index1, const FIntPoint& index2, bool Diagonals)
{
	int Res;
	switch (GridIns->GridShape)
	{
	case EGridShapEnum::EGS_None:
		break;
	case EGridShapEnum::EGS_Square:
		Res = CaculateCostForSquare(index1, index2, Diagonals);
		break;
	case EGridShapEnum::EGS_Triangle:
		Res = CaculateCostForTriangle(index1, index2, Diagonals);
		break;
	case EGridShapEnum::EGS_Hexagon:
		Res = CaculateCostForHexagon(index1, index2);
		break;
	}
	return Res;
}

int AXGridPathFinding::CaculateCostForSquare(const FIntPoint& index1, const FIntPoint& index2, bool Diagonals)
{
	auto temp = index1 - index2;
	temp.X = abs(temp.X);
	temp.Y = abs(temp.Y);
	if (Diagonals)
	{
		return temp.X > temp.Y ? temp.X : temp.Y;
	}
	else
	{
		return temp.X + temp.Y;
	}
}

int AXGridPathFinding::CaculateCostForHexagon(const FIntPoint& index1, const FIntPoint& index2)
{
	auto temp = index1 - index2;
	temp.X = abs(temp.X);
	temp.Y = abs(temp.Y);
	int res = temp.X + (temp.Y - temp.X) / 2 > 0 ? (temp.Y - temp.X) / 2 : 0;
	return res;
}

int AXGridPathFinding::CaculateCostForTriangle(const FIntPoint& index1, const FIntPoint& index2, bool Diagonals)
{
	auto temp = index1 - index2;
	temp.X = abs(temp.X);
	temp.Y = abs(temp.Y);
	if (Diagonals)
	{
		return temp.X + temp.Y;
	}
	else
	{
		int x = temp.X;
		int y = temp.Y;
		bool control1 = index2.X < index1.X;
		bool control2 = IsIntEven(index1.X) == IsIntEven(index1.Y);
		bool choose1 = control1 ? (x <= y) : ((x - 1) <= y);
		bool choose2 = control1 ? ((x - 1) <= y) : (x <= y);
		bool choose = control2 ? choose2 : choose1;
		if (choose)
		{
			return x + y;
		}
		else
		{
			if (IsIntEven(x) == IsIntEven(y))
			{
				return x * 2;
			}
			else
			{
				int param1 = control1 ? -1 : 1;
				int param2 = control2 ? param1 : param1 * (-1);
				return x * 2 + param2;
			}
		}
	}
}

//返回节点是否为终点的判断
bool AXGridPathFinding::AnalyseNextDiscoveredTile()
{
	//首先将消耗最小的节点取出，从存储数组和排序数组中移除（一定是第一个元素），然后加入到分析数组中
	CurrentDiscoveredTile = PullCheapestTileOutOfDiscoveredList();
	//获取当前点的下一步可移动的点
	CurrentNeighbors = GetValidTileNeighbor(CurrentDiscoveredTile.Index, bIncludeDiagonals);
	if(CurrentNeighbors.Num() == 0) UE_LOG(LogTemp, Warning, TEXT("No CurrentNeighbors"));
	while (CurrentNeighbors.Num() > 0)
	{
		if (DiscoverNextNeighbor())
		{
			return true;
		}
	}
	return false;
}

TArray<FIntPoint> AXGridPathFinding::GerneratePath()
{
	FIntPoint Current = TargetIndex;
	TArray<FIntPoint> InvertedPath, Res;
	while (Current != StartIndex)
	{
		InvertedPath.Add(Current);
		Current = PathFindingData[Current].PreviousIndex;
	}
	for (int i = InvertedPath.Num() - 1; i >= 0; i--)
	{
		//UE_LOG(LogTemp, Warning, TEXT("InvertedPath[i]:%d,%d"), InvertedPath[i].X, InvertedPath[i].Y);
		Res.Add(InvertedPath[i]);
	}
	return Res;
}

FPathFindingData AXGridPathFinding::PullCheapestTileOutOfDiscoveredList()
{
	FIntPoint TileIndex = DiscoveredTileIndexed[0];
	DiscoveredTileIndexed.RemoveAt(0);
	DiscoveredTileSortingCosts.RemoveAt(0);
	AnalysedTileIndex.Add(TileIndex);
	//获取存在于结果Map中的数据，如果没有就返回空
	FPathFindingData res = PathFindingData[TileIndex];
	return res;
}

bool AXGridPathFinding::DiscoverNextNeighbor()
{
	CurrentNeighbor = CurrentNeighbors[0];
	CurrentNeighbors.RemoveAt(0);
	
	//如果在分析数组中已经存在说明之前遍历过，即往回走了，直接返回false
	if(AnalysedTileIndex.Contains(CurrentNeighbor.Index)) return false;
	//计算起点到当前点的消耗，就是起点到前一个点的消耗 + 前一个点到目前点的消耗
	int CostFromStart = CurrentDiscoveredTile.CostFromStart + CurrentNeighbor.CostToEnterTile;
	
	//判断该点是否存在于之前点的邻接点但还未遍历的数组中
	//如果在
	int IndexInDiscovered = DiscoveredTileIndexed.Find(CurrentNeighbor.Index);
	if (IndexInDiscovered != -1)
	{
		CurrentNeighbor = PathFindingData[CurrentNeighbor.Index];
		if (CostFromStart >= CurrentNeighbor.CostFromStart)
		{
			
			return false;
		}
		else
		{
			DiscoveredTileIndexed.RemoveAt(IndexInDiscovered);
			DiscoveredTileSortingCosts.RemoveAt(IndexInDiscovered);
		}
	}
	//如果不在，那么直接加入就行了
	int MinimumCostToTarget = GetMinimumCostBetweenTwoTiles(CurrentNeighbor.Index, TargetIndex, bIncludeDiagonals);
	UE_LOG(LogTemp, Warning, TEXT("CurrentNeighbor:%d,%d,CostFromStart:%d,MinimumCostToTarget:%d"), CurrentNeighbor.Index.X, CurrentNeighbor.Index.Y, CostFromStart, MinimumCostToTarget);
	FPathFindingData temp(CurrentNeighbor.Index, CurrentNeighbor.CostToEnterTile, CostFromStart, MinimumCostToTarget, CurrentDiscoveredTile.Index);
	DiscoverTile(temp);
	if (CurrentNeighbor.Index == TargetIndex)
	{
		return true;
	}
	else return false;
}

void AXGridPathFinding::InsertTileInDiscoveredArray(const FPathFindingData& TileData)
{
	//计算当前点的消耗
	int SortingData = GetTileSortingData(TileData);
	//如果排序数组长度为0，或者当前点的SortingData比排序数组中都大，那么直接压入
	if (DiscoveredTileSortingCosts.Num() == 0)
	{
		//都是在对应的队尾加入元素，保证顺序
		DiscoveredTileSortingCosts.Add(SortingData);
		DiscoveredTileIndexed.Add(TileData.Index);
	}
	else
	{
		if (SortingData >= DiscoveredTileSortingCosts.Last())
		{
			DiscoveredTileSortingCosts.Add(SortingData);
			DiscoveredTileIndexed.Add(TileData.Index);
		}
		else
		{
			for (int i = 0;i<DiscoveredTileSortingCosts.Num();i++)
			{
				if (SortingData < DiscoveredTileSortingCosts[i])
				{
					DiscoveredTileSortingCosts.Insert(SortingData, i);
					DiscoveredTileIndexed.Insert(TileData.Index,i);
					break;
				}
			}
		}
	}
}

void AXGridPathFinding::ClearGenerateData()
{
	PathFindingData.Empty();
	DiscoveredTileSortingCosts.Empty();
	DiscoveredTileIndexed.Empty();
	AnalysedTileIndex.Empty();
	OnPathFindingDataCleared.Broadcast();
}

bool AXGridPathFinding::IsDiagonal(FIntPoint index1, FIntPoint index2)
{
	//通过GetNeighborIndexes查询不包含斜方向上的点数组，判断Index2是否在其中
	bool res = GetNeighborIndexes(index1, false).Contains(index2);
	return !res;
}

int AXGridPathFinding::GetTileSortingData(const FPathFindingData& TileData)
{
	int add = IsDiagonal(TileData.Index, TileData.PreviousIndex) ? 1 : 0;
	int base = (TileData.CostFromStart + TileData.MinimumCostToTarget) * 2;
	return add + base;
}

void AXGridPathFinding::FindPathWithDelay()
{
	FLatentActionInfo LatentInfo;
	LatentInfo.CallbackTarget = this;
	LatentInfo.ExecutionFunction = FName("FindPathWithDelay");
	LatentInfo.UUID = 111;
	GetWorldTimerManager().ClearTimer(ControlFindPathTime);
	if (DiscoveredTileIndexed.Num() > 0)
	{
		if (AnalyseNextDiscoveredTile())
		{
			OnPathFindingCompleted.Broadcast(GerneratePath());
		}
		else
		{
			//RetriggerableDelay会自动重置延迟时间
			//UKismetSystemLibrary::RetriggerableDelay(this, Delay, LatentInfo);
			GetWorldTimerManager().SetTimer(ControlFindPathTime, this, &AXGridPathFinding::FindPathWithDelay, Delay, false);
		}
	}
	else
	{
		OnPathFindingCompleted.Broadcast(TArray<FIntPoint>());
	}
}

