// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_FINAL_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "Input")
        void SetThrottle(float Throttle);

    //Max Force track applied ,in newton
    UPROPERTY(EditDefaultsOnly)
     float TrackMaxDrivingForce = 50000000;

    void DestroySpawnPoint();

protected:
    TArray<USceneComponent*>Children;  

private:
    UTankTrack();

    void DriveTrack(float CurrentThrottle);

    TArray<class ASprungWheel*> GetWheels();
}; 
