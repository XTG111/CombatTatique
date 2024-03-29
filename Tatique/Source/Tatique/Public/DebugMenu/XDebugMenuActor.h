// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DebugMenu/XDebugMenuWidget.h"
#include "XDebugMenuActor.generated.h"

UCLASS()
class TATIQUE_API AXDebugMenuActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AXDebugMenuActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY()
		class UXDebugMenuWidget* XDebugMenu;

	UPROPERTY(EditAnywhere, Category = "Debug")
		TSubclassOf<class UUserWidget> DebugMenuWdgClass;


};
