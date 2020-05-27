// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "OpenWorld_BP.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_FINAL_API AOpenWorld_BP : public ALevelScriptActor
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	TMap<class ATankAIController*, bool>SavedData;

	void LoadingEnemyData();

	void SavingEnemyData();

	void SavePlayerStatus();

	UFUNCTION()
	void BindingFunction(class ATankAIController* Enemy);
};
