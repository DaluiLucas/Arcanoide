// Fill out your copyright notice in the Description page of Project Settings.


#include "BreakableBlock.h"
#include <Components/BoxComponent.h>
#include "Ball.h"
#include <Kismet/KismetSystemLibrary.h>
#include<chrono>
#include<thread>

// Sets default values
ABreakableBlock::ABreakableBlock()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = RootScene;

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision Box"));
	CollisionBox->SetupAttachment(RootComponent);
	CollisionBox->SetBoxExtent(FVector(60.f, 60.f, 60.f));
	CollisionBox->SetRelativeLocation(FVector(0.f, 0.f, 120.f));
	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &ABreakableBlock::OnBeginOverlap);
}

// Called when the game starts or when spawned
void ABreakableBlock::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABreakableBlock::OnBeginOverlap(UPrimitiveComponent* OverlapperComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<ABall>(OtherActor) != nullptr)
	{
		Destroy();
	}
}

// Called every frame
void ABreakableBlock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

