// Fill out your copyright notice in the Description page of Project Settings.


#include "NajmanPlayer.h"
#include "TimerManager.h"
#include "Components/InputComponent.h"

// Sets default values
ANajmanPlayer::ANajmanPlayer()
{
     // Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

}

void ANajmanPlayer::EndPlay(const EEndPlayReason::Type EndPlayReason)
{

    GetWorldTimerManager().ClearAllTimersForObject(this);

    Super::EndPlay(EndPlayReason);
}

// Called when the game starts or when spawned
void ANajmanPlayer::BeginPlay()
{
    Super::BeginPlay();
    
}

// Called every frame
void ANajmanPlayer::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    static int Cnt = 0;

    if (Cnt % 20 == 0)
    {
        UE_LOG(LogTemp, Log, TEXT("Is punching: %d"), (int)IsPunching);
    }

    Cnt++;
}

// Called to bind functionality to input
void ANajmanPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAction("Punch", IE_Pressed, this, &ANajmanPlayer::Punch);
}

void ANajmanPlayer::Punch()
{
    if (!IsPunching)
    {
        GetWorldTimerManager().ClearTimer(PunchTimer);

        IsPunching = true;
        GetWorldTimerManager().SetTimer(
            PunchTimer,
            [=]() { IsPunching = false; },
            0.5,
            false
        );
    }
}

