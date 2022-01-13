// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "ArcanoidePawn.generated.h"

UCLASS(config=Game)
class AArcanoidePawn : public APawn
{
	GENERATED_UCLASS_BODY()

private:
	UPROPERTY(VisibleAnywhere, BluePrintReadOnly, Category = VictoryBox, meta = (AllowPrivateAccess = "true"))
	class USceneComponent* RootScene;

	UPROPERTY(VisibleAnywhere, BluePrintReadOnly, Category = VictoryBox, meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* CollisionBox;

public:

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Patate, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class ABall> BallClass;

	class ABall* Ball;

protected:
	UPROPERTY(EditAnywhere, Category="Movement")
	float MovementSpeed = 10.f;
	
	void Move(float Value);

	void ThrowBall();

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
