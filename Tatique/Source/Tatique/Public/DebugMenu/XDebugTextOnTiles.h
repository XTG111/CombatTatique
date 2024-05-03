// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "D:/UnrealProject/CombatTatique_W/CombatTatique/Tatique/Source/Tatique/XHeadFile/GridShapeEnum.h"
#include "XDebugTextOnTiles.generated.h"

UCLASS()
class TATIQUE_API AXDebugTextOnTiles : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AXDebugTextOnTiles();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(VisibleAnywhere)
		class AXGrid* GridIns;
	TMap<FIntPoint, class ATextRenderActor*> SpawnedTexts;
	//控制显示哪些信息
	bool bShowTileIndexes = false;
	bool bShowCostToEnterTile = false;
	bool bShowMinCostToTarget = false;
	bool bShowCostFromStart = false;
	bool bShowSortOrder = false;
	bool bShowDiscoveredTiles = false;
	bool bShowAnalysedTiles = false;

public:
	//生成获取当前格子对应的TextActor
	ATextRenderActor* GetTextActor(FIntPoint index);
	//清除当前格子对应的TextActor
	void DestroyTextActor(FIntPoint index);
	//清除所有格子的TextActor
	UFUNCTION()
		void  ClearAllTextActors();
	//为每个TextActor生成Text
	UFUNCTION()
		void UpdateTextOnTile(FIntPoint index);
	UFUNCTION()
		void ReUpdateAllTextAfterDelay(FIntPoint index);
	UFUNCTION()
		void ReUpdateAllTextAndColorAfterDelay_NoInput();
	void UpdateTextOnAllTiles();
	void DelayFunc();
	bool WantToDisplayAnyText();
	//控制是否显示文字
	void SetShowTileIndexes(bool bstl, bool bsctet, bool bsmctt, bool bcfs, bool bsso);

	//用于显示寻路过程中处于Discovered和Analysed数组中的方块
	void UpdateStateOnTile(FIntPoint index);
	void UpdateStateOnAllTile();
	void SetShowTileStates(bool bsdt, bool bsat);

	bool IsTileWalkAble(ETileType type);

	FTimerHandle UpdateAllTextTimer;
	FTimerHandle UpdateAllTextNoInputTimer;



};
