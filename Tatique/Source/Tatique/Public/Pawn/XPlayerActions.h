// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "XPlayerActions.generated.h"

UCLASS()
class TATIQUE_API AXPlayerActions : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AXPlayerActions();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
public:
	virtual void ExecuteAction(FIntPoint index);

	UPROPERTY(EditInstanceOnly, Instanced, BlueprintReadWrite,meta = (ExposeOnSpawn = "true"))
		class AXSelectorContorlActor* PlayerAction;

};
