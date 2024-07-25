// Fill out your copyright notice in the Description page of Project Settings.

#include "Custom/GizmoRotate.h"

AGizmoRotate::AGizmoRotate()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void AGizmoRotate::BeginPlay()
{
	Super::BeginPlay();
	
	GizmoBase = Cast<AGizmoBase>(this->GetParentActor());

	if (IsValid(GizmoBase))
	{
		EnableInput(this->GizmoBase->PlayerController);
	}
}

void AGizmoRotate::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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

	RotateMultiplier += this->GetInputAxisKeyValue(EKeys::MouseWheelAxis);

	if (RotateMultiplier <= 0)
	{
		RotateMultiplier = 1;
	}

	if (bRotateLocal == true)
	{

	}

	else
	{

	}
}