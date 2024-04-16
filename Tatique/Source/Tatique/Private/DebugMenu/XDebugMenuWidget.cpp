// Fill out your copyright notice in the Description page of Project Settings.


#include "DebugMenu/XDebugMenuWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Kismet/KismetMathLibrary.h"
#include "DebugMenu/X_TAB_ConsoleCommandWidget.h"
#include "DebugMenu/XCameraDebugWidget.h"

void UXDebugMenuWidget::NativeConstruct()
{

	Button_Tab1->SetBackgroundColor(FLinearColor::Black);
	Button_Tab2->SetBackgroundColor(FLinearColor::Black);
	Button_Tab3->SetBackgroundColor(FLinearColor::Black);
	Button_Tab4->SetBackgroundColor(FLinearColor::Black);
	TextBlock_Tab1->SetText(FText::FromString("Command"));
	TextBlock_Tab2->SetText(FText::FromString("Camera"));
	TextBlock_Tab3->SetText(FText::FromString("Grid"));
	TextBlock_Tab4->SetText(FText::FromString("PathFinding"));
	//UE_LOG(LogTemp, Warning, TEXT("The XDebugMenuWidget"));

	if (Button_Tab1)
	{
		Button_Tab1->OnClicked.AddDynamic(this, &UXDebugMenuWidget::SetChoose1);
	}
	if (Button_Tab2)
	{
		Button_Tab2->OnClicked.AddDynamic(this, &UXDebugMenuWidget::SetChoose2);
	}
	if (Button_Tab3)
	{
		Button_Tab3->OnClicked.AddDynamic(this, &UXDebugMenuWidget::SetChoose3);
	}
	if (Button_Tab4)
	{
		Button_Tab4->OnClicked.AddDynamic(this, &UXDebugMenuWidget::SetChoose4);
	}
}

void UXDebugMenuWidget::SetChoose1()
{
	bool check = Button_Tab1!=nullptr && Button_Tab2!=nullptr && Button_Tab3!=nullptr && Button_Tab4 != nullptr && WidgetSwitcher_TabContent!=nullptr;
	if (!check) return;
	int ActiveWidgetIndex = WidgetSwitcher_TabContent->ActiveWidgetIndex;
	
	if (ActiveWidgetIndex == 1)
	{
		WidgetSwitcher_TabContent->SetActiveWidgetIndex(0);
	}
	else
	{
		WidgetSwitcher_TabContent->SetActiveWidgetIndex(1);
	}

	bool PickA = (ActiveWidgetIndex == 1);
	BackgroudColor = UKismetMathLibrary::SelectColor(FLinearColor::Black, FLinearColor::Blue, PickA);
	BackgroundColorOther = FLinearColor::Black;
	Button_Tab1->SetBackgroundColor(BackgroudColor);
	Button_Tab2->SetBackgroundColor(BackgroundColorOther);
	Button_Tab3->SetBackgroundColor(BackgroundColorOther);
	Button_Tab4->SetBackgroundColor(BackgroundColorOther);
}

void UXDebugMenuWidget::SetChoose2()
{
	bool check = Button_Tab1 != nullptr && Button_Tab2 != nullptr && Button_Tab3 != nullptr && Button_Tab4 != nullptr && WidgetSwitcher_TabContent != nullptr;
	if (!check) return;
	int ActiveWidgetIndex = WidgetSwitcher_TabContent->ActiveWidgetIndex;

	if (ActiveWidgetIndex == 2)
	{
		WidgetSwitcher_TabContent->SetActiveWidgetIndex(0);
	}
	else
	{
		WidgetSwitcher_TabContent->SetActiveWidgetIndex(2);
	}

	bool PickA = (ActiveWidgetIndex == 2);
	BackgroudColor = UKismetMathLibrary::SelectColor(FLinearColor::Black, FLinearColor::Blue, PickA);
	BackgroundColorOther = FLinearColor::Black;
	Button_Tab2->SetBackgroundColor(BackgroudColor);
	Button_Tab1->SetBackgroundColor(BackgroundColorOther);
	Button_Tab3->SetBackgroundColor(BackgroundColorOther);
	Button_Tab4->SetBackgroundColor(BackgroundColorOther);
}

void UXDebugMenuWidget::SetChoose3()
{
	bool check = Button_Tab1 != nullptr && Button_Tab2 != nullptr && Button_Tab3 != nullptr && Button_Tab4 != nullptr && WidgetSwitcher_TabContent != nullptr;
	if (!check) return;
	int ActiveWidgetIndex = WidgetSwitcher_TabContent->ActiveWidgetIndex;

	if (ActiveWidgetIndex == 3)
	{
		WidgetSwitcher_TabContent->SetActiveWidgetIndex(0);
	}
	else
	{
		WidgetSwitcher_TabContent->SetActiveWidgetIndex(3);
	}

	bool PickA = (ActiveWidgetIndex == 3);
	BackgroudColor = UKismetMathLibrary::SelectColor(FLinearColor::Black, FLinearColor::Blue, PickA);
	BackgroundColorOther = FLinearColor::Black;
	Button_Tab3->SetBackgroundColor(BackgroudColor);
	Button_Tab1->SetBackgroundColor(BackgroundColorOther);
	Button_Tab2->SetBackgroundColor(BackgroundColorOther);
	Button_Tab4->SetBackgroundColor(BackgroundColorOther);
}

void UXDebugMenuWidget::SetChoose4()
{
	bool check = Button_Tab1 != nullptr && Button_Tab2 != nullptr && Button_Tab3 != nullptr && Button_Tab4 != nullptr && WidgetSwitcher_TabContent != nullptr;
	if (!check) return;
	int ActiveWidgetIndex = WidgetSwitcher_TabContent->ActiveWidgetIndex;

	if (ActiveWidgetIndex == 4)
	{
		WidgetSwitcher_TabContent->SetActiveWidgetIndex(0);
	}
	else
	{
		WidgetSwitcher_TabContent->SetActiveWidgetIndex(4);
	}

	bool PickA = (ActiveWidgetIndex == 4);
	BackgroudColor = UKismetMathLibrary::SelectColor(FLinearColor::Black, FLinearColor::Blue, PickA);
	BackgroundColorOther = FLinearColor::Black;
	Button_Tab4->SetBackgroundColor(BackgroudColor);
	Button_Tab1->SetBackgroundColor(BackgroundColorOther);
	Button_Tab2->SetBackgroundColor(BackgroundColorOther);
	Button_Tab3->SetBackgroundColor(BackgroundColorOther);
}
