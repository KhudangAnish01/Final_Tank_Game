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

	UPROPERTY(EditDefaultsOnly, Category =" Setup")
		float MaxDegreePerSecond = 15.0;//how fast u want to move barrel

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		float MaxElevationDegrees = 40.0;//katti degree samma barrel utawnay

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		float MinElevationDegrees = 0.0;//katti degree samma barrel jarnay down
};
