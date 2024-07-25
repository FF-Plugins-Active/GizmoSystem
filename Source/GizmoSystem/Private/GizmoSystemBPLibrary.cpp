// Copyright Epic Games, Inc. All Rights Reserved.

#include "GizmoSystemBPLibrary.h"
#include "GizmoSystem.h"

#include "Math/Vector.h"

#include "BaseGizmos/GizmoActor.h"
#include "InteractiveGizmoManager.h"
#include "InteractiveToolsContext.h"


UGizmoSystemBPLibrary::UGizmoSystemBPLibrary(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{

}

bool UGizmoSystemBPLibrary::IsVectorsParallel(const FVector V1, const FVector V2, float ParallelCosineThreshold)
{
	FVector Normalized_V1 = UKismetMathLibrary::Normal(V1);
	FVector Normalized_V2 = UKismetMathLibrary::Normal(V2);

	return FVector::Parallel(Normalized_V1, Normalized_V2, ParallelCosineThreshold);
}

bool UGizmoSystemBPLibrary::IsVectorsCoincident(const FVector V1, const FVector V2, float ParallelCosineThreshold)
{
	FVector Normalized_V1 = UKismetMathLibrary::Normal(V1);
	FVector Normalized_V2 = UKismetMathLibrary::Normal(V2);

	return FVector::Coincident(Normalized_V1, Normalized_V2, ParallelCosineThreshold);
}

void UGizmoSystemBPLibrary::AddLocalRotWithQuat(USceneComponent* TargetObject, const FVector RotationAxis, float RotationAngle)
{
	TargetObject->AddLocalRotation(FQuat(RotationAxis, FMath::DegreesToRadians(RotationAngle)));
}