// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "ArcanoidePawn.generated.h"

UCLASS(config=Game)
class AArcanoidePawn : public APawn
{
	GENERATED_UCLASS_BODY()

public:

	virtual void Tick(float DeltaSeconds) override;

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

protected:
	UPROPERTY(EditAnywhere, Category="Movement")
	float MovementSpeed = 500.f;
	
	void Move(float Value);
};
