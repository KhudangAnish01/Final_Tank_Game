// Fill out your copyright notice in the Description page of Project Settings.
#include "TankAimingComponent.h"
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
	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto ControlledTank = GetPawn();
	if (!ensure(PlayerTank && ControlledTank)) { return; }
		MoveToActor(PlayerTank, AcceptanceRadius);
		auto AimComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
		AimComponent->AimAt(PlayerTank->GetActorLocation());
		AimComponent->Fire();
}

