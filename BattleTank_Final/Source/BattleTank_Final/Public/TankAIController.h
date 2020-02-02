// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

class ATank;
/**
 * 
 */
UCLASS()
class BATTLETANK_FINAL_API ATankAIController : public AAIController
{
	GENERATED_BODY()

public:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//Gets the name of Tank actor possessed by the AI
	ATank* GetTankControlled();

	ATank* GetPlayerTank() const;
	
};
