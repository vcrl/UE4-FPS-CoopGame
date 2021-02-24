// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSAIGuard.h"


// Sets default values
AFPSAIGuard::AFPSAIGuard()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SensingComp = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("Sensing Component"));

}

// Called when the game starts or when spawned
void AFPSAIGuard::BeginPlay()
{
	Super::BeginPlay();
	SensingComp->OnSeePawn.AddDynamic(this, &AFPSAIGuard::OnSeePawn);
	SensingComp->OnHearNoise.AddDynamic(this, &AFPSAIGuard::OnHearPawn);
	
}

// Called every frame
void AFPSAIGuard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AFPSAIGuard::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AFPSAIGuard::OnSeePawn(APawn* SeenPawn)
{
	UE_LOG(LogTemp, Warning, TEXT("Detected !"));
}

void AFPSAIGuard::OnHearPawn(APawn* HeardPawn, const FVector& Location, float Volume)
{
	UE_LOG(LogTemp, Warning, TEXT("Heard !"));
}
