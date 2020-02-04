// Fill out your copyright notice in the Description page of Project Settings.

#include "Engine/World.h"
#include "TankBarrel.h"

void UTankBarrel::ElevateBarrel(float DegreePerSecond)
{
	auto Time = GetWorld()->GetTimeSeconds();
	UE_LOG(LogTemp, Warning, TEXT("%f: BarrelElevate Called At Speed: %f"), Time,DegreePerSecond)
}

