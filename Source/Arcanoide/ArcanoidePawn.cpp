// Copyright Epic Games, Inc. All Rights Reserved.

#include "ArcanoidePawn.h"
#include "ArcanoideBlock.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include <Kismet/KismetSystemLibrary.h>
#include "Wall.h"
#include <Components/BoxComponent.h>

AArcanoidePawn::AArcanoidePawn(const FObjectInitializer& ObjectInitializer) 
	: Super(ObjectInitializer)
{
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = RootScene;

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision Box"));
	CollisionBox->SetupAttachment(RootComponent);
	CollisionBox->SetBoxExtent(FVector(50.f, 250.f, 25.f));
	

}

void AArcanoidePawn::BeginPlay()
{
	Super::BeginPlay();
	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AArcanoidePawn::OnBeginOverlap);
}
void AArcanoidePawn::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void AArcanoidePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis(TEXT("Move"), this, &AArcanoidePawn::Move);
}

void AArcanoidePawn::Move(float Value)
{
	AddMovementInput(FVector(0.f, 1.f, 0.f), Value);
}

void AArcanoidePawn::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Hit"));
	if (Cast<AWall>(OtherActor) != nullptr) 
	{
		FVector MyLocation = GetActorLocation();
		
		MyLocation.Y = (MyLocation.Y - Cast<AWall>(OtherActor)->Limiter);
		SetActorLocation(MyLocation);
	}
}