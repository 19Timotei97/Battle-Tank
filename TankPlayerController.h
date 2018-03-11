// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

//Foward declaration
class UTankAimingComponent;

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
	void AimCompFound(UTankAimingComponent* AimCompRef);

private:

	virtual void BeginPlay() override;

	virtual void Tick( float DeltaTime ) override;

	virtual void SetPawn(APawn* InPawn) override;
	
	UFUNCTION()
	void OnPlayerTankDeath();

	// The barrel moves so it hits where the crosshair interesects the world
	void AimTowardsCrosshair();

	bool GetSightRayHitLocation(FVector& OutHitLocation) const;
	
	 UPROPERTY(EditDefaultsOnly)
	 float CrossHairXLocation = 0.5;

	 UPROPERTY(EditDefaultsOnly)
	 float CrossHairYLocation = 0.33333;

	 bool GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const;

	 bool GetLookVectorHitLocation(FVector LookDirection, FVector &HitLocation) const;
	 
	 UPROPERTY(EditDefaultsOnly)
	 float LineTraceRange = 1000000;

};
