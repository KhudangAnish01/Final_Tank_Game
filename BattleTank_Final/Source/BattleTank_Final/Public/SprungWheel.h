// Fill out your copyright notice in the Description page of Project Settings.
//spawnchild
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

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void AddDrivingForce(float ForceForDrive);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	void SetupConstriant();

	//ufunction must compulsory cause it is dynamic delegate
	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	void ApplyForce();

	UPROPERTY(VisibleAnyWhere, Category = "Component")
		USphereComponent * Wheel = nullptr;

	UPROPERTY(VisibleAnyWhere, Category = "Component")
		UPhysicsConstraintComponent* MassWheelConstriant = nullptr;

	UPROPERTY(VisibleAnyWhere, Category = "Component")
		USphereComponent* Axle = nullptr;

	UPROPERTY(VisibleAnyWhere, Category = "Component")
		UPhysicsConstraintComponent* AxleWheelConstriant = nullptr;

	float TotalForceForDrive=0;
};
