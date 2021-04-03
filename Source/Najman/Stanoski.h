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

public:
    // Sets default values for this pawn's properties
    AStanoski();

    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:    
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    // Called to bind functionality to input
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    bool isHit;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    bool isSayingHello;

private:
    FTimerHandle handle;
    FTimerHandle sayHelloTimerHandle;
    FTimerHandle sayHelloTriggerTimerHandle;

    TFunction<void(void)> timerCallback();

    ANajmanPlayer* marcinPlayer;

    void teleport();

    TArray<AActor*> spawnPoints;

    AActor* currentSpawnPoint;
    int currentSpawnPointId;

protected:
    UFUNCTION()
    void sayHello();

    void setupSayHelloTriggerTimer();
};


