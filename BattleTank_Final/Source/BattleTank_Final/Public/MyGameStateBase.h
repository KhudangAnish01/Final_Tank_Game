// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "MyGameStateBase.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FIsEnemyDestroyed, class ATankAIController*,Enemy);
UCLASS()
class BATTLETANK_FINAL_API AMyGameStateBase : public AGameStateBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable, Category = "EventDispatcher")
		FIsEnemyDestroyed EnemyDestroyed;
};
