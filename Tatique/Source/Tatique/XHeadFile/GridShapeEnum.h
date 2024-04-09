#pragma once
UENUM(BlueprintType)
enum class EGridShapEnum : uint8
{
	EGS_None UMETA(DisplayName = "None"),
	EGS_Square UMETA(DisplayName = "Square"),
	EGS_Triangle UMETA(DisplayName = "Triangle"),
	EGS_Hexagon UMETA(DisplayName = "Hexagon"),
};

UENUM(BlueprintType)
enum class ETileType :uint8
{
	ETT_None UMETA(DisplayName = "None"),
	ETT_Normal UMETA(DisplayName = "Normal"),
	ETT_Obstacle UMETA(DisplayName = "Obstacle"),
};

UENUM(BlueprintType)
enum class ETileState :uint8
{
	ETT_None UMETA(DisplayName = "None"),
	ETT_Hovered UMETA(DisplayName = "Hovered"),
	ETT_Selected UMETA(DisplayName = "Selected"),
};