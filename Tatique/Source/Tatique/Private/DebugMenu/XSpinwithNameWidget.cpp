// Fill out your copyright notice in the Description page of Project Settings.


#include "DebugMenu/XSpinwithNameWidget.h"
#include "Components/SpinBox.h"
#include "Components/TextBlock.h"
//Debug
#include "Misc/DateTime.h"
#include "Internationalization/Internationalization.h"

void UXSpinwithNameWidget::NativeConstruct()
{
	// 获取当前时间
	FDateTime CurrentTime = FDateTime::Now();

	// 格式化时间为字符串
	FString CurrentTimeString = FDateTime::UtcNow().ToString(TEXT("%Y-%m-%d %H:%M:%S"));

	//Super::NativePreConstruct();
	bool check = TextBlock_Name && SpinBox_Value;
	if (!check) return;
	//UE_LOG(LogTemp, Warning, TEXT("The XSpinwithNameWidget, Current Time: %d"), count);
}

void UXSpinwithNameWidget::SetSpinBox()
{
	if (TextBlock_Name == nullptr || SpinBox_Value == nullptr) return;
	TextBlock_Name->SetText(Name);
	SpinBox_Value->SetMinSliderValue(MinSliderValue);
	SpinBox_Value->SetMaxSliderValue(MaxSliderValue);
	SpinBox_Value->SetMinValue(MinValue);
	SpinBox_Value->SetMaxValue(MaxValue);
	SpinBox_Value->SetValue(Value);
	SpinBox_Value->SetMinFractionalDigits(MinFractionalValue);
	SpinBox_Value->SetMaxFractionalDigits(MaxFractionalValue);
	SpinBox_Value->SetAlwaysUsesDeltaSnap(AlwaysUsesDeltaSnap);
	SpinBox_Value->SetDelta(Delta);
}

void UXSpinwithNameWidget::SteDefaultValue(const float dvalue)
{
	this->Value = dvalue;
}
