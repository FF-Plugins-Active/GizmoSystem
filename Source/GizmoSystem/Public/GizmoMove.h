// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputCoreTypes.h"
#include "Kismet/KismetMathLibrary.h"

#include "GameFramework/Actor.h"
#include "GameFramework/Character.h"

#include "Components/CapsuleComponent.h"
#include "Components/ArrowComponent.h"
#include "Kismet/GameplayStatics.h"

#include "GizmoMove.generated.h"


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
class GIZMOSYSTEM_API AGizmoMove : public AActor
{
	GENERATED_BODY()

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 ScaleMultiplier = 1150;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 RotateMultiplier = 5;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	APlayerController* PlayerController;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UPrimitiveComponent* AxisComponent;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	ESelectedAxis AxisEnum = ESelectedAxis::Null_Axis;

	virtual bool ForbiddenKeysCallback();
	virtual bool DetectMovementCallback();
	virtual bool IsGizmoInViewCallback();

public:	
	// Sets default values for this actor's properties
	AGizmoMove();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UCapsuleComponent* CapsuleComponent;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	USceneComponent* PlayerCamera;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	USceneComponent* GizmoTarget;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<FKey> ForbiddenKeys;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<FKey> PressedKeys;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 PlayerIndex;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bMoveLocal = false;

};