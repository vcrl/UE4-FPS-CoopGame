// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSAIGuard.h"


#include "FPSGameMode.h"
#include "Kismet/KismetMathLibrary.h"


// Sets default values
AFPSAIGuard::AFPSAIGuard()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SensingComp = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("Sensing Component"));
	GuardState = EAIGuardState::Idle;

}

// Called when the game starts or when spawned
void AFPSAIGuard::BeginPlay()
{
	Super::BeginPlay();
	SensingComp->OnSeePawn.AddDynamic(this, &AFPSAIGuard::OnSeePawn);
	SensingComp->OnHearNoise.AddDynamic(this, &AFPSAIGuard::OnHearPawn);
	InitialRot = GetActorRotation();
	
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
	AFPSGameMode* GM = Cast<AFPSGameMode>(GetWorld()->GetAuthGameMode());
	GM->CompleteMission(SeenPawn, true);

	if (GuardState != EAIGuardState::Alerted)
	{
		SetGuardState(EAIGuardState::Alerted);
	}
}

void AFPSAIGuard::OnHearPawn(APawn* HeardPawn, const FVector& Location, float Volume)
{
	FVector Direction = Location - GetActorLocation();
	Direction.Normalize();

	FRotator NewLookDir = FRotationMatrix::MakeFromX(Direction).Rotator();
	NewLookDir.Roll = 0.f;
	NewLookDir.Pitch = 0.f;
	SetActorRotation(NewLookDir);
	GetWorldTimerManager().ClearTimer(TimerHandle_ResetLocation);
	GetWorldTimerManager().SetTimer(TimerHandle_ResetLocation, this, &AFPSAIGuard::ResetPosition, 3.f);

	if (GuardState != EAIGuardState::Alerted)
	{
		SetGuardState(EAIGuardState::Suspicicous);
	}
	
}

void AFPSAIGuard::ResetPosition()
{
	SetActorRotation(InitialRot);
	UE_LOG(LogTemp, Warning, TEXT("Oui"));
	if (GuardState != EAIGuardState::Alerted)
	{
		SetGuardState(EAIGuardState::Idle);
	}
}

void AFPSAIGuard::SetGuardState(EAIGuardState NewState)
{
	if (GuardState == NewState)
	{
		return;
	}

	GuardState = NewState;
	OnStateChange(GuardState);
}
