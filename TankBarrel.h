// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS( meta = (BlueprintSpawnableComponent)/*, hidecategories = ("Collision")*/ )
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	// -1 max downward speed
	// +1 max up movement
	void ElevateBarrel(float RelativeSpeed);

private:
	UPROPERTY(EditDefaultsOnly, Category = "Setup" )
	float MaxDegreePerSecond = 5;
	
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float MinElevationDegree = 0;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float MaxElevationDegree = 40;
	
};
