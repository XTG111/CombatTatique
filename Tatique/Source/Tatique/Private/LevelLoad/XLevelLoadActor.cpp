// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelLoad/XLevelLoadActor.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/LevelStreaming.h"

// Sets default values
AXLevelLoadActor::AXLevelLoadActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("MyRootComponent"));
	RootComponent = DefaultSceneRoot;

}

// Called when the game starts or when spawned
void AXLevelLoadActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AXLevelLoadActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AXLevelLoadActor::LoadLevel(const FString& Level, bool bIsSame)
{
	bool check = (Level != LevelLoaded) || bIsSame;
	if (!check) return;
	FName curLevel = FName(*LevelLoaded);
	auto LoadedLevel = UGameplayStatics::GetStreamingLevel(this, curLevel);
	if (LoadedLevel)
	{
		LoadedLevel->SetShouldBeLoaded(false);
		LoadedLevel->SetShouldBeVisible(false);
	}
	LevelLoaded = Level;
	curLevel = FName(*Level);
	LoadedLevel = UGameplayStatics::GetStreamingLevel(this, curLevel);
	if (LoadedLevel)
	{
		LoadedLevel->SetShouldBeLoaded(true);
		LoadedLevel->SetShouldBeVisible(true);
	}
}

