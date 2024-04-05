// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "XLevelLoadActor.generated.h"

UCLASS()
class TATIQUE_API AXLevelLoadActor : public AActor
{
	GENERATED_BODY()
private:
	UPROPERTY(VisibleAnywhere, Category = MySceneComponent)
		class USceneComponent* DefaultSceneRoot;
	
public:	
	// Sets default values for this actor's properties
	AXLevelLoadActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Load Level
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString LevelLoaded;

	void LoadLevel(const FString& Level, bool bIsSame);

};
