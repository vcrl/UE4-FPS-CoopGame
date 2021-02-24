// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSLaunchPad.h"

#include "FPSCharacter.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AFPSLaunchPad::AFPSLaunchPad()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Comp"));
	Mesh->SetupAttachment(GetRootComponent());
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Comp"));
	BoxComp->SetupAttachment(Mesh);
	BoxComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	BoxComp->SetCollisionResponseToAllChannels(ECR_Overlap);

	LaunchStrength = 5000.f;
	LaunchPitch = 45.f;
	LaunchHeight = 1000.f;

}

// Called when the game starts or when spawned
void AFPSLaunchPad::BeginPlay()
{
	Super::BeginPlay();
	BoxComp->OnComponentBeginOverlap.AddDynamic(this, &AFPSLaunchPad::OnBeginOverlap);
	
}

// Called every frame
void AFPSLaunchPad::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFPSLaunchPad::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
	if (OtherActor)
	{
		FRotator LaunchRotation = OtherActor->GetActorRotation();
		LaunchRotation.Pitch += LaunchPitch;
		FVector LaunchVelocity = LaunchRotation.Vector() * LaunchStrength;
		
		ACharacter* MyCharacter = Cast<ACharacter>(OtherActor);

		TArray<UPrimitiveComponent*> OverlappingActors; // Array of PrimitiveComponent
		BoxComp->GetOverlappingComponents(OverlappingActors); // Store all overlappingcomponents of BoxComp in the array
		
		if (MyCharacter)
		{
			UE_LOG(LogTemp, Warning, TEXT("Player overlapping"));
			MyCharacter->LaunchCharacter(FVector(LaunchVelocity.X, LaunchVelocity.Y, LaunchHeight), false, false);
		}else
		{
			for (int i = 0; i < OverlappingActors.Num(); i++) // For every Components in the array
			{
				UPrimitiveComponent* CurrentComp = OverlappingActors[i]; // Store in variable
				if (CurrentComp && CurrentComp->IsSimulatingPhysics()) // If not null + simulatingphysics
				{
					UE_LOG(LogTemp, Warning, TEXT("Cube Overlapping"))
					CurrentComp->AddImpulse(FVector(LaunchVelocity.X, LaunchVelocity.Y, LaunchHeight), NAME_None, true); // SET TO NAME_NAME + TRUE FOR IT TO WORK // add impulse
				}
			}
		}
		UGameplayStatics::SpawnEmitterAtLocation(this, LaunchFX, GetActorLocation());
		UGameplayStatics::PlaySound2D(this, LaunchSound);
	}
}

