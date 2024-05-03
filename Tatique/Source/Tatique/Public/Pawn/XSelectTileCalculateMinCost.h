// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pawn/XPlayerActions.h"
#include "XSelectTileCalculateMinCost.generated.h"

/**
 * 
 */
UCLASS()
class TATIQUE_API AXSelectTileCalculateMinCost : public AXPlayerActions
{
	GENERATED_BODY()
public:
	virtual void ExecuteAction(FIntPoint index) override;

	//�����Ƿ�����Խ���
	bool bIncludeDiagonals;
	
};
