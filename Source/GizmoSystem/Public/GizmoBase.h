// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "InputCoreTypes.h"

#include "GameFramework/Character.h"
#include "Components/CapsuleComponent.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

#include "GizmoBase.generated.h"

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

UCLASS()
class GIZMOSYSTEM_API AGizmoBase : public AActor
{
	GENERATED_BODY()
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Sets default values for this actor's properties
	AGizmoBase();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

// Callbacks.
public:

	virtual bool ForbiddenKeysCallback();
	virtual bool DetectMovementCallback();
	virtual bool IsGizmoInViewCallback();

// Player Variables.
public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UCapsuleComponent* CapsuleComponent;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	APlayerController* PlayerController;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	USceneComponent* PlayerCamera;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 PlayerIndex;

// Actor Components.
public:
	
	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UChildActorComponent* GizmoType;

// Actor Variables.
public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	USceneComponent* GizmoTarget;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 GizmoSizeMultiplier = 1150;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<FKey> ForbiddenKeys;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<FKey> PressedKeys;

};
