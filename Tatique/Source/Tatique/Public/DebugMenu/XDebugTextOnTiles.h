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
	//������ʾ��Щ��Ϣ
	bool bShowTileIndexes = false;
	bool bShowCostToEnterTile = false;
	bool bShowMinCostToTarget = false;
	bool bShowCostFromStart = false;
	bool bShowSortOrder = false;
	bool bShowDiscoveredTiles = false;
	bool bShowAnalysedTiles = false;

public:
	//���ɻ�ȡ��ǰ���Ӷ�Ӧ��TextActor
	ATextRenderActor* GetTextActor(FIntPoint index);
	//�����ǰ���Ӷ�Ӧ��TextActor
	void DestroyTextActor(FIntPoint index);
	//������и��ӵ�TextActor
	UFUNCTION()
		void  ClearAllTextActors();
	//Ϊÿ��TextActor����Text
	UFUNCTION()
		void UpdateTextOnTile(FIntPoint index);
	UFUNCTION()
		void ReUpdateAllTextAfterDelay(FIntPoint index);
	UFUNCTION()
		void ReUpdateAllTextAndColorAfterDelay_NoInput();
	void UpdateTextOnAllTiles();
	void DelayFunc();
	bool WantToDisplayAnyText();
	//�����Ƿ���ʾ����
	void SetShowTileIndexes(bool bstl, bool bsctet, bool bsmctt, bool bcfs, bool bsso);

	//������ʾѰ·�����д���Discovered��Analysed�����еķ���
	void UpdateStateOnTile(FIntPoint index);
	void UpdateStateOnAllTile();
	void SetShowTileStates(bool bsdt, bool bsat);

	bool IsTileWalkAble(ETileType type);

	FTimerHandle UpdateAllTextTimer;
	FTimerHandle UpdateAllTextNoInputTimer;



};
