// Fill out your copyright notice in the Description page of Project Settings.


#include "BreakableBlock.h"
#include <Components/CapsuleComponent.h>

// Sets default values
ABreakableBlock::ABreakableBlock()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = RootScene;

	CollisionBox = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Collision Box"));
	CollisionBox->SetupAttachment(RootComponent);
	CollisionBox->SetCapsuleSize(30.0f, 55.0f);
	CollisionBox->SetRelativeLocation(FVector(0.f, 0.f, 120.f));

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Comp"));
	MeshComp->SetupAttachment(CollisionBox);


}

// Called when the game starts or when spawned
void ABreakableBlock::BeginPlay()
{
	Super::BeginPlay();
	MeshComp->SetVectorParameterValueOnMaterials(FName("Color"), FVector(0.6f, 0.6f, 0.2f));
	
}

// Called every frame
void ABreakableBlock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

