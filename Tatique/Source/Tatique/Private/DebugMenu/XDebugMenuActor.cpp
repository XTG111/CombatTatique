// Fill out your copyright notice in the Description page of Project Settings.


#include "DebugMenu/XDebugMenuActor.h"
#include "Kismet/GameplayStatics.h"
#include "DebugMenu/XDebugMenuWidget.h"
#include "DebugMenu/XCameraDebugWidget.h"
#include "DebugMenu/XSpinwithNameWidget.h"

// Sets default values
AXDebugMenuActor::AXDebugMenuActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AXDebugMenuActor::BeginPlay()
{
	Super::BeginPlay();
	//Create Widget
	XDebugMenu = CreateWidget<UXDebugMenuWidget>(GetWorld(), DebugMenuWdgClass);
	if (XDebugMenu)
	{
		XDebugMenu->AddToViewport();
	}
}

// Called every frame
void AXDebugMenuActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

