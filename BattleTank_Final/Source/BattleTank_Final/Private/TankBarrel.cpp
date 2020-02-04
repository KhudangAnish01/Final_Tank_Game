// Fill out your copyright notice in the Description page of Project Settings.

#include "Engine/World.h"
#include "TankBarrel.h"

void UTankBarrel::ElevateBarrel(float RelativeSpeed)
{
	//auto Time = GetWorld()->GetTimeSeconds();
	//UE_LOG(LogTemp, Warning, TEXT("%f: BarrelElevate Called At Speed: %f"), Time,DegreePerSecond)
	RelativeSpeed= FMath::Clamp<float>(RelativeSpeed, -1, +1);
	auto ElevationChange = RelativeSpeed * MaxDegreePerSecond * GetWorld()->DeltaTimeSeconds;
	auto RawNewElevation = RelativeRotation.Pitch + ElevationChange;//RelativeRotation defines present rotation of component (TankBarrel)
	auto ELevation = FMath::Clamp<float>(RawNewElevation, MinElevationDegrees, MaxElevationDegrees);//binds RawNewElevation between 0 and 40
	SetRelativeRotation(FRotator(ELevation, 0, 0));
}

