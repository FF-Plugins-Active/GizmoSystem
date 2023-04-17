// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"

#include "InputCoreTypes.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

#include "GizmoSystemBPLibrary.generated.h"

UCLASS()
class UGizmoSystemBPLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Is Vectors Parallel", ToolTip = "See if two normal vectors are nearly parallel, meaning the angle between them is close to 0 degrees.", Keywords = "vector, math, parallel"), Category = "Math")
	static bool IsVectorsParallel(const FVector V1, const FVector V2, float ParallelCosineThreshold);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Is Vectors Coincident", ToolTip = "See if two normal vectors are coincident (nearly parallel and point in the same direction).", Keywords = "vector, math, coincident"), Category = "Math")
	static bool IsVectorsCoincident(const FVector V1, const FVector V2, float ParallelCosineThreshold);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Is Vectors Coincident", ToolTip = "See if two normal vectors are coincident (nearly parallel and point in the same direction).", Keywords = "vector, math, coincident"), Category = "Math")
	static void AddLocalRotWithQuat(USceneComponent* TargetObject, const FVector RotationAxis, float RotationAngle);

};