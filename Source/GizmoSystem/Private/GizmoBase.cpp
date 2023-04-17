// Fill out your copyright notice in the Description page of Project Settings.

#include "GizmoBase.h"

// Sets default values
AGizmoBase::AGizmoBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"), false);
	RootComponent = Root;

	GizmoType = CreateDefaultSubobject<UChildActorComponent>(TEXT("GizmoType"), false);
	GizmoType->AttachToComponent(this->Root, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));
}

// Called when the game starts or when spawned
void AGizmoBase::BeginPlay()
{
	Super::BeginPlay();
	
	UWorld* CurrentWorld = GEngine->GetCurrentPlayWorld();
	
	if (IsValid(UGameplayStatics::GetPlayerCharacter(CurrentWorld, PlayerIndex)))
	{
		this->CapsuleComponent = UGameplayStatics::GetPlayerCharacter(CurrentWorld, PlayerIndex)->GetCapsuleComponent();
	}
	
	this->PlayerController = UGameplayStatics::GetPlayerController(CurrentWorld, PlayerIndex);
	EnableInput(this->PlayerController);
}

// Called every frame
void AGizmoBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Gizmo Size in World.
	if (IsValid(this->CapsuleComponent))
	{
		double ScaleAxis = ((FVector::Distance(this->CapsuleComponent->GetComponentLocation(), this->GetRootComponent()->GetComponentLocation())) / this->GizmoSizeMultiplier);

		if (IsValid(GizmoType->GetChildActor()))
		{
			GizmoType->GetChildActor()->GetRootComponent()->SetWorldScale3D(FVector3d(ScaleAxis, ScaleAxis, ScaleAxis));
		}
	}
}

bool AGizmoBase::ForbiddenKeysCallback()
{
	bool bForbiddenKeyPressed = false;

	for (int32 PressedKeyIndex = 0; PressedKeyIndex <PressedKeys.Num(); PressedKeyIndex++)
	{
		if (ForbiddenKeys.Contains(PressedKeys[PressedKeyIndex]))
		{
			bForbiddenKeyPressed = true;
			break;
		}
	}

	return bForbiddenKeyPressed;
}

bool AGizmoBase::DetectMovementCallback()
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

bool AGizmoBase::IsGizmoInViewCallback()
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