// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "NajmanPlayer.h"
#include "StanoskiBaseSpawnPoint.h"
#include "Stanoski.generated.h"

UCLASS()
class NAJMAN_API AStanoski : public APawn
{
    GENERATED_BODY()

private:
    FTimerHandle TimerHandle;
    FTimerHandle SayHelloTimerHandle;
    FTimerHandle SayHelloTriggerTimerHandle;

    TFunction<void(void)> TimerCallback();

    ANajmanPlayer* MarcinPlayer;

    void Teleport();

    TArray<AActor*> SpawnPoints;

    AActor* CurrentSpawnPoint;
    int CurrentSpawnPointId;

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

    UFUNCTION()
        void SayHello();

    void SetupSayHelloTriggerTimer();

public:
    // Sets default values for this pawn's properties
    AStanoski();

    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

    // Called every frame
    virtual void Tick(float DeltaTime) override;

    // Called to bind functionality to input
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    bool IsHit;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    bool IsSayingHello;
};


