// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "PhysicsEngine/PhysicsConstraintComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SprungWheel.generated.h"

class USphereComponent;

UCLASS()
class BATTLETANK_FINAL_API ASprungWheel : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASprungWheel();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	void SetupConstriant();

	UPROPERTY(VisibleAnyWhere, Category = "Component")
		USphereComponent * Wheel = nullptr;

	UPROPERTY(VisibleAnyWhere, Category = "Component")
		UPhysicsConstraintComponent* MassWheelConstriant = nullptr;

	UPROPERTY(VisibleAnyWhere, Category = "Component")
		USphereComponent* Axle = nullptr;

	UPROPERTY(VisibleAnyWhere, Category = "Component")
		UPhysicsConstraintComponent* AxleWheelConstriant = nullptr;

};
