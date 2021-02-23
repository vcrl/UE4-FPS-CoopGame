// Fill out your copyright notice in the Description page of Project Settings.


#include "Blackhole.h"
#include "Components/SphereComponent.h"

// Sets default values
ABlackhole::ABlackhole()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("Mesh Comp");
	SetRootComponent(MeshComp);
	
	InnerSphere = CreateDefaultSubobject<USphereComponent>("Hole Mesh");
	InnerSphere->SetupAttachment(GetRootComponent());
	InnerSphere->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	OuterSphere = CreateDefaultSubobject<USphereComponent>("Destroy Actor Sphere");
	OuterSphere->SetupAttachment(GetRootComponent());
	OuterSphere->SetCollisionEnabled(ECollisionEnabled::NoCollision);

}

// Called when the game starts or when spawned
void ABlackhole::BeginPlay()
{
	Super::BeginPlay();
	OuterSphere->OnComponentBeginOverlap.AddDynamic(this, &ABlackhole::OverlapsOutersphere);
	
}

// Called every frame
void ABlackhole::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	TArray<UPrimitiveComponent*> OverlappingComp;
	OuterSphere->GetOverlappingComponents(OverlappingComp);

	for (int i = 0; i < OverlappingComp.Num(); i++)
	{
		UPrimitiveComponent* PrimComp = OverlappingComp[i];
		if (PrimComp && PrimComp->IsSimulatingPhysics())
		{
			const float SphereRadius = OuterSphere->GetScaledSphereRadius();
			const float ForceStrength = -2000; // Negative value to pull toward origin

			PrimComp->AddRadialForce(GetActorLocation(), SphereRadius, ForceStrength, ERadialImpulseFalloff::RIF_Constant, false);
		}
	}

}

void ABlackhole::OverlapsOutersphere(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor != nullptr)
	{
		OtherActor->Destroy();
	}
}

