// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTankDelegate);//yaha hamila awta matrai delegate garxaw but we can made multicast here

UCLASS()
class BATTLETANK_FINAL_API ATank : public APawn
{
	GENERATED_BODY()

public:

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	UFUNCTION(BlueprintCallable,Category="Health")
	float GetHealthPercent() const;

	FTankDelegate OnDead;

	void GetMedicalKit(int health);

	void ReSpawn(int RemainLife);

	int ReturnCurrentHealth();

	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite, Category = "Health")//remains constant don't change
		int32 CurrentHealth=100;

private:
	// Sets default values for this pawn's properties
	ATank();

	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")//use manipulate
	int32 StartingHealth = 100;	
};
