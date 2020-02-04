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
	void ElevateBarrel(float DegreePerSecond);

private:
	UPROPERTY(EditAnyWhere, Category = Setup)
		float MaxDegreePerSecond = 20.0;

	UPROPERTY(EditAnyWhere, Category = Setup)
		float MaxElevationDegrees = 40.0;

	UPROPERTY(EditAnyWhere, Category = Setup)
		float MinElevationDegrees = 0.0;
};
