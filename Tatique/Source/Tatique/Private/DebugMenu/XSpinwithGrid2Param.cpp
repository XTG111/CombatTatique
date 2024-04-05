// Fill out your copyright notice in the Description page of Project Settings.


#include "DebugMenu/XSpinwithGrid2Param.h"
#include "Components/SpinBox.h"
#include "Components/TextBlock.h"

void UXSpinwithGrid2Param::NativeConstruct()
{
	bool check = TextBlock_Name && SpinBox_Value_X && SpinBox_Value_Y;
	if (!check) return;
	SpinBoxList.Add(SpinBox_Value_X);
	SpinBoxList.Add(SpinBox_Value_Y);

	SpinBox_Value_X->OnValueChanged.AddDynamic(this, &UXSpinwithGrid2Param::SelfOnValueChange);
	SpinBox_Value_Y->OnValueChanged.AddDynamic(this, &UXSpinwithGrid2Param::SelfOnValueChange);
}

void UXSpinwithGrid2Param::SetSpinBox()
{
	if (TextBlock_Name == nullptr || SpinBox_Value_X == nullptr || SpinBox_Value_Y == nullptr) return;
	TextBlock_Name->SetText(Name);
	SpinBox_Value_X->SetValue(Value.X);
	SpinBox_Value_Y->SetValue(Value.Y);
	for (auto spinbox : SpinBoxList)
	{
		spinbox->SetMinSliderValue(SliderValue.X);
		spinbox->SetMaxSliderValue(SliderValue.Y);
		spinbox->SetMinValue(ValueBor.X);
		spinbox->SetMaxValue(ValueBor.Y);
		spinbox->SetMinFractionalDigits(FractionalDigits.X);
		spinbox->SetMaxFractionalDigits(FractionalDigits.Y);
		spinbox->SetAlwaysUsesDeltaSnap(AlwaysDeltaSnap);
		spinbox->SetDelta(Delta);
	}
}

void UXSpinwithGrid2Param::SelfOnValueChange(float chvalue)
{
	this->Value.X = SpinBox_Value_X->GetValue();
	this->Value.Y = SpinBox_Value_Y->GetValue();
	MyOnValueChange.Broadcast(this->Value);
}

void UXSpinwithGrid2Param::SetDefauleValue(const FVector2D& dvalue)
{
	this->Value = dvalue;
}
