// Copyright Epic Games, Inc. All Rights Reserved.

#include "ArcanoidePawn.h"
#include "ArcanoideBlock.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"

AArcanoidePawn::AArcanoidePawn(const FObjectInitializer& ObjectInitializer) 
	: Super(ObjectInitializer)
{
	AutoPossessPlayer = EAutoReceiveInput::Player0;
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

	if ((Controller != nullptr) && (Value != 0.0f))
	{
		

		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, Direction.ToString());
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, YawRotation.ToString());
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}
