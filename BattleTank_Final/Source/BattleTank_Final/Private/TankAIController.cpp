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

// Called every frame
void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//todo move towards player
	//to aim player
	if (!GetPlayerTank()) { return; }
	else
	{
		GetTankControlled()->AimAt(GetPlayerTank()->GetActorLocation());
	}
	//fire if ready

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


