// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "FPSGameMode.h"
#include "FPSHUD.h"
#include "FPSCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"

AFPSGameMode::AFPSGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Blueprints/BP_Player"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AFPSHUD::StaticClass();
}

void AFPSGameMode::CompleteMission(APawn* Actor)
{
	if (Actor != nullptr)
	{
		Actor->DisableInput(nullptr);
		OnMissionCompleted(Actor);
		APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		if (PC)
		{
			//AActor* View;

			TArray<AActor*> ReturnedActors;
			UGameplayStatics::GetAllActorsOfClass(GetWorld(), NewCameraView, ReturnedActors);

			if (ReturnedActors.Num() > 0)
			{
				PC->SetViewTargetWithBlend(ReturnedActors[0], 0.5f, EViewTargetBlendFunction::VTBlend_Cubic);
			}
		}
	}
}
