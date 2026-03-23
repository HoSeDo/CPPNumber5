// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyActor1.generated.h"

UCLASS()
class CPPNUMBER5_API AMyActor1 : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyActor1();
	void Move(float Distance);
	void Turn(float Angle);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void PerformMoveAndTurn();
	void TriggerEvent();

private:
	int32 MoveCount = 0;
	int32 EventCount = 0;     // ÀÌº¥Æ® È½¼ö

	float TotalDistance = 0.f; // ÃÑ ÀÌµ¿ °Å¸®

	FTimerHandle MoveTimerHandle;

};
