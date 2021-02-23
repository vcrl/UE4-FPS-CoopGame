// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FPSExtractZone.generated.h"

UCLASS()
class FPSGAME_API AFPSExtractZone : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFPSExtractZone();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, category = "Mesh")
	class UBoxComponent* CollisionComp;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, category = "Mesh")
	UDecalComponent* DecalComp;

	UFUNCTION(BlueprintCallable)
	void HandleBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, category = "Sound")
	USoundBase* MissingObjectiveSound;
};
