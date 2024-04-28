// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnGrid/XGrid.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Components/ChildActorComponent.h"
#include "SpawnGrid/XGridModifier.h"
#include "SpawnGrid/XGridVisiual.h"
#include "SpawnGrid/XGridPathFinding.h"


// Sets default values
AXGrid::AXGrid()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("MyRootComponent"));
	RootComponent = DefaultSceneRoot;

	ChildActor_GridVisual = CreateDefaultSubobject<UChildActorComponent>(TEXT("ChildActor_GridVisual"));
	ChildActor_GridVisual->SetupAttachment(RootComponent);

	ChildActor_GridPathFinding = CreateDefaultSubobject<UChildActorComponent>(TEXT("ChildActor_GridPathFinding"));
	ChildActor_GridPathFinding->SetupAttachment(RootComponent);

	//InstancedMeshComponent = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("InstancedMeshComponent"));

	MyEnumPtr = FindObject<UEnum>(ANY_PACKAGE, TEXT("EGridShapEnum"), true);
}


// Called when the game starts or when spawned
void AXGrid::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AXGrid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AXGrid::OnConstruction(const FTransform& Transform)
{
	if (!ChildActor_GridVisual) return;
	XGridVisual = Cast<AXGridVisiual>(ChildActor_GridVisual->GetChildActor());
	XGridPathFinding = Cast<AXGridPathFinding>(ChildActor_GridPathFinding->GetChildActor());
	if (XGridPathFinding)
	{
		XGridPathFinding->GridIns = this;
	}
	if (!XGridVisual) return;
	SpawnGrid(GetActorLocation(), TileSize, TileCount, GridShape, true);

}

void AXGrid::AddGridTile(FTileDataStruct* TileData)
{
	GridTiles.Add(TileData->Index, *TileData);
	if (!XGridVisual) return;
	XGridVisual->UpdateTileVisual(TileData);
	OnTileDataUpdated.Broadcast(TileData->Index);
}

FVector AXGrid::GetTileScale()
{
	FGridShapeStruct* curGrid = GetCurrentGridShape(GridShape);
	FVector MeshSize = curGrid->MeshSize;
	return (TileSize / MeshSize);
}

bool AXGrid::IsIndexValid(FIntPoint index)
{
	return GridTiles.Contains(index);
}

void AXGrid::RemoveGridTile(FIntPoint index)
{
	if (XGridVisual && GridTiles.Remove(index))
	{
		UE_LOG(LogTemp, Warning, TEXT("Remove Index!!!!!!!"));
		FTransform TileTransform;
		TileTransform.SetLocation(FVector{0.0f,0.0f,0.0f});
		TileTransform.SetRotation(FQuat::MakeFromEuler(FVector{0.0f,0.0f,0.0f}));
		TileTransform.SetScale3D(FVector{1.0f,1.0f,1.0f});
		FTileDataStruct data{ index,ETileType::ETT_None ,TileTransform };

		XGridVisual->UpdateTileVisual(&data);

		OnTileDataUpdated.Broadcast(index);
	}
}

TArray<FIntPoint> AXGrid::GetAllTilesWithState(const ETileState& type)
{
	TArray<FIntPoint> Res;
	for (auto& it : GridTiles)
	{
		FTileDataStruct Data = it.Value;
		if (Data.States.Contains(type))
		{
			Res.Add(Data.Index);
		}
	}
	return Res;
}

void AXGrid::ClearStateFromTiles(const ETileState& type)
{
	TArray<FIntPoint> temp = GetAllTilesWithState(type);
	for (auto& it : temp)
	{
		RemoveStateFromTile(it, type);
	}
}

bool AXGrid::IsTileTypeWalkAble(const ETileType& type)
{
	if (type == ETileType::ETT_Normal) return true;
	else return false;
}

bool AXGrid::IsTileWalkable(const FIntPoint& index)
{
	if (GridTiles.Find(index))
	{
		ETileType type = GridTiles.Find(index)->Type;
		if (IsTileTypeWalkAble(type)) return true;
		else return false;
	}
	return false;
}

void AXGrid::DestroyGrid()
{
	if (!XGridVisual) return;
	GridTiles.Empty();
	XGridVisual->DestroyGridVisual();
	OnGridDestroyed.Broadcast();
}

