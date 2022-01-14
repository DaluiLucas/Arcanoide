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
#include "GameFramework/ProjectileMovementComponent.h"
#include "Ball.h"
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
	
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Comp"));
	MeshComp->SetupAttachment(CollisionBox);
	
	FakeBallMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Fake Ball Mesh Comp"));
	FakeBallMeshComp->SetCollisionProfileName(TEXT("OverlapAll"));
	FakeBallMeshComp->SetupAttachment(RootComponent);
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
	PlayerInputComponent->BindAction(TEXT("Throw"), IE_Pressed, this, &AArcanoidePawn::ThrowBall);

}

void AArcanoidePawn::BallDestroyed()
{
	NumberOfBalls--; 
	if (NumberOfBalls == 0) {
		FakeBallMeshComp->SetVisibility(true);
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("PERDU !!!"));

	}
}

void AArcanoidePawn::Move(float Value)
{
	AddMovementInput(FVector(0.f, 1.f, 0.f), Value);
}

void AArcanoidePawn::ThrowBall()
{
	if (BallClass != nullptr && NumberOfBalls == 0) {
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Throw"));
		FakeBallMeshComp->SetVisibility(false);
		FVector ForwardVector = GetActorForwardVector();
		float SpawnDistance = 40.f;
		FVector SpawnLocation = GetActorLocation() + (ForwardVector * SpawnDistance);
		FTransform SpawnTransform(GetActorRotation(), SpawnLocation);
		GetWorld()->SpawnActorDeferred<ABall>(BallClass, SpawnTransform)->FinishSpawning(SpawnTransform);
		NumberOfBalls++;
	}
}

void AArcanoidePawn::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<AWall>(OtherActor) != nullptr) 
	{
		FVector MyLocation = GetActorLocation();
		
		MyLocation.Y = (MyLocation.Y - Cast<AWall>(OtherActor)->Limiter);
		SetActorLocation(MyLocation);
	}
}