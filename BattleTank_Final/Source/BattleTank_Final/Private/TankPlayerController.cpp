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

	FVector HitLocation;//out parameter

	if (GetSightRayHitLocation(HitLocation))
	{
		//Tell tha tank aim at this point
		//UE_LOG(LogTemp, Warning, TEXT("HitLocation: %s"),*HitLocation.ToString())
	}
}

//Get The World location if linetrace through CrossHair,it it is true
bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{

	//find the cross hair position
	int32 ViewPortSizeX, ViewPortSizeY;
	GetViewportSize(ViewPortSizeX, ViewPortSizeY);

	auto ScreenLocation = FVector2D(CrossHairXPosition * ViewPortSizeX, CrossHairYPosition * ViewPortSizeY);
	//de-project the position of crosshair to worlld direction
	//linetrace along the look direction,see what we hit
	UE_LOG(LogTemp, Warning, TEXT("ScreenLocation: %s"), *ScreenLocation.ToString())
	return true;
}