void AXGrid::SpawnGrid(const FVector& pCenterLocation, const FVector& pTileSize, const FIntPoint& pTileCount, const EGridShapEnum& pGridShape, bool bUseEnv)
{
	if (!XGridVisual) return;
	this->CenterLocation = pCenterLocation;
	this->TileSize = pTileSize;
	this->TileCount.X = pTileCount.X;
	this->TileCount.Y = pTileCount.Y;
	this->GridShape = pGridShape;

	DestroyGrid();
	XGridVisual->InitializeGridVisual(this);

	FGridShapeStruct* curGrid = GetCurrentGridShape(pGridShape);

	if (!curGrid)
	{
		UE_LOG(LogTemp, Warning, TEXT("No curGrid"));
		return;
	}

	//寻找生成起点，左下角
	CalculateCenterAndBottomLeft(this->CenterLocation, GridBottomLeftCornerLoc);

	//x,y方向循环生成
	for (int i = 0; i < TileCount.X - 1; i++)
	{
		if (GridShape == EGridShapEnum::EGS_Hexagon)
		{
			int k = IsIntEven(i) ? 0 : 1;
			int bor = TileCount.Y * 2 - 1;
			for (int j = k; j < bor;)
			{
				SetTileGrid(i, j, curGrid, bUseEnv);
				j += 2;
			}
		}
		else
		{
			for (int j = 0; j < TileCount.Y - 1; j++)
			{
				SetTileGrid(i, j, curGrid, bUseEnv);
			}
		}
	}
}

FGridShapeStruct* AXGrid::GetCurrentGridShape(EGridShapEnum GridShapeIns)
{
	if (!MyEnumPtr || !DT_GridDateTable) return nullptr;
	FName Name = FName(*(MyEnumPtr->GetDisplayNameTextByValue(static_cast<int32>(GridShapeIns)).ToString()));
	FGridShapeStruct* Row = DT_GridDateTable->FindRow<FGridShapeStruct>(Name, TEXT(""));
	return	Row;
}

FVector AXGrid::SnapVectorToVector(const FVector& V1, const FVector& V2)
{
	FVector Res;
	Res.X = FMath::RoundToFloat(V1.X / V2.X) * V2.X;
	Res.Y = FMath::RoundToFloat(V1.Y / V2.Y) * V2.Y;
	Res.Z = FMath::RoundToFloat(V1.Z / V2.Z) * V2.Z;
	return Res;
}

bool AXGrid::IsFloatEven(float value)
{
	float temp = FMath::Fmod(value, 2.0f);
	return temp == 0.0f;
}

bool AXGrid::IsIntEven(int value)
{
	int temp = FMath::Fmod(value, 2);
	return temp == 0;
}

void AXGrid::CalculateCenterAndBottomLeft(FVector& CenterLoc, FVector& BottomLeftLoc)
{
	FVector multemp;
	int tempx;
	int tempy;
	FVector div;
	switch (GridShape)
	{
	case EGridShapEnum::EGS_Square:

		//中心点需要与Grid的大小匹配
		CenterLoc = SnapVectorToVector(CenterLoc, TileSize);

		//计算左下角起始位置，中心点先左下方向回退x/2 和 y/2个Grid大小
		//1. 首先判断当前x,y方向上个数是否为偶数
		tempx = IsIntEven(TileCount.X) ? TileCount.X : TileCount.X - 1;
		tempy = IsIntEven(TileCount.Y) ? TileCount.Y : TileCount.Y - 1;
		div = { TileSize.X * tempx / 2,TileSize.Y * tempy / 2,0.0f };

		BottomLeftLoc = CenterLoc - div;

		break;
	case EGridShapEnum::EGS_Triangle:
		//正三角形，沿x,y,z移动的倍数导致Center离开某个三角形
		multemp = { 2.0f,1.0f,1.0f };
		CenterLoc = SnapVectorToVector(CenterLoc, TileSize * multemp);
		//计算左下角起始位置
		tempx = TileCount.X - 1.0f;
		tempy = TileCount.Y - 1.0f;
		div = { TileSize.X * tempx / 2.0f,TileSize.Y * tempy / 4.0f,0.0f };
		BottomLeftLoc = CenterLoc - SnapVectorToVector(div, TileSize*multemp);
		break;
	case EGridShapEnum::EGS_Hexagon:
		//正六边形，沿x,y,z移动的倍数导致Center离开某个三角形
		multemp = { 1.5f,1.0f,1.0f };
		CenterLoc = SnapVectorToVector(CenterLoc, TileSize * multemp);
		//计算左下角起始位置
		tempx = TileCount.X;
		tempy = TileCount.Y;
		div = { TileSize.X * tempx / 3.0f,TileSize.Y * tempy / 2.0f,0.0f };
		BottomLeftLoc = CenterLoc - SnapVectorToVector(div, TileSize * multemp);
		break;
	case EGridShapEnum::EGS_None:
		break;
	default:
		break;
	}
}

