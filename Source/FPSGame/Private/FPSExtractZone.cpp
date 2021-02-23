// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSExtractZone.h"

#include "FPSCharacter.h"
#include "FPSGameMode.h"
#include "Components/BoxComponent.h"
#include "Components/DecalComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AFPSExtractZone::AFPSExtractZone()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionComp = CreateDefaultSubobject<UBoxComponent>("Collision box");
	RootComponent = CollisionComp;
	CollisionComp->SetBoxExtent(FVector(500.f));
	CollisionComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionComp->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	CollisionComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	DecalComp = CreateDefaultSubobject<UDecalComponent>("Decal Comp");
	DecalComp->DecalSize = CollisionComp->GetScaledBoxExtent();
	DecalComp->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AFPSExtractZone::BeginPlay()
{
	Super::BeginPlay();
	CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &AFPSExtractZone::HandleBeginOverlap);
}

// Called every frame
void AFPSExtractZone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFPSExtractZone::HandleBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AFPSCharacter* MyCharacter = Cast<AFPSCharacter>(OtherActor);
	if (MyCharacter != nullptr)
	{
		if (MyCharacter->bIsHoldingObjective)
		{
			AFPSGameMode* GameMode = Cast<AFPSGameMode>(GetWorld()->GetAuthGameMode());
			if (GameMode != nullptr)
			{
				GameMode->CompleteMission(MyCharacter);
			}
		}else
		{
			UGameplayStatics::PlaySound2D(this, MissingObjectiveSound);
		}
		
	}
}

