#pragma once
UENUM(BlueprintType)
enum class EGridShapEnum : uint8
{
	EGS_Squard UMETA(DisplayName = "Square"),
	EGS_Triangle UMETA(DisplayName = "Triangle"),
	EGS_Hexagon UMETA(DisplayName = "Hexagon"),

	EGS_None UMETA(DisplayName = "None"),
};