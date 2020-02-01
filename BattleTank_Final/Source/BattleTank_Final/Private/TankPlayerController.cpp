// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"
#include "Tank.h"


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	auto ControlledTank = GetTankControlled();
	if (!ControlledTank) {
		UE_LOG(LogTemp, Warning, TEXT("Tank is not possess"))
	}

	else{
		UE_LOG(LogTemp,Warning,TEXT("Tank possess by: %s"), *ControlledTank->GetName())
	}
}


ATank* ATankPlayerController::GetTankControlled()
{
	return Cast<ATank>(GetPawn());
}

