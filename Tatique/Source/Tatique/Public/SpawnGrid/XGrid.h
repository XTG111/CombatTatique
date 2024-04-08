// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Pawn/XStructInfo.h"
#include "D:/UnrealProject/CombatTatique_W/CombatTatique/Tatique/Source/Tatique/XHeadFile/GridShapeEnum.h"
#include "XGrid.generated.h"

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

	//销毁模板
	void DestroyGrid();

	//生成Grid
	void SpawnGrid(const FVector& pCenterLocation,const FVector& pTileSize, const FIntPoint& pTileCount, const EGridShapEnum& pGridShape, bool bUseEnv);

	//获取当前enum对应的Data数据
	struct FGridShapeStruct* GetCurrentGridShape(EGridShapEnum GridShapeIns);

public:

	UPROPERTY(VisibleAnywhere, Category = MySceneComponent)
		class USceneComponent* DefaultSceneRoot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UChildActorComponent* ChildActor_GridVisual;
	UPROPERTY(VisibleAnywhere)
		class AXGridVisiual* XGridVisual;

	//Grid生成中心
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector CenterLocation = { 0.0f,0.0f,0.0f };
	//Grid的大小
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector TileSize = { 100.0f,100.0f,50.0f };
	//生成个数以x和y分别记录
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FIntPoint TileCount = { 10,10 };
	//枚举类型 Grid的Shape
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EGridShapEnum GridShape = EGridShapEnum::EGS_Square;
	//生成位置的起始点，默认设置为左下角
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		FVector GridBottomLeftCornerLoc;
	//偏移量
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Offset = 2.0f;

	//所使用的DataTable
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UDataTable* DT_GridDateTable;
	//所使用的Enum
	UEnum* MyEnumPtr;
	//Map
	TMap<FIntPoint, FTileDataStruct> GridTiles;

public:
	//将V1向V2的值接近，想让Grid群的中心和Grid的大小一致
	FVector SnapVectorToVector(const FVector& V1, const FVector& V2);
	//判断是否被2整除
	bool IsFloatEven(float value);
	bool IsIntEven(int value);

	//获取Grid的群的中心位置和左下角遍历起点
	void CalculateCenterAndBottomLeft(FVector& CenterLoc, FVector& BottomLeftLoc);
	//获取某个Grid的位置
	FVector GetTileLocationFromGridIndex(int x, int y);
	//获取某个Grid的旋转偏移
	FVector GetTileRotationFromGridIndex(int x, int y);
	//绘制
	void SetTileGrid(int x, int y, const FGridShapeStruct* curGrid, bool bUseEnv);
	//判断方格
	ETileType TraceForGround(const FTransform& Location, FTransform& OutLocation);

	//网格吸附鼠标
	FVector GetCursorLocationOnGrid(int playerindex);
	FIntPoint GetTileIndexFromWorldLocation(FVector vetor);
	FIntPoint GetTileIndexUnderCursor(int playerindex);


	void AddGridTile(FTileDataStruct TileData);
};