FVector AXGrid::GetTileLocationFromGridIndex(int x, int y)
{
	FVector multemp;
	switch (GridShape)
	{
	case EGridShapEnum::EGS_Square:
		multemp = { x * 1.0f,y * 1.0f,0.0f };
		break;
	case EGridShapEnum::EGS_Triangle:
		multemp = { x * 1.0f,y * 0.5f,0.0f };
		break;
	case EGridShapEnum::EGS_Hexagon:
		multemp = { x * 0.75f,y * 0.5f,0.0f };
		break;
	case EGridShapEnum::EGS_None:
		break;
	default:
		break;
	}
	FVector res = TileSize * multemp + GridBottomLeftCornerLoc;
	return res;
}

FVector AXGrid::GetTileRotationFromGridIndex(int x, int y)
{
	if (GridShape != EGridShapEnum::EGS_Triangle) return { 0.0f,0.0f,0.0f };
	else
	{
		float tempx = IsFloatEven(x) ? 180.0f : 0.0f;
		float tempy = IsFloatEven(y) ? 180.0f : 0.0f;
		return { 0.0f,0.0f,tempx + tempy };
	}
}

void AXGrid::SetTileGrid(int x, int y, const FGridShapeStruct* curGrid, bool bUseEnv)
{
	FTransform TileTransform;
	FIntPoint index = { x,y };
	TileTransform.SetLocation(GetTileLocationFromGridIndex(x,y));
	TileTransform.SetRotation(FQuat::MakeFromEuler(GetTileRotationFromGridIndex(x, y)));
	TileTransform.SetScale3D(TileSize / (curGrid->MeshSize));

	if (!bUseEnv)
	{
		FTileDataStruct data{ index,ETileType::ETT_Normal ,TileTransform };
		AddGridTile(&data);
	}
	else
	{
		FTransform curTileTransform;
		ETileType type = TraceForGround(TileTransform, curTileTransform);
		FTileDataStruct data{ index,type,curTileTransform };
		AddGridTile(&data);
		
	}
	
}

ETileType AXGrid::TraceForGround(const FTransform& Location, FTransform& OutLocation)
{
	float Radius;
	float divtemp;
	if (GridShape != EGridShapEnum::EGS_Triangle) divtemp = 3.0f;
	else divtemp = 5.0f;
	Radius = TileSize.X / divtemp;

	TArray<FHitResult> HitResults;
	FVector temp = { 0.0f,0.0f,500.0f };
	FVector Start = Location.GetLocation() + temp;
	FVector End = Location.GetLocation() - temp;

	UKismetSystemLibrary::SphereTraceMulti(
		GetWorld(),
		Start,
		End,
		Radius,
		UEngineTypes::ConvertToTraceType(ECC_GameTraceChannel1),
		false,
		TArray<AActor*>(),
		EDrawDebugTrace::None,
		HitResults,
		true
	);

	if (HitResults.Num() <= 0)
	{
		OutLocation = Location;
		return ETileType::ETT_None;
	}
	else
	{
		ETileType RetType = ETileType::ETT_Normal;
		FVector res;
		for (auto& hit : HitResults)
		{
			AXGridModifier* XGMActor = Cast<AXGridModifier>(hit.Actor);
			if (XGMActor == nullptr)
			{
				FVector curLoc = hit.Location;
				res.Z = UKismetMathLibrary::GridSnap_Float(curLoc.Z - Radius, TileSize.Z);
				OutLocation.SetRotation(Location.GetRotation());
				OutLocation.SetScale3D(Location.GetScale3D());
				res.X = hit.Location.X;
				res.Y = hit.Location.Y;
				OutLocation.SetLocation(res);
			}
			else
			{
				
				RetType = XGMActor->TileTypeIns;
			}
		}
		return RetType;
	}
}

