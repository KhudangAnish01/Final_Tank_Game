// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MenuSwitchGameInstance.generated.h"

/**
 * 
 */

UCLASS()
class BATTLETANK_FINAL_API UMenuSwitchGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, Category = "LoadSwitch")
	bool LoadSwitch=false;

};
