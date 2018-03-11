// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurret.h"
#include "BattleTank.h"
#include "Engine/World.h"

void UTankTurret::RotateTurret(float RelativeSpeed)
{
	// Move the barrel the right ammount this frame
	// Given a max velocity and the frame time
	auto NewRelSpeed = FMath::Clamp<float>(RelativeSpeed, -1, +1);
	auto RotationChange = NewRelSpeed * MaxDegreePerSecond * GetWorld()->DeltaTimeSeconds;
	auto NewRotation = RelativeRotation.Yaw + RotationChange;
	SetRelativeRotation(FRotator(0, NewRotation, 0));

}


