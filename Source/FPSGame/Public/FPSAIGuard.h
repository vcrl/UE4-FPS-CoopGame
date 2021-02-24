// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Perception/PawnSensingComponent.h"

#include "FPSAIGuard.generated.h"

UCLASS()
class FPSGAME_API AFPSAIGuard : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFPSAIGuard();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditDefaultsOnly, Category = "Sensor")
	UPawnSensingComponent* SensingComp;

	UFUNCTION(BlueprintCallable, Category = "Sensor")
	void OnSeePawn(APawn* SeenPawn);

	UFUNCTION(BlueprintCallable, Category = "Sensor")
    void OnHearPawn(APawn* HeardPawn, const FVector& Location, float Volume);

};
