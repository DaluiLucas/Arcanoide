// Fill out your copyright notice in the Description page of Project Settings.


#include "Ball.h"
#include "BreakableBlock.h"

#include <Components/SphereComponent.h>
#include <GameFramework/ProjectileMovementComponent.h>
// Sets default values
ABall::ABall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Component"));
	SphereComponent->SetSphereRadius(35.f);
	SphereComponent->SetCollisionProfileName("Ball");
	SphereComponent->SetSimulatePhysics(true);
	SphereComponent->SetNotifyRigidBodyCollision(true);

	RootComponent = SphereComponent;

	BallMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));
	BallMovement->InitialSpeed = 0.f;
}

// Called when the game starts or when spawned
void ABall::BeginPlay()
{
	Super::BeginPlay();	

	SphereComponent->OnComponentHit.AddDynamic(this, &ABall::OnHit);
}

void ABall::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& hit)
{
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, TEXT("HIT"));
	ABreakableBlock* Block = Cast<ABreakableBlock>(OtherActor);
	if (Block != nullptr)
	{
		Block->Destroy();
	}
}

// Called every frame
void ABall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Yellow, FString::Printf(TEXT("MS: %f"), MovementSpeed));

}

