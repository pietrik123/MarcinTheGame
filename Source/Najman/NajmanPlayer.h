// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "NajmanPlayer.generated.h"

UCLASS()
class NAJMAN_API ANajmanPlayer : public APawn
{
    GENERATED_BODY()

private:
    FTimerHandle PunchTimer;

    void Punch();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:
    // Sets default values for this pawn's properties
    ANajmanPlayer();

    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

    // Called every frame
    virtual void Tick(float DeltaTime) override;

    // Called to bind functionality to input
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    bool IsPunching;
};
