// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
//Provides properties Of Barrel
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_FINAL_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()

public:

	//-1 is max downward speed and +1 is max upward speed
	void ElevateBarrel(float RelativeSpeed);

private:
	UPROPERTY(EditAnyWhere, Category = Setup)
		float MaxDegreePerSecond = 5.0;

	UPROPERTY(EditAnyWhere, Category = Setup)
		float MaxElevationDegrees = 40.0;

	UPROPERTY(EditAnyWhere, Category = Setup)
		float MinElevationDegrees = 0.0;
};
