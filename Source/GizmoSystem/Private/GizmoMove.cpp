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

	GizmoBase = Cast<AGizmoBase>(this->GetParentActor());
	
	if (IsValid(GizmoBase))
	{
		EnableInput(this->GizmoBase->PlayerController);
	}
}

// Called every frame
void AGizmoMove::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MoveMultiplier = this->GetInputAxisKeyValue(EKeys::MouseWheelAxis) + MoveMultiplier;

	if (MoveMultiplier <= 0)
	{
		MoveMultiplier = 1;
	}

	if (IsValid(GizmoBase) == false)
	{
		return;
	}

	if (IsValid(this->GizmoBase->GizmoTarget) == false)
	{
		return;
	}
	
	if (this->GizmoBase->DetectMovementCallback() == false || this->GizmoBase->IsGizmoInViewCallback() == false || this->GizmoBase->ForbiddenKeysCallback() == true)
	{
		return;
	}

	// Local Space Movement.
	if (bMoveLocal == true)
	{
		if (IsValid(this->GizmoBase->PlayerCamera) == false)
		{
			return;
		}

		if (IsValid(AxisComponent) == false)
		{
			return;
		}

		this->GetRootComponent()->SetWorldRotation(this->GizmoBase->GizmoTarget->GetComponentRotation());
		
		// MAIN VARIABLES
		double Delta_X = 0;
		double Delta_Y = 0;
		this->GizmoBase->PlayerController->GetInputMouseDelta(Delta_X, Delta_Y);

		// MAIN CALCULATIONS
		FVector AxisForward = AxisComponent->GetForwardVector();
		FVector NormalTarget = this->GizmoBase->PlayerCamera->GetComponentLocation() - this->GizmoBase->GizmoTarget->GetComponentLocation();
		FVector NormalizedVector = UKismetMathLibrary::Normal(FVector(NormalTarget.X, NormalTarget.Y, 0.0f), 0.0001);
		FVector CrossVector = UKismetMathLibrary::Cross_VectorVector(AxisForward, NormalizedVector);
		double DotProduct = UKismetMathLibrary::Dot_VectorVector(AxisForward, NormalizedVector);

		// X OFFSET
		double HorizontalMultiplier = 0;
		if (CrossVector.Z > 0 == true)
		{
			HorizontalMultiplier = Delta_X * MoveMultiplier;
		}

		else
		{
			HorizontalMultiplier = Delta_X * MoveMultiplier * (-1);
		}

		// Y OFFSET
		double VerticalMultiplier = 0;
		if (UKismetMathLibrary::Abs(AxisForward.Z) >= 0.75 == true)
		{
			if (AxisForward.Z >= 0 == true)
			{
				VerticalMultiplier = Delta_Y * MoveMultiplier;
			}

			else
			{
				VerticalMultiplier = Delta_Y * MoveMultiplier * (-1);
			}

		}

		else
		{
			if (DotProduct > 0 == true)
			{
				VerticalMultiplier = Delta_Y * MoveMultiplier * (-1);
			}

			else
			{
				VerticalMultiplier = Delta_Y * MoveMultiplier;
			}
		}

		FVector DeltaLocation = AxisForward * UKismetMathLibrary::Lerp(VerticalMultiplier, HorizontalMultiplier, UKismetMathLibrary::FClamp(UKismetMathLibrary::Abs(CrossVector.Z), 0, 1));
		this->GizmoBase->GizmoTarget->AddWorldOffset(DeltaLocation, false, nullptr, ETeleportType::None);
	}

	// World Space Movement.
	else
	{
		this->GetRootComponent()->SetWorldRotation(FQuat(0.f), false, nullptr, ETeleportType::None);
		
		double ObjectDistance = UKismetMathLibrary::Vector_Distance(this->GizmoBase->PlayerCamera->GetComponentLocation(), this->GizmoBase->GizmoTarget->GetComponentLocation());

		FVector MouseWorldLocation;
		FVector MouseWorldDirection;
		this->GizmoBase->PlayerController->DeprojectMousePositionToWorld(MouseWorldLocation, MouseWorldDirection);

		FVector NewLocation = MouseWorldLocation + (MouseWorldDirection * ObjectDistance);
		FVector OriginalLocation = this->GizmoBase->GizmoTarget->GetComponentLocation();

		switch (AxisEnum)
		{
		case ESelectedAxis::Null_Axis:
			break;
		case ESelectedAxis::X_Axis:
			this->GizmoBase->GizmoTarget->SetWorldLocation(FVector(NewLocation.X, this->GizmoBase->GizmoTarget->GetComponentLocation().Y, this->GizmoBase->GizmoTarget->GetComponentLocation().Z));

			break;
		case ESelectedAxis::Y_Axis:
			this->GizmoBase->GizmoTarget->SetWorldLocation(FVector(this->GizmoBase->GizmoTarget->GetComponentLocation().X, NewLocation.Y, this->GizmoBase->GizmoTarget->GetComponentLocation().Z));

			break;
		case ESelectedAxis::Z_Axis:
			this->GizmoBase->GizmoTarget->SetWorldLocation(FVector(this->GizmoBase->GizmoTarget->GetComponentLocation().X, this->GizmoBase->GizmoTarget->GetComponentLocation().Y, NewLocation.Z));

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
	USceneComponent* ParentRoot = nullptr;
	if (IsValid(GizmoBase->GetRootComponent()))
	{
		ParentRoot = GizmoBase->GetRootComponent();
		ParentRoot->SetWorldLocation(this->GizmoBase->GizmoTarget->GetComponentLocation(), false, nullptr, ETeleportType::None);
	}	
}