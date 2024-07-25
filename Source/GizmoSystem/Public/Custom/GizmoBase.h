// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Gizmo_Includes.h"
#include "Gizmo_Enums.h"

#include "GizmoBase.generated.h"

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
	UCapsuleComponent* CapsuleComponent = nullptr;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	APlayerController* PlayerController = nullptr;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	USceneComponent* PlayerCamera = nullptr;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 PlayerIndex = 0;

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
