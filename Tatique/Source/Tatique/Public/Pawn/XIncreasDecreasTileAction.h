// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pawn/XPlayerActions.h"
#include "XIncreasDecreasTileAction.generated.h"

/**
 * 
 */
UCLASS()
class TATIQUE_API AXIncreasDecreasTileAction : public AXPlayerActions
{
	GENERATED_BODY()
public:
	virtual void ExecuteAction(FIntPoint index);
	bool Increase;
};
