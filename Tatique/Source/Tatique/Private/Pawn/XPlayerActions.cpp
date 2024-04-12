// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawn/XPlayerActions.h"

// Sets default values
AXPlayerActions::AXPlayerActions()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AXPlayerActions::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AXPlayerActions::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AXPlayerActions::ExecuteAction(FIntPoint index)
{
}

