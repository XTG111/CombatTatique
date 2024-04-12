// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "XSelectorContorlActor.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnSelectionActionChange, class AXPlayerActions*, param1, AXPlayerActions*, param2);
UCLASS()
class TATIQUE_API AXSelectorContorlActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AXSelectorContorlActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
public:
	//选择方块
	void ChooseGrid();
	void RemoveGrid();
	//鼠标悬浮所在方块的位置
	FIntPoint HoveredTile;
	//鼠标点击所在方块的位置
	FIntPoint SelectedTile;
	void UpdateHoveredTile();
	void SetSelectedActions(TSubclassOf<class AXPlayerActions> LeftActionClass, TSubclassOf<AXPlayerActions> RightActionClass);
	UPROPERTY(VisibleAnywhere)
		AXPlayerActions* SelecetAction_LeftCheck;
	UPROPERTY(VisibleAnywhere)
		AXPlayerActions* SelecetAction_RightCheck;
	void setact(TSubclassOf<AXPlayerActions> LeftActionClass, TSubclassOf<AXPlayerActions> RightActionClass);
	UPROPERTY(VisibleAnywhere)
		FOnSelectionActionChange OnSelectionActionChange;

	UPROPERTY(VisibleAnywhere)
		class AXGrid* GridIns;
};
