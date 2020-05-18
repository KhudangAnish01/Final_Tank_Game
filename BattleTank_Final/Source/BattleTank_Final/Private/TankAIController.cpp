// Fill out your copyright notice in the Description page of Project Settings.
#include "MyGameStateBase.h"
#include "TankMovementComponent.h"
#include "TimerManager.h"
#include "TankAimingComponent.h"
#include "BattleTank_FinalGameModeBase.h"
#include "Engine/World.h"
#include "Tank.h"
#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	LastFireTime = FPlatformTime::Seconds();
	AimComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	EnemyTankName = AimComponent->GetOwner()->GetName();
	EnemyTankName.Split("_", &FirstName, &lastname);
}

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
	IsEnemyDead = true;
	AMyGameStateBase* const MyGameState = GetWorld() != NULL ? GetWorld()->GetGameState<AMyGameStateBase>() : NULL;
	MyGameState->EnemyDestroyed.Broadcast(this);
	DestroyEnemy();
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
		AimComponent->AimAt(PlayerTank->GetActorLocation());//for locating point
		AimComponent->AcceptDamagePoint(MyDamagePoint);//for danage point
		if (AimComponent->GetFiringState() == EFiringState::Locked)
		{
			if (FirstName == "EM4"|| FirstName == "EM5") {
				if (count > 0) {
					AimComponent->FireBullet();
					UE_LOG(LogTemp, Warning, TEXT("%d"), count);
					LastFireTime = FPlatformTime::Seconds();
					count--;
				}
				else if(((FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSecond)) {
					count = 25;
				}
			}
			else {
				AimComponent->Fire();
			}
		}
}

void ATankAIController::DestroyEnemy() {
	auto MovementRef = GetPawn()->FindComponentByClass<UTankMovementComponent>();//for destroying spawnpoint child of lefttrack
	if (MovementRef) {
		if (!MovementRef) { return; }
		MovementRef->TrackReference();
	}
	AimComponent->GetOwner()->Destroy();
}

void ATankAIController::Update() {
	if (IsEnemyDead) {
		DestroyEnemy();
	}
}