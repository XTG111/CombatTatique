// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pawn/XPlayerActions.h"
#include "D:/UnrealProject/CombatTatique_W/CombatTatique/Tatique/Source/Tatique/XHeadFile/GridShapeEnum.h"
#include "XSetTileTypeAction.generated.h"

/**
 * 
 */
UCLASS()
class TATIQUE_API AXSetTileTypeAction : public AXPlayerActions
{
	GENERATED_BODY()
public:
	virtual void ExecuteAction(FIntPoint index);
	UPROPERTY(VisibleAnywhere)
		ETileType TileType;
};
