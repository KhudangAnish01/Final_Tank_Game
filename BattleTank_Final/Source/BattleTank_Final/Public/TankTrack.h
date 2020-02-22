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

    UTankTrack();

    virtual void BeginPlay() override;

    UFUNCTION()
        void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

	void ApplySidewaysForce();

    UFUNCTION(BlueprintCallable, Category = "Input")
        void SetThrottle(float Throttle);

    void DriveTrack(float Throttle);

    //Max Force track applied ,in newton
    UPROPERTY(EditDefaultsOnly)
        float TrackMaxDrivingForce = 50000000;

    float CurrentThrottle = 0;
}; 
