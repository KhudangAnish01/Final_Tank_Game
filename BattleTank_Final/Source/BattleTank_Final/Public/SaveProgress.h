// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "SaveProgress.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_FINAL_API USaveProgress : public USaveGame
{
	GENERATED_BODY()

public:

	USaveProgress();

	UPROPERTY(BlueprintReadOnly, Category = "SavingProgress")
		FVector PlayerPosition;

	UPROPERTY(BlueprintReadOnly, Category = "SavingProgress")
		FRotator PlayerRotation;
};
