// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"
#include "BattleTank.h"
#include "Engine/World.h"

void UTankBarrel::ElevateBarrel(float RelativeSpeed)
{
	// Move the barrel the right ammount this frame
	// Given a max velocity and the frame time
	auto NewRelSpeed = FMath::Clamp<float>(RelativeSpeed, -1, +1);
	auto ElevationChange = NewRelSpeed * MaxDegreePerSecond * GetWorld()->DeltaTimeSeconds;
	auto RawNewElevation = RelativeRotation.Pitch + ElevationChange;
	auto Elevation = FMath::Clamp<float>(RawNewElevation, MinElevationDegree, MaxElevationDegree);
	SetRelativeRotation(FRotator(Elevation, 0, 0));
	
}




