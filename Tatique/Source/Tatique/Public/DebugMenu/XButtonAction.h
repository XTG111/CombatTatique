// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "XButtonAction.generated.h"

/**
 * 
 */
UCLASS()
class TATIQUE_API UXButtonAction : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
	UFUNCTION()
		void SetActions();

public:
	UPROPERTY(meta = (BindWidget))
		class UButton* Button_Actions;
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* TextBlock_Actions;
	UPROPERTY(VisibleAnywhere)
		class AXSelectorContorlActor* PlayerActions;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<AXPlayerActions> LeftAction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<AXPlayerActions> RightAction;

public:
	UFUNCTION()
		void OnSelectedActionsChanged(class AXPlayerActions* leftclickaction, AXPlayerActions* rightclickaction);
};
