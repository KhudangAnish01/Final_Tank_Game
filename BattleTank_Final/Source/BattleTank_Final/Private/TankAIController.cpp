// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank_FinalGameModeBase.h"
#include "Engine/World.h"
#include "Tank.h"
#include "TankAIController.h"


void ATankAIController ::BeginPlay()
{
	Super::BeginPlay();

	auto PlayerTank = GetPlayerTank();
	if (!PlayerTank) {
		UE_LOG(LogTemp, Warning, TEXT("AITank is not possess"))
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("AITank possess by: %s"),*( PlayerTank->GetName()))
	}
}


ATank* ATankAIController::GetTankControlled()
{
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const
{
	auto PlayerPawn= GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!PlayerPawn) { return nullptr; }
	return Cast<ATank>(PlayerPawn);
}


