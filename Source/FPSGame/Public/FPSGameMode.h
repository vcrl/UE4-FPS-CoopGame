// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "FPSGameMode.generated.h"

UCLASS()
class AFPSGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:

	AFPSGameMode();

	UFUNCTION()
	void CompleteMission(APawn* Actor);

	UFUNCTION(BlueprintImplementableEvent, Category = "Gameplay")
	void OnMissionCompleted(APawn* Actor);

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "View")
	TSubclassOf<AActor> NewCameraView;
};



