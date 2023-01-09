// Fill out your copyright notice in the Description page of Project Settings.


#include "GizmoMove.h"

// Sets default values
AGizmoMove::AGizmoMove()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGizmoMove::BeginPlay()
{	
	Super::BeginPlay();

	UWorld* CurrentWorld = GEngine->GetCurrentPlayWorld();
	this->CapsuleComponent = (UGameplayStatics::GetPlayerCharacter(CurrentWorld, PlayerIndex))->GetCapsuleComponent();
	this->PlayerController = UGameplayStatics::GetPlayerController(CurrentWorld, PlayerIndex);
}

// Called every frame
void AGizmoMove::Tick(float DeltaTime)
{
	USceneComponent* ParentRoot = nullptr;
	if (IsValid(this->GetParentActor()->GetRootComponent()))
	{
		ParentRoot = this->GetParentActor()->GetRootComponent();
	}
	
	// Movement Gizmo Size in World.
	double ScaleAxis = ((FVector::Distance(this->CapsuleComponent->GetComponentLocation(), this->GetRootComponent()->GetComponentLocation())) / ScaleMultiplier);
	ParentRoot->SetWorldScale3D(FVector3d(ScaleAxis, ScaleAxis, ScaleAxis));

	// Gizmo Condition.
	if (IsValid(GizmoTarget) == false || this->DetectMovementCallback() == false || this->IsGizmoInViewCallback() == false || this->ForbiddenKeysCallback() == true)
	{
		return;
	}

	// Local Space Movement.
	if (bMoveLocal == true)
	{
		// MAIN VARIABLES
		double Delta_X = 0;
		double Delta_Y = 0;
		this->PlayerController->GetInputMouseDelta(Delta_X, Delta_Y);

		// MAIN CALCULATIONS
		FVector AxisForward = AxisComponent->GetForwardVector();

		FVector NormalTarget = PlayerCamera->GetComponentLocation() - GizmoTarget->GetComponentLocation();
		FVector NormalizedVector = UKismetMathLibrary::Normal(FVector(NormalTarget.X, NormalTarget.Y, 0.0f), 0.0001);

		FVector CrossVector = UKismetMathLibrary::Cross_VectorVector(AxisForward, NormalizedVector);
		double DotProduct = UKismetMathLibrary::Dot_VectorVector(AxisForward, NormalizedVector);

		// X OFFSET
		double HorizontalMultiplier = 0;
		if (CrossVector.Z > 0 == true)
		{
			HorizontalMultiplier = Delta_X * 5;
		}

		else
		{
			HorizontalMultiplier = Delta_X * -5;
		}

		// Y OFFSET
		double VerticalMultiplier = 0;
		if (UKismetMathLibrary::Abs(AxisForward.Z) >= 0.75 == true)
		{
			if (AxisForward.Z >= 0 == true)
			{
				VerticalMultiplier = Delta_Y * 5;
			}

			else
			{
				VerticalMultiplier = Delta_Y * -5;
			}

		}

		else
		{
			if (DotProduct > 0 == true)
			{
				VerticalMultiplier = Delta_Y * -5;
			}

			else
			{
				VerticalMultiplier = Delta_Y * 5;
			}
		}

		FVector DeltaLocation = AxisForward * UKismetMathLibrary::Lerp(VerticalMultiplier, HorizontalMultiplier, UKismetMathLibrary::FClamp(UKismetMathLibrary::Abs(CrossVector.Z), 0, 1));
		GizmoTarget->AddWorldOffset(DeltaLocation, false, nullptr, ETeleportType::None);

		this->GetRootComponent()->SetWorldRotation(GizmoTarget->GetComponentRotation());
	}

	// World Space Movement.
	else
	{
		double ObjectDistance = UKismetMathLibrary::Vector_Distance(PlayerCamera->GetComponentLocation(), GizmoTarget->GetComponentLocation());

		FVector MouseWorldLocation;
		FVector MouseWorldDirection;
		PlayerController->DeprojectMousePositionToWorld(MouseWorldLocation, MouseWorldDirection);

		FVector NewLocation = MouseWorldLocation + (MouseWorldDirection * ObjectDistance);
		FVector OriginalLocation = GizmoTarget->GetComponentLocation();

		switch (AxisEnum)
		{
		case ESelectedAxis::Null_Axis:
			break;
		case ESelectedAxis::X_Axis:
			GizmoTarget->SetWorldLocation(FVector(NewLocation.X, GizmoTarget->GetComponentLocation().Y, GizmoTarget->GetComponentLocation().Z));
			this->GetRootComponent()->SetWorldRotation(FQuat(0.f), false, nullptr, ETeleportType::None);

			break;
		case ESelectedAxis::Y_Axis:
			GizmoTarget->SetWorldLocation(FVector(GizmoTarget->GetComponentLocation().X, NewLocation.Y, GizmoTarget->GetComponentLocation().Z));
			this->GetRootComponent()->SetWorldRotation(FQuat(0.f), false, nullptr, ETeleportType::None);

			break;
		case ESelectedAxis::Z_Axis:
			GizmoTarget->SetWorldLocation(FVector(GizmoTarget->GetComponentLocation().X, GizmoTarget->GetComponentLocation().Y, NewLocation.Z));
			this->GetRootComponent()->SetWorldRotation(FQuat(0.f), false, nullptr, ETeleportType::None);

			break;
		case ESelectedAxis::XY_Axis:
			break;
		case ESelectedAxis::XZ_Axis:
			break;
		case ESelectedAxis::YZ_Axis:
			break;
		case ESelectedAxis::XYZ_Axis:
			break;
		default:
			break;
		}
	}

	// Object Tracking for Gizmo.
	ParentRoot->SetWorldLocation(this->GizmoTarget->GetComponentLocation(), false, nullptr, ETeleportType::None);

	// Mouse Wheel Rotation.
	if (this->GetInputAxisKeyValue(EKeys::MouseWheelAxis) != 0)
	{
		if (this->IsGizmoInViewCallback() == true)
		{
			double RotationAxis = GetInputAxisKeyValue(EKeys::MouseWheelAxis) * RotateMultiplier;
			FRotator Rotation;
			/*
			switch (SelectedAxis)
			{
			case ESelectedAxis::X_Axis:
				Rotation.Roll = RotationAxis;
				UKismetMathLibrary::TransformRotation(this->GizmoTarget->GetComponentTransform(), Rotation);
				break;
			case ESelectedAxis::Y_Axis:
				Rotation.Pitch = RotationAxis;
				UKismetMathLibrary::TransformRotation(this->GizmoTarget->GetComponentTransform(), Rotation);
				break;
			case ESelectedAxis::Z_Axis:
				Rotation.Yaw = RotationAxis;
				UKismetMathLibrary::TransformRotation(this->GizmoTarget->GetComponentTransform(), Rotation);
				break;
			case ESelectedAxis::XY_Axis:
				break;
			case ESelectedAxis::XZ_Axis:
				break;
			case ESelectedAxis::YZ_Axis:
				break;
			case ESelectedAxis::XYZ_Axis:
				break;
			}
			*/
		}
	}
	
	Super::Tick(DeltaTime);	
}

bool AGizmoMove::ForbiddenKeysCallback()
{
	bool bForbiddenKeyPressed = false;
	
	for (int32 PressedKeyIndex = 0; PressedKeyIndex < PressedKeys.Num(); PressedKeyIndex++)
	{
		if (ForbiddenKeys.Contains(PressedKeys[PressedKeyIndex]))
		{
			bForbiddenKeyPressed = true;
			break;
		}
	}

	return bForbiddenKeyPressed;
}

bool AGizmoMove::DetectMovementCallback()
{
	double Delta_X;
	double Delta_Y;
	UGameplayStatics::GetPlayerController(GEngine->GetCurrentPlayWorld(), 0)->GetInputMouseDelta(Delta_X, Delta_Y);

	if (Delta_X || Delta_Y != 0)
	{
		return true;
	}

	else
	{
		return false;
	}
}

bool AGizmoMove::IsGizmoInViewCallback()
{
	if ((UKismetMathLibrary::Dot_VectorVector(PlayerCamera->GetForwardVector(), UKismetMathLibrary::Normal(GizmoTarget->GetComponentLocation() - PlayerCamera->GetComponentLocation(), 0.0001f))) > 0.5)
	{
		return true;
	}
	
	else
	{
		return false;
	}
}