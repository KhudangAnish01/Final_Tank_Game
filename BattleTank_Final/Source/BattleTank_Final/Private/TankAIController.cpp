// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank_FinalGameModeBase.h"
#include "Engine/World.h"
#include "Tank.h"
#include "TankAIController.h"


void ATankAIController ::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//todo move towards player
	//to aim player
	auto PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	auto ControlledTank = Cast<ATank>(GetPawn());
	if (PlayerTank)
	{
		MoveToActor(PlayerTank, AcceptanceRadius);

		ControlledTank->AimAt(PlayerTank->GetActorLocation());
		//fire if ready
		ControlledTank->Fire();
	}
	
}

