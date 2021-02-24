// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FPSLaunchPad.generated.h"

UCLASS()
class FPSGAME_API AFPSLaunchPad : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFPSLaunchPad();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Mesh")
	UStaticMeshComponent* Mesh;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Mesh")
	class UBoxComponent* BoxComp;

	UFUNCTION(BlueprintCallable, Category = "Collision")
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UFUNCTION(BlueprintImplementableEvent, Category = "Gameplay")
	void LaunchPlayer(AActor* Actor);

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Effects")
	UParticleSystem* LaunchFX;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Sound")
	USoundBase* LaunchSound;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Gameplay")
	float LaunchStrength;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Gameplay")
	float LaunchPitch;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Gameplay")
	float LaunchHeight;

	

};
