// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawn/XPawn.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/KismetMathLibrary.h"

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
}

// Called every frame
void AXPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//��ֵƽ��
	SpringArmComp->TargetArmLength = UKismetMathLibrary::FInterpTo(SpringArmComp->TargetArmLength, Zoom_Desired, DeltaTime, 2.0f);
	
	FVector TargetLoc = UKismetMathLibrary::VInterpTo(GetActorLocation(), Location_Desired, DeltaTime, 5.0f);
	SetActorLocation(TargetLoc);

	FRotator TargetRot = UKismetMathLibrary::RInterpTo(GetActorRotation(), Rotation_Desired, DeltaTime, 5.0f);
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

}

void AXPawn::Zoom(float value)
{
	float temp = -20.0f * value;
	Zoom_Desired += temp;
	Zoom_Desired = UKismetMathLibrary::Clamp(Zoom_Desired, 100.0f, 1500.0f);
}

void AXPawn::MoveForward(float value)
{
	FVector temp = GetActorForwardVector() * value * 20.0;
	Location_Desired += temp;
}

void AXPawn::MoveRight(float value)
{
	FVector temp = GetActorRightVector() * value * 20.0;
	Location_Desired += temp;
}

void AXPawn::RotationRight()
{
	FRotator temp = UKismetMathLibrary::MakeRotator(0.0f, 0.0f, -45.0f);
	Rotation_Desired += temp;
}

void AXPawn::RotationLeft()
{
	FRotator temp = UKismetMathLibrary::MakeRotator(0.0f, 0.0f, 45.0f);
	Rotation_Desired += temp;
}

