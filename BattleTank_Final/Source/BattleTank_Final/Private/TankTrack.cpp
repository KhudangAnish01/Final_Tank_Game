// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTrack.h"

void  UTankTrack::SetThrottle(float Throttle)
{
	auto ForceApplied = GetForwardVector() * Throttle * TrackMaxDrivingForce;//get forward get forward value
	auto ForceLocation = GetComponentLocation();
	//we must use tankroot to apply force and must be uprimitivecomponent.
	auto TankRoot = Cast<UPrimitiveComponent> (GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}



