// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "XPawn.generated.h"

UCLASS()
class TATIQUE_API AXPawn : public APawn
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere, Category = MySceneComponent)
		class USceneComponent* DefaultSceneRoot;

	UPROPERTY(VisibleAnywhere, Category = Camera)
		class USpringArmComponent* SpringArmComp;

	UPROPERTY(VisibleAnywhere, Category = Camera)
		class UCameraComponent* CameraComp;

	//控制springarm 长度来控制缩放
	float Zoom_Desired;
	//控制左右前后移动的向量
	FVector Location_Desired;
	//控制视角旋转
	FRotator Rotation_Desired;

public:
	// Sets default values for this pawn's properties
	AXPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//缩放
	void Zoom(float value);
	//移动
	void MoveForward(float value);
	void MoveRight(float value);
	//旋转
	void RotationRight();
	void RotationLeft();
};
