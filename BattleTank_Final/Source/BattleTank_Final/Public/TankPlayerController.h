// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"
class ATank;

/**
 * 
 */
UCLASS()
class BATTLETANK_FINAL_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

public:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	ATank* GetTankControlled();
};