FVector AXGrid::GetCursorLocationOnGrid(int playerindex)
{
	FHitResult HitResults;
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), playerindex);
	if (!PlayerController) return FVector();
	bool HitValue = PlayerController->GetHitResultUnderCursorByChannel(UEngineTypes::ConvertToTraceType(ECC_GameTraceChannel2), false, HitResults);
	if (HitValue)
	{
		return HitResults.ImpactPoint;
	}
	else
	{
		
		if (PlayerController->GetHitResultUnderCursorByChannel(UEngineTypes::ConvertToTraceType(ECC_GameTraceChannel1), false, HitResults))
		{
			return HitResults.ImpactPoint;
		}
		FVector WorldLocation;
		FVector WorldDirction;
		//获取鼠标在屏幕空间的世界坐标
		bool RValue = PlayerController->DeprojectMousePositionToWorld(WorldLocation, WorldDirction);
		
		//定义网格平面
		FVector Normal = { 0.0f,0.0f,1.0f };
		FPlane plane = UKismetMathLibrary::MakePlaneFromPointAndNormal(CenterLocation, Normal);

		//计算平面和射线的交点
		FVector LineStart = WorldLocation;
		FVector LineEnd = WorldLocation + 999999.0f * WorldDirction;
		FVector Intersection;
		float T;
		bool value = UKismetMathLibrary::LinePlaneIntersection(LineStart, LineEnd, plane, T, Intersection);
		if (value)
		{
			return Intersection;
		}
		else
		{
			FVector res = { -999.0f,-999.0f,-999.0f };
			return res;
		}
	}
}

FIntPoint AXGrid::GetTileIndexFromWorldLocation(FVector vetor)
{
	FVector LocationOnGrid = vetor - GridBottomLeftCornerLoc;
	FVector2D TileSizeVector2D = { TileSize.X,TileSize.Y };
	FVector2D SnappedLocationOnGrid;
	FVector temp;
	FVector div1;
	FVector div2;
	FIntPoint res;
	FVector2D a;
	FVector2D tempindex;
	switch (GridShape)
	{
	case EGridShapEnum::EGS_None:
		res.X = -999;
		res.Y = -999;
		break;
	case EGridShapEnum::EGS_Square:
		temp = SnapVectorToVector(LocationOnGrid, TileSize);
		SnappedLocationOnGrid = { temp.X,temp.Y };
		res.X = FMath::RoundToInt((SnappedLocationOnGrid / TileSizeVector2D).X);
		res.Y = FMath::RoundToInt((SnappedLocationOnGrid / TileSizeVector2D).Y);
		break;
	case EGridShapEnum::EGS_Triangle:
		div2 = { 1.0f,2.0f,1.0f };
		temp = SnapVectorToVector(LocationOnGrid, TileSize / div2);
		SnappedLocationOnGrid = { temp.X,temp.Y };
		res.X = FMath::RoundToInt((SnappedLocationOnGrid / TileSizeVector2D).X * 1.0f);
		res.Y = FMath::RoundToInt((SnappedLocationOnGrid / TileSizeVector2D).Y * 2.0f);
		break;
	case EGridShapEnum::EGS_Hexagon:
		div1 = { 1.0f,2.0f,1.0f };
		div2 = { 0.75f,0.25f,1.0f };
		temp = SnapVectorToVector(LocationOnGrid / div1, TileSize / div2);
		SnappedLocationOnGrid = { temp.X,temp.Y };
		a = { 0.75f,1.0f };
		tempindex = SnappedLocationOnGrid / (TileSizeVector2D * a);
		if (IsFloatEven(tempindex.X))
		{
			res.X = FMath::TruncToInt(tempindex.X);
			res.Y = FMath::TruncToInt(2 * FMath::RoundToInt(tempindex.Y / 2.0f));
		}
		else
		{
			res.X = FMath::TruncToInt(tempindex.X);
			res.Y = FMath::TruncToInt(1 + 2 * FMath::RoundToInt(tempindex.Y / 2.0f));
		}
		break;
	default:
		break;
	}
	return res;
}

FIntPoint AXGrid::GetTileIndexUnderCursor(int playerindex)
{
	FVector loc = GetCursorLocationOnGrid(playerindex);
	return GetTileIndexFromWorldLocation(loc);
}

void AXGrid::AddStateToTile(const FIntPoint& index, const ETileState& state)
{
	if (!GridTiles.Find(index)) return;
	FTileDataStruct* data = GridTiles.Find(index);
	if (!data) return;
	if ((data->States.AddUnique(state)) < 0) return;
	GridTiles.Add(data->Index, *data);
	if (!XGridVisual) return;
	XGridVisual->UpdateTileVisual(data);
	OnTileDataUpdated.Broadcast(index);
}

void AXGrid::RemoveStateFromTile(const FIntPoint& index, const ETileState& state)
{
	if (!GridTiles.Find(index)) return;
	FTileDataStruct* data = GridTiles.Find(index);
	if (!data) return;
	if (!(data->States.Remove(state))) return;
	GridTiles.Add(data->Index, *data);
	if (!XGridVisual) return;
	XGridVisual->UpdateTileVisual(data);
	OnTileDataUpdated.Broadcast(index);
}



