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

	//����springarm ��������������
	float Zoom_Desired;
	//��������ǰ���ƶ�������
	FVector Location_Desired;
	//�����ӽ���ת
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

	//����
	void Zoom(float value);
	//�ƶ�
	void MoveForward(float value);
	void MoveRight(float value);
	//��ת
	void RotationRight();
	void RotationLeft();
	//ѡ�񷽿�
	void ChooseGrid();
	void RemoveGrid();
	FIntPoint HoveredTile;
	void UpdateHoveredTile();

//����
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float LocationSpeed = 40.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float LocationInterp = 5.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float RotationSpeed = 45.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float RotationInterp = 5.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float ZoomSpeed = 20.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float ZoomInterp = 2.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float ZoomMin = 100.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float ZoomMax = 1500.0f;

	UPROPERTY(VisibleAnywhere)
		class AXGrid* GridIns;
};
