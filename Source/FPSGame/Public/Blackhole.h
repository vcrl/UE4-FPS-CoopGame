// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Blackhole.generated.h"

UCLASS()
class FPSGAME_API ABlackhole : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABlackhole();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintReadWrite, EditInstanceOnly, Category = "Mesh")
	UStaticMeshComponent* MeshComp;

	UPROPERTY(BlueprintReadWrite, EditInstanceOnly, Category = "Mesh")
	class USphereComponent* InnerSphere;

	UPROPERTY(BlueprintReadWrite, EditInstanceOnly, Category = "Mesh")
	class USphereComponent* OuterSphere;

	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	void OverlapsOutersphere(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

};
