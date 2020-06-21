// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTurret.h"

void UTankTurret::RotateTurret(float RelativeSpeed)
{
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, +1);
	auto RotationChange = RelativeSpeed * MaxDegreePerSecond * GetWorld()->DeltaTimeSeconds;//relative spped check more
	auto Rotation = GetRelativeRotation().Yaw + RotationChange;//RelativeRotation defines present rotation of component (TankTurret)
	SetRelativeRotation(FRotator( 0, Rotation, 0));
}