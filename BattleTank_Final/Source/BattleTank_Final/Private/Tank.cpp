// Fill out your copyright notice in the Description page of Project Settings.
#include "Engine/World.h"
#include "Projectile.h"
#include "Tank.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

void ATank::BeginPlay()
{
	Super::BeginPlay();
	CurrentHealth = StartingHealth;//because it call after BP_Constructor which makes logical error in gameplay health
}

float ATank::GetHealthPercent() const
{
	return (float)CurrentHealth / (float)StartingHealth;//1 means full life length
}

float ATank::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	//int32 DamagePoints = (int)DamageAmount;
	int32 DamagePoints = FPlatformMath::RoundToInt(DamageAmount);//Rounds up nearest integer cause damagepoint is in float
	int32 DamageToApply = FMath::Clamp(DamagePoints, 0, CurrentHealth);//if we want to make tank life decrese slowly then tweak this code
	CurrentHealth -= DamageToApply;

	if (CurrentHealth <= 0)
	{
		OnDead.Broadcast();
	}
	return DamageToApply;
}

void  ATank::GetMedicalKit(int health) {
	CurrentHealth += health;
	if (CurrentHealth > 100) {
		CurrentHealth = 100;
	}
}

void  ATank::ReSpawn() {
	CurrentHealth = 100;
}


