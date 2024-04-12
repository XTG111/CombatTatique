// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawn/XSelectorContorlActor.h"
#include "SpawnGrid/XGrid.h"
#include "Kismet/GameplayStatics.h"
#include "Pawn/XPlayerActions.h"
#include "Pawn/XChildPlayerActions.h"

// Sets default values
AXSelectorContorlActor::AXSelectorContorlActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AXSelectorContorlActor::BeginPlay()
{
	Super::BeginPlay();
	GridIns = Cast<AXGrid>(UGameplayStatics::GetActorOfClass(GetWorld(), AXGrid::StaticClass()));
	//EnableInput(UGameplayStatics::GetPlayerController(GetWorld(),0));
}

// Called every frame
void AXSelectorContorlActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UpdateHoveredTile();

}

void AXSelectorContorlActor::ChooseGrid()
{
	if (!GridIns) return;
	UE_LOG(LogTemp, Warning, TEXT("Left"));
	//GridIns->AddStateToTile(HoveredTile, ETileState::ETT_Selected);
	UpdateHoveredTile();
	if (SelecetAction_LeftCheck)
	{
		SelecetAction_LeftCheck->ExecuteAction(HoveredTile);
	}
}

void AXSelectorContorlActor::RemoveGrid()
{
	if (!GridIns) return;
	UE_LOG(LogTemp, Warning, TEXT("Right"));
	//GridIns->RemoveStateFromTile(HoveredTile, ETileState::ETT_Selected);
	UpdateHoveredTile();
	if (SelecetAction_RightCheck)
	{
		SelecetAction_RightCheck->ExecuteAction(HoveredTile);
	}
}

void AXSelectorContorlActor::UpdateHoveredTile()
{
	if (!GridIns)
	{
		UE_LOG(LogTemp, Warning, TEXT("No GridIns!!!!!!!"));
		return;
	}
	FIntPoint index = GridIns->GetTileIndexUnderCursor(0);
	if (index != HoveredTile)
	{
		GridIns->RemoveStateFromTile(HoveredTile, ETileState::ETT_Hovered);
		HoveredTile = index;
		GridIns->AddStateToTile(HoveredTile, ETileState::ETT_Hovered);
	}
}

void AXSelectorContorlActor::SetSelectedActions(TSubclassOf<class AXPlayerActions> LeftActionClass, TSubclassOf<AXPlayerActions> RightActionClass)
{
	setact(LeftActionClass, RightActionClass);
	OnSelectionActionChange.Broadcast(SelecetAction_LeftCheck, SelecetAction_RightCheck);
}

void AXSelectorContorlActor::setact(TSubclassOf<AXPlayerActions> LeftActionClass, TSubclassOf<AXPlayerActions> RightActionClass)
{
	if (SelecetAction_LeftCheck)
	{
		SelecetAction_LeftCheck->Destroy();
		SelecetAction_LeftCheck = nullptr;
	}
	if (UKismetSystemLibrary::IsValidClass(LeftActionClass))
	{
		FVector loc = { 0.0f,0.0f,0.0f };
		FRotator rot = { 0.0f,0.0f,0.0f };
		FVector scal = { 1.0f,1.0f,1.0f };
		FTransform trans;
		trans.SetLocation(loc);
		trans.SetRotation(FQuat(rot));
		trans.SetScale3D(scal);
		FActorSpawnParameters SpawnParameters;
		SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		SelecetAction_LeftCheck = GetWorld()->SpawnActor<AXChildPlayerActions>(LeftActionClass, trans, SpawnParameters);
	}

	if (SelecetAction_RightCheck)
	{
		SelecetAction_RightCheck->Destroy();
		SelecetAction_RightCheck = nullptr;
	}
	if (UKismetSystemLibrary::IsValidClass(RightActionClass))
	{
		FVector loc = { 0.0f,0.0f,0.0f };
		FRotator rot = { 0.0f,0.0f,0.0f };
		FVector scal = { 1.0f,1.0f,1.0f };
		FTransform trans;
		trans.SetLocation(loc);
		trans.SetRotation(FQuat(rot));
		trans.SetScale3D(scal);
		FActorSpawnParameters SpawnParameters;
		SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		SelecetAction_RightCheck = GetWorld()->SpawnActor<AXChildPlayerActions>(RightActionClass, trans, SpawnParameters);
	}
}

