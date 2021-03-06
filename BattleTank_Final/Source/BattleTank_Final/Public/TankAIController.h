// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_FINAL_API ATankAIController : public AAIController
{
	GENERATED_BODY()

private:
	float MyDamagePoint = 10;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnyWhere, Category="Setup")
		float AcceptanceRadius = 6000;//to make AItank stop at 30 cm before Playertank

public:

	void SetPawn(APawn* InPawn);

	UFUNCTION(BlueprintCallable, Category = "Death")
	void OnPossedTankDeath();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Getting Reference Of Aiming Component 
	class UTankAimingComponent* AimComponent; 

	FString EnemyTankName;

	FString FirstName;

	FString lastname;

	int32 count = 25;

	float ReloadTimeInSecond = 3;

	double LastFireTime = 0;

	UPROPERTY(BlueprintReadWrite, Category = "Firing")
	bool IsEnemyDead=false;

	void DestroyEnemy();

	UFUNCTION(BlueprintCallable)
		void Update();
};

