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

	// Called when the game end or when destroyed.
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UPROPERTY(BlueprintReadOnly)
	AGizmoBase* GizmoBase = nullptr;

	virtual void InitHandles();
	virtual void TransformSystem();
	virtual bool Transform_Check();
	virtual void Transform_World();
	virtual void Transform_Local();
	virtual void Transform_Track();

	UFUNCTION()
	virtual void OnClickedEvent(UPrimitiveComponent* TouchComponent, FKey PressedButton);

	virtual void BindDelegates();

public:	

	// Sets default values for this actor's properties.
	AGizmoMove();

	// Called every frame.
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	USceneComponent* Root = nullptr;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* Axis_X = nullptr;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* Axis_Y = nullptr;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* Axis_Z = nullptr;

	UFUNCTION(BlueprintCallable)
	virtual void SetArrowMesh(UStaticMesh* In_Mesh);

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UPrimitiveComponent* AxisComponent = nullptr;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	ESelectedAxis AxisEnum = ESelectedAxis::Null_Axis;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ExposeOnSpawn = "true"))
	bool bMoveLocal = true;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ExposeOnSpawn = "true"))
	float MoveMultiplier = 5;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ExposeOnSpawn = "true"))
	bool bEnableDebugMode = false;

};