// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "GizmoBase.h"

// Exprimental
#include "BaseGizmos/CombinedTransformGizmo.h"

#include "GizmoRotate.generated.h"

UCLASS()
class GIZMOSYSTEM_API AGizmoRotate : public AActor
{
	GENERATED_BODY()
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly)
	AGizmoBase* GizmoBase;

public:	

	// Sets default values for this actor's properties
	AGizmoRotate();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UPrimitiveComponent* AxisComponent;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	ESelectedAxis AxisEnum = ESelectedAxis::Null_Axis;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bRotateLocal = true;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float RotateMultiplier = 5;

	UPROPERTY()
	UCombinedTransformGizmo* TransformGizmo;

	//UFUNCTION(BlueprintCallable, meta = (DisplayName = "Exprimental - Enable Transform Gizmo", Description = "Exprimental", Keywords = "enable, combined, transform, gizmo, pivot"), Category = "Gizmo")
	virtual void EnableTransformGizmo();
};
