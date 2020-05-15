// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/PrimitiveComponent.h"
#include "SaveProgress.h"
#include"Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "TankPlayerController.h"
#include"TankAimingComponent.h"
#include"Tank.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	if (!GetPawn()) { return; } // e.g. if not possessing
	 AimComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimComponent)) { return; }
		FoundAimingComponent(AimComponent);
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrossHair();
}

void ATankPlayerController::PossessedDeath()
{
	if (!GetPawn()) { return; } // e.g. if not possessing
	Player = GetWorld()->GetFirstPlayerController();
	GetPawn()->DisableInput(Player);

	auto SaveProgressInstance = Cast<USaveProgress>(UGameplayStatics::LoadGameFromSlot("CheckPoint", 0));
	if (!SaveProgressInstance) { return; }
	//Set Player Position
	FHitResult Hit;
	Player->GetPawn()->SetActorLocation(SaveProgressInstance->PlayerPosition, false, &Hit, ETeleportType::TeleportPhysics);
	TankRoot = Cast<UPrimitiveComponent>(AimComponent->GetOwner()->GetRootComponent());
	if (!TankRoot) { return; }
	UE_LOG(LogTemp, Warning, TEXT("TankRoot"));
	TankRoot->SetSimulatePhysics(false);
	GetPawn()->EnableInput(Player);

	FTimerHandle Timer;//Respawn Time;
	GetWorld()->GetTimerManager().SetTimer(Timer, this, &ATankPlayerController::GoToCheckPoint, 3, false);
}

void ATankPlayerController::AimTowardsCrossHair()
{
	if (!GetPawn()) { return; } // e.g. if not possessing
	AimComponent->AcceptDamagePoint(MyDamagePoint);//for damage point
	if (!ensure(AimComponent)) { return; }

	FVector HitLocation;//out parameter
	bool bGotHitLocation = GetSightRayHitLocation(HitLocation);
	//UE_LOG(LogTemp, Warning, TEXT("bGotHitLocation: %i"), bGotHitLocation)
	if (bGotHitLocation)
	{
		//Tell tha tank aim at this point
		AimComponent->AimAt(HitLocation);
	}
}

//Get The World location if linetrace through CrossHair,it it is true
bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{
	//find the cross hair position
	int32 ViewPortSizeX, ViewPortSizeY;
	GetViewportSize(ViewPortSizeX, ViewPortSizeY);

	auto ScreenLocation = FVector2D(CrossHairXPosition * ViewPortSizeX, CrossHairYPosition * ViewPortSizeY);
	FVector LookDirection;
	//de-project the position of crosshair to worlld direction
	if (GetLookDirection(ScreenLocation, LookDirection))
	{
		return GetLookVectorHitLocation(LookDirection, HitLocation);
	}
	//linetrace along the look direction,see what we hit
	return false;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
	FVector CameraWorldLocation;//to be discarded
	if (DeprojectScreenPositionToWorld(
		ScreenLocation.X,
		ScreenLocation.Y,
		CameraWorldLocation,
		LookDirection
	))
	{
		return true;
	}
	return false;
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const
{
	FHitResult HitResult;

	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + (LineTraceRange * LookDirection);
	if (GetWorld()->LineTraceSingleByChannel(
		HitResult,
		StartLocation,
		EndLocation,
		ECollisionChannel::ECC_Visibility
	))
	{
		HitLocation = HitResult.Location;
		return true;
	}
	return false;
}

void ATankPlayerController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);

	if (InPawn)
	{
		auto PossessedTank = Cast<ATank>(InPawn);
		if (!ensure(PossessedTank)) { return; }
		PossessedTank->OnDead.AddUniqueDynamic(this, &ATankPlayerController::PossessedDeath);
	}
}

void ATankPlayerController::GoToCheckPoint() {
	//Load Saved Game from slot
	Cast<ATank>(Player->GetPawn())->ReSpawn();
	TankRoot->SetSimulatePhysics(true);
}
