// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActor1.h"

// Sets default values
AMyActor1::AMyActor1()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMyActor1::BeginPlay()
{
    Super::BeginPlay();

    // 시작 위치 고정
    SetActorLocation(FVector(0.f, 50.f, 0.f));

    GetWorldTimerManager().SetTimer(
        MoveTimerHandle,
        this,
        &AMyActor1::PerformMoveAndTurn,
        1.0f,   // 1초 간격
        true    // 반복 실행
    );
}

// Called every frame
void AMyActor1::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    FVector Location = GetActorLocation();

    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(
            0, // key (0이면 계속 덮어쓰기)
            0.f, // 시간 (0이면 한 프레임만 표시 → 계속 갱신됨)
            FColor::Green,
            FString::Printf(TEXT("위치: X=%.2f Y=%.2f Z=%.2f"),
                Location.X, Location.Y, Location.Z)
        );
    }
}

void AMyActor1::TriggerEvent()
{
    EventCount++; // 이벤트 횟수 증가

    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(
            -1,
            2.0f,
            FColor::Red,
            TEXT("이벤트 발생!")
        );
    }
}

void AMyActor1::PerformMoveAndTurn()
{
    if (MoveCount >= 10)
    {
        GetWorldTimerManager().ClearTimer(MoveTimerHandle);

        // 최종 리포트 출력
        if (GEngine)
        {
            GEngine->AddOnScreenDebugMessage(
                -1,
                5.0f,
                FColor::Yellow,
                FString::Printf(
                    TEXT("총 거리: %.2f / 총 이벤트 발생 횟수: %d"),
                    TotalDistance,
                    EventCount
                )
            );
        }

        return;
    }

    float RandomDistance = FMath::RandRange(100.f, 300.f);
    float RandomAngle = FMath::RandRange(-90.f, 90.f);

    Move(RandomDistance);
    Turn(RandomAngle);

    // 50% 확률 이벤트
    if (FMath::FRand() < 0.5f)
    {
        TriggerEvent();
    }
}

void AMyActor1::Move(float Distance)
{
    FVector StartLocation = GetActorLocation();

    FVector Forward = GetActorForwardVector();
    FVector NewLocation = StartLocation + (Forward * Distance);

    SetActorLocation(NewLocation);

    // 이동 거리 누적
    float MoveDist = FVector::Dist(StartLocation, NewLocation);
    TotalDistance += MoveDist;

    MoveCount++;

    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(
            -1,
            2.0f,
            FColor::Green,
            FString::Printf(
                TEXT("움직인 횟수: %d / 거리: %.2f"),
                MoveCount,
                MoveDist
            )
        );
    }
}

void AMyActor1::Turn(float Angle)
{
    FRotator CurrentRotation = GetActorRotation();

    FRotator NewRotation = CurrentRotation;
    NewRotation.Yaw += Angle;

    SetActorRotation(NewRotation);
}

