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

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrossHair();
}

ATank* ATankPlayerController::GetTankControlled()
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrossHair()
{
	if (!GetTankControlled()) { return; }
	//Get The World location if linetrace through CrossHair
	//if hits landscape
		//Tell tha tank aim at this point
}
