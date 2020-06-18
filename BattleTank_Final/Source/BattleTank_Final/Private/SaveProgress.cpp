// Fill out your copyright notice in the Description page of Project Settings.


#include "SaveProgress.h"

USaveProgress::USaveProgress() {
	PlayerPosition = FVector(0.0f, 0.0f, 0.0f);
	PlayerLife = 0;
	MachinegunAmmo = 0;
	TankAmmo = 0;
	MaxMachinegunAmmo = 0;
}