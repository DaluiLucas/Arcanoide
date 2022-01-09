// Fill out your copyright notice in the Description page of Project Settings.


#include "ZonePerdu.h"

#include <Components/BoxComponent.h>
#include <Arcanoide/Ball.h>

// Sets default values
AZonePerdu::AZonePerdu()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = RootScene;

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision Box"));
	CollisionBox->SetupAttachment(RootComponent);
	CollisionBox->SetBoxExtent(FVector(60.f, 10.f, 10.f));
	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AZonePerdu::OnBeginOverlap);
}

// Called when the game starts or when spawned
void AZonePerdu::BeginPlay()
{
	Super::BeginPlay();
	
}

void AZonePerdu::OnBeginOverlap(UPrimitiveComponent* OverlapComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<ABall>(OtherActor) != nullptr)
	{
		OtherActor->Destroy();
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("PERDU !!!"));
	}
}


// Called every frame
void AZonePerdu::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

