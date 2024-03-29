// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "GizmoBase.h"

#include "GizmoMove.generated.h"

UCLASS()
class GIZMOSYSTEM_API AGizmoMove : public AActor
{
	GENERATED_BODY()

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly)
	AGizmoBase* GizmoBase;

public:	
	// Sets default values for this actor's properties
	AGizmoMove();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UPrimitiveComponent* AxisComponent;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	ESelectedAxis AxisEnum = ESelectedAxis::Null_Axis;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bMoveLocal = true;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float MoveMultiplier = 5;

};