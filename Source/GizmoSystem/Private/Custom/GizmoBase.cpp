// Fill out your copyright notice in the Description page of Project Settings.

#include "Custom/GizmoBase.h"

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
	ACharacter* Character = UGameplayStatics::GetPlayerCharacter(CurrentWorld, PlayerIndex);

	this->PlayerController = UGameplayStatics::GetPlayerController(CurrentWorld, PlayerIndex);
	this->CapsuleComponent = Character->GetCapsuleComponent();

	if (Character->GetComponentsByTag(USceneComponent::StaticClass(), FName("camera")).Num() > 0)
	{
		this->PlayerCamera = Cast<USceneComponent>(Character->GetComponentsByTag(USceneComponent::StaticClass(), FName("camera"))[0]);
		EnableInput(this->PlayerController);
	}

	else
	{
		UE_LOG(LogTemp, Warning, TEXT("You need to define camera and enable input manually."))
	}
}

// Called every frame
void AGizmoBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Gizmo Size in World.
	if (IsValid(this->CapsuleComponent) && IsValid(GizmoType->GetChildActor()))
	{
		double ScaleAxis = ((FVector::Distance(this->CapsuleComponent->GetComponentLocation(), this->GetRootComponent()->GetComponentLocation())) / this->GizmoSizeMultiplier);
		GizmoType->GetChildActor()->GetRootComponent()->SetWorldScale3D(FVector3d(ScaleAxis, ScaleAxis, ScaleAxis));
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
	this->PlayerController->GetInputMouseDelta(Delta_X, Delta_Y);

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
	if (!IsValid(PlayerCamera) || !IsValid(GizmoTarget) || !((UKismetMathLibrary::Dot_VectorVector(PlayerCamera->GetForwardVector(), UKismetMathLibrary::Normal(GizmoTarget->GetComponentLocation() - PlayerCamera->GetComponentLocation(), 0.0001f))) > 0.5))
	{
		return false;
	}

	else
	{
		return true;
	}
}