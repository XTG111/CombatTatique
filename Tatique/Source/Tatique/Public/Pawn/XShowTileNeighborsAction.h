// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pawn/XPlayerActions.h"
#include "XShowTileNeighborsAction.generated.h"

/**
 * 
 */
UCLASS()
class TATIQUE_API AXShowTileNeighborsAction : public AXPlayerActions
{
	GENERATED_BODY()
public:
	virtual void ExecuteAction(FIntPoint index) override;
	virtual void EndPlay(EEndPlayReason::Type EndPlayReason) override;

	//�����Ƿ�����Խ���
	bool bIncludeDiagonals;
	
};
