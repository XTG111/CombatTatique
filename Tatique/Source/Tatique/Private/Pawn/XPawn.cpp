// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawn/XPawn.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Pawn/XSelectorContorlActor.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AXPawn::AXPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("MyRootComponent"));
	RootComponent = DefaultSceneRoot;
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	SpringArmComp->SetupAttachment(RootComponent);
	SpringArmComp->TargetArmLength = 700.0f;

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComp->SetupAttachment(SpringArmComp);
}

// Called when the game starts or when spawned
void AXPawn::BeginPlay()
{
	Super::BeginPlay();
	Location_Desired = GetActorLocation();
	Zoom_Desired = SpringArmComp->TargetArmLength;
	Rotation_Desired = GetActorRotation();

	SelectorContorlActorIns = Cast<AXSelectorContorlActor>(UGameplayStatics::GetActorOfClass(GetWorld(), AXSelectorContorlActor::StaticClass()));
	//EnableInput(UGameplayStatics::GetPlayerController(GetWorld(),0));
}

// Called every frame
void AXPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//²åÖµÆ½»¬
	SpringArmComp->TargetArmLength = UKismetMathLibrary::FInterpTo(SpringArmComp->TargetArmLength, Zoom_Desired, DeltaTime, ZoomInterp);
	
	FVector TargetLoc = UKismetMathLibrary::VInterpTo(GetActorLocation(), Location_Desired, DeltaTime, LocationInterp);
	SetActorLocation(TargetLoc);

	FRotator TargetRot = UKismetMathLibrary::RInterpTo(GetActorRotation(), Rotation_Desired, DeltaTime, RotationInterp);
	SetActorRotation(TargetRot);

}

// Called to bind functionality to input
void AXPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("Zoom", this, &AXPawn::Zoom);
	PlayerInputComponent->BindAxis("MoveForward", this, &AXPawn::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AXPawn::MoveRight);

	PlayerInputComponent->BindAction("RotationRight", IE_Pressed, this, &AXPawn::RotationRight);
	PlayerInputComponent->BindAction("RotationLeft", IE_Pressed, this, &AXPawn::RotationLeft);
	PlayerInputComponent->BindAction("CheckGrid", IE_Pressed, this, &AXPawn::ChooseGrid);
	PlayerInputComponent->BindAction("CheckGrid", IE_Released, this, &AXPawn::ReleasedLeft);
	PlayerInputComponent->BindAction("UnCheckGrid", IE_Pressed, this, &AXPawn::RemoveGrid);
	PlayerInputComponent->BindAction("UnCheckGrid", IE_Released, this, &AXPawn::ReleasedRight);

}

void AXPawn::Zoom(float value)
{
	float temp = -1.0f * ZoomSpeed * value;
	Zoom_Desired += temp;
	Zoom_Desired = UKismetMathLibrary::Clamp(Zoom_Desired, ZoomMin, ZoomMax);
}

void AXPawn::MoveForward(float value)
{
	FVector temp = GetActorForwardVector() * value * LocationSpeed;
	Location_Desired += temp;
}

void AXPawn::MoveRight(float value)
{
	FVector temp = GetActorRightVector() * value * RotationSpeed;
	Location_Desired += temp;
}

void AXPawn::RotationRight()
{
	FRotator temp = UKismetMathLibrary::MakeRotator(0.0f, 0.0f, -1.0f*RotationSpeed);
	Rotation_Desired += temp;
}

void AXPawn::RotationLeft()
{
	FRotator temp = UKismetMathLibrary::MakeRotator(0.0f, 0.0f, RotationSpeed);
	Rotation_Desired += temp;
}

void AXPawn::ChooseGrid()
{
	SelectorContorlActorIns->ChooseGrid();
}

void AXPawn::ReleasedLeft()
{
	SelectorContorlActorIns->IsLeftClickDown = false;
}

void AXPawn::RemoveGrid()
{
	SelectorContorlActorIns->RemoveGrid();
}

void AXPawn::ReleasedRight()
{
	SelectorContorlActorIns->IsRightClickDown = false;
}



