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
	bool bShowTileIndexes = false;

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

	//�����Ƿ���ʾ����
	void SetShowTileIndexes(bool bstl);

	bool IsTileWalkAble(ETileType type);

};
