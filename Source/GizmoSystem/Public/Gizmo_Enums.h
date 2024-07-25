#pragma once

UENUM(BlueprintType)
enum class ESelectedAxis : uint8
{
	Null_Axis	UMETA(DisplayName = "Null Axis"),
	X_Axis		UMETA(DisplayName = "X Axis"),
	Y_Axis		UMETA(DisplayName = "Y Axis"),
	Z_Axis		UMETA(DisplayName = "Z Axis"),
	XY_Axis		UMETA(DisplayName = "XY Axis"),
	XZ_Axis		UMETA(DisplayName = "XZ Axis"),
	YZ_Axis		UMETA(DisplayName = "YZ Axis"),
	XYZ_Axis	UMETA(DisplayName = "XYZ Axis"),
};
ENUM_CLASS_FLAGS(ESelectedAxis)