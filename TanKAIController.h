// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TanKAIController.generated.h"


/**
 * 
 */
UCLASS()
class BATTLETANK_API ATanKAIController : public AAIController
{
	GENERATED_BODY()

protected:
	// The maximum approach between the AI and the player
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float AcceptanceRadius = 7500;

private:
	virtual void BeginPlay() override;

	virtual void SetPawn(APawn* InPawn) override;

	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnTankDeath();

};
