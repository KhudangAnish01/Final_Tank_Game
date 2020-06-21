// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TimerManager.h"
#include "TankTurret.h"
#include "TankBarrel.h"
#include"Kismet/GameplayStatics.h"
#include"Components/StaticMeshComponent.h"
#include "Engine/World.h"
#include"Projectile.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::initialse(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet)
{
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}

void UTankAimingComponent::AcceptDamagePoint(float HitDamage) {
	DamagePoint = HitDamage;
}

// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();
	//initailize only one time at begin
	LastFireTime = FPlatformTime::Seconds();//AI la suru mai nahanos vanayra,only hit after after 3 seconds
}

// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//for TankBullet
	if (TankRoundsLeft == 0 && CurrentGunBullet==0)
	{
		FiringState = EFiringState::OutOfAmmo;
	}
	else if ((FPlatformTime::Seconds() - LastFireTime)< ReloadTimeInSecond)
	{
		FiringState = EFiringState::Reloading;
	}
	else if( (IsBarrelMoving())&&(IsReloading))
	{
		FiringState = EFiringState::Aiming;
	}
	else
	{
		if (IsReloading) {
			FiringState = EFiringState::Locked;
		}
	}
}

int UTankAimingComponent::GetTankBullet() const
{
	return TankRoundsLeft;
}

int UTankAimingComponent::GetMaxGunBullet() const
{
	return MaxGunBullett;
}

int UTankAimingComponent::GetCurrentGunBullet() const
{
	return CurrentGunBullet;
}

EFiringState UTankAimingComponent::GetFiringState() const
{
	return FiringState;
}

bool UTankAimingComponent::IsBarrelMoving()
{
	if (!ensure(Barrel)) { return false; }
	auto BarrelForward = Barrel->GetForwardVector();
	return !BarrelForward.Equals(AimDirection, 0.01);//kati ko difference xa 0.01 wit aim direction that has normal value 1
}
  
void UTankAimingComponent::AimAt(FVector HitLocation)
{
	if (!ensure(Barrel)) { return; }
	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));

	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(
		this,
		OutLaunchVelocity,
		StartLocation,
		HitLocation,
		LaunchSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace//used paramteter false,0,0 to prevent bugs
	);

	if(bHaveAimSolution)
	{
		AimDirection = OutLaunchVelocity.GetSafeNormal(); 
		MoveBarrelTowards(AimDirection);
	}
	//if no solution then do nothing
}

void  UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	if (!ensure(Barrel) || !ensure(Turret)) { return; }
	//work-out Difference Between current Barrel Rotation and AimDirection
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();//AimDirection is used here as initial value for barrel pointing
	auto DeltaRotator = AimAsRotator - BarrelRotator;//(if Barrel move up then +ve ,if Barrel move up We get -ve)
	Barrel->ElevateBarrel(DeltaRotator.Pitch);

	if (FMath::Abs(DeltaRotator.Yaw) < 180)//IT IS DONE TO TAKE SHORT PATH OF AIMING,DECREASE ROTATING TIME
	{
		Turret->RotateTurret(DeltaRotator.Yaw);
	}
	else
	{
		Turret->RotateTurret(-DeltaRotator.Yaw);
	}
}
	
void UTankAimingComponent::Fire()
{
	if (FiringState== EFiringState::Aiming || FiringState == EFiringState::Locked) {//locked means while not moving barel
		if (!ensure(Barrel)) { return; }
		if (!ensure(ProjectileBlueprint)) { return; }
		if (TankRoundsLeft != 0) {
			auto Projectile = GetWorld()->SpawnActor<AProjectile>(
				ProjectileBlueprint,
				Barrel->GetSocketLocation(FName("Projectile")),
				Barrel->GetSocketRotation(FName("Projectile"))
				);
			Projectile->LaunchProjectile(LaunchSpeed);
			Projectile->GetProjectileDamage(DamagePoint);
			TankRoundsLeft--;
		}
		LastFireTime = FPlatformTime::Seconds();
	}
}

void UTankAimingComponent::FireBullet() {
	if (FiringState == EFiringState::Aiming || FiringState == EFiringState::Locked) {
		if (!ensure(Barrel)) { return; }
		if (!ensure(ProjectileBlueprint1)) { return; }
		if (CurrentGunBullet != 0) {
			auto Projectile = GetWorld()->SpawnActor<AProjectile>(
				ProjectileBlueprint1,
				Barrel->GetSocketLocation(FName("Projectile1")),
				Barrel->GetSocketRotation(FName("Projectile1"))
				);
			Projectile->LaunchProjectile(LaunchSpeed);
			Projectile->GetProjectileDamage(1.0);
			CurrentGunBullet--;
		}
	}
}

void UTankAimingComponent::Reloading() {
	IsReloading = false;
	FiringState = EFiringState::Reloading;
		FTimerHandle Delaying;//ReloadingBullet
		GetWorld()->GetTimerManager().SetTimer(Delaying, this, &UTankAimingComponent::Delay, ReloadTimeGun, false);
}

void UTankAimingComponent::GetGrabbedTankAmmo(int GrabTankAmmo) {
	TankRoundsLeft += GrabTankAmmo;
	if (TankRoundsLeft > 30) {
		TankRoundsLeft = 30;
	}
}

void UTankAimingComponent::GetGrabbedGunAmmo(int GrabGunAmmo) {
	MaxGunBullett += GrabGunAmmo;
	if (MaxGunBullett > 120) {
		MaxGunBullett = 120;
	}
}

void UTankAimingComponent::Delay() {
	IsReloading = true;
	if (CurrentGunBullet == MagazineSize) {//1
	}
	else {//2
		if (MaxGunBullett > MagazineSize) {//2.1
			MaxGunBullett += CurrentGunBullet;
			CurrentGunBullet = MagazineSize;
			MaxGunBullett = MaxGunBullett - MagazineSize;
		}
		else {//2.2
			MaxGunBullett += CurrentGunBullet;
			if (MaxGunBullett > MagazineSize) {//2.2.1
				CurrentGunBullet = MagazineSize;
				MaxGunBullett = MaxGunBullett - MagazineSize;
			}

			else {//2.2.2
				CurrentGunBullet = MaxGunBullett;
				MaxGunBullett = 0;
			}
		}
	}
}

void  UTankAimingComponent::RetrievedSavedAmmo(int TankAmmo, int GunAmmo, int MaxGunAmmo) {
	CurrentGunBullet = GunAmmo;
	TankRoundsLeft = TankAmmo;
	MaxGunBullett = MaxGunAmmo;
}

//114 lines of code