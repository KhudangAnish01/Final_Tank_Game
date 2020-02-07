// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"
class ATank;

/**
 * 
 */
UCLASS()
class BATTLETANK_FINAL_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Gets the name of Tank actor possessed by the Player
	ATank* GetTankControlled();

	//Tank Fire if Aim is Ready
	void AimTowardsCrossHair();

	//returns Outparameter , If it true i.e hit on landscape
	bool GetSightRayHitLocation(FVector& HitLocation) const;

	//Corss Hair Position
	UPROPERTY(EditDefaultsOnly)
		float CrossHairXPosition = 0.5;
	float CrossHairYPosition = 0.333;

	UPROPERTY(EditDefaultsOnly)
		float LineTraceRange = 1000000;

	bool GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const;

	bool GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const;
};
