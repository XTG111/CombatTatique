// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pawn/XPlayerActions.h"
#include "XFindingPathToTargetAction.generated.h"

/**
 * 
 */
UCLASS()
class TATIQUE_API AXFindingPathToTargetAction : public AXPlayerActions
{
	GENERATED_BODY()
public:
	virtual void ExecuteAction(FIntPoint index) override;
	virtual void EndPlay(EEndPlayReason::Type EndPlayReason) override;
	UFUNCTION()
		void OnPathFindingCompleted(TArray<FIntPoint> Path);

	//控制是否包含对角线
	bool bIncludeDiagonals;
	float Delay;
};
