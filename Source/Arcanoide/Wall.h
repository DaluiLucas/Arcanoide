// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Wall.generated.h"

UCLASS()
class ARCANOIDE_API AWall : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere, BluePrintReadOnly, Category = Wall, meta = (AllowPrivateAccess = "true"))
	class USceneComponent* RootScene;
public:	
	// Sets default values for this actor's properties
	AWall();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(editinstanceonly, BlueprintReadOnly, Category = Patate, meta = (AllowPrivateAccess = "true"))
	float Limiter = 0.f;
};