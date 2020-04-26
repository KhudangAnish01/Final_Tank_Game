// Fill out your copyright notice in the Description page of Project Settings.
#include "TankAimingComponent.h"
#include "BattleTank_FinalGameModeBase.h"
#include "Engine/World.h"
#include "Tank.h"
#include "TankAIController.h"

void ATankAIController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn)
	{
		auto PossessedTank = Cast<ATank>(InPawn);
		if (!ensure(PossessedTank)) { return; }
		// Subscribe our local method to the tank's death event
		PossessedTank->OnDead.AddUniqueDynamic(this, &ATankAIController::OnPossedTankDeath);
	}
}

void ATankAIController::OnPossedTankDeath()
{
	GetPawn()->DetachFromControllerPendingDestroy();
}

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
	auto PlayerTank =GetWorld()->GetFirstPlayerController()->GetPawn();
	auto ControlledTank =GetPawn();
	if(!PlayerTank) { return; }
		MoveToActor(PlayerTank, AcceptanceRadius);//moving ai tank
		auto AimComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
		AimComponent->AimAt(PlayerTank->GetActorLocation());//for locating point
		AimComponent->AcceptDamagePoint(MyDamagePoint);//for danage point
		if (AimComponent->GetFiringState() == EFiringState::Locked)
		{
			AimComponent->Fire();
		}
}

