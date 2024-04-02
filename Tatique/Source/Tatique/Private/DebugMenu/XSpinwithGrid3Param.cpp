// Fill out your copyright notice in the Description page of Project Settings.


#include "DebugMenu/XSpinwithGrid3Param.h"
#include "Components/SpinBox.h"
#include "Components/TextBlock.h"

void UXSpinwithGrid3Param::NativeConstruct()
{
	bool check = TextBlock_Name && SpinBox_Value_X && SpinBox_Value_Y && SpinBox_Value_Z;
	if (!check) return;
	SpinBoxList.Add(SpinBox_Value_X);
	SpinBoxList.Add(SpinBox_Value_Y);
	SpinBoxList.Add(SpinBox_Value_Z);

	SpinBox_Value_X->OnValueChanged.AddDynamic(this, &UXSpinwithGrid3Param::SelfOnValueChange);
	SpinBox_Value_Y->OnValueChanged.AddDynamic(this, &UXSpinwithGrid3Param::SelfOnValueChange);
	SpinBox_Value_Z->OnValueChanged.AddDynamic(this, &UXSpinwithGrid3Param::SelfOnValueChange);
}

void UXSpinwithGrid3Param::SetSpinBox()
{
	if (TextBlock_Name == nullptr || SpinBox_Value_X == nullptr || SpinBox_Value_Y == nullptr) return;
	TextBlock_Name->SetText(Name);
	SpinBox_Value_X->SetValue(Value.X);
	SpinBox_Value_Y->SetValue(Value.Y);
	SpinBox_Value_Z->SetValue(Value.Z);
	UE_LOG(LogTemp, Warning, TEXT("TileSize,%f,%f,%f"), Value.X, Value.Y, Value.Z);
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
	//UE_LOG(LogTemp, Warning, TEXT("No GridIns!!!!!!!"));
}

void UXSpinwithGrid3Param::SelfOnValueChange(float chvalue)
{
	this->Value.X = SpinBox_Value_X->GetValue();
	this->Value.Y = SpinBox_Value_Y->GetValue();
	this->Value.Z = SpinBox_Value_Z->GetValue();
	MyOnValueChange.Broadcast(this->Value);
}
