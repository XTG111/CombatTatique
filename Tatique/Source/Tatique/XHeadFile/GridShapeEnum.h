#pragma once
UENUM(BlueprintType)
enum class EGridShapEnum : uint8
{
	EGS_None UMETA(DisplayName = "None"),
	EGS_Square UMETA(DisplayName = "Square"),
	EGS_Triangle UMETA(DisplayName = "Triangle"),
	EGS_Hexagon UMETA(DisplayName = "Hexagon"),
};