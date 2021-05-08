// Fill out your copyright notice in the Description page of Project Settings.


#include "Stanoski.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AStanoski::AStanoski()
{
     // Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

}

void AStanoski::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    UE_LOG(LogTemp, Log, TEXT("Stanoski, end play!!!"));

    GetWorldTimerManager().ClearAllTimersForObject(this);

    Super::EndPlay(EndPlayReason);
}

// Called when the game starts or when spawned
void AStanoski::BeginPlay()
{
    Super::BeginPlay();

    APawn* PlayerPtr = UGameplayStatics::GetPlayerPawn(this, 0);

    if (PlayerPtr)
    {
        MarcinPlayer = Cast<ANajmanPlayer, APawn>(PlayerPtr);
    }

    UGameplayStatics::GetAllActorsOfClass(this, AStanoskiBaseSpawnPoint::StaticClass(), SpawnPoints);

    CurrentSpawnPointId = 0;

    CurrentSpawnPoint = nullptr;

    SetupSayHelloTriggerTimer();
}

// Called every frame
void AStanoski::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (MarcinPlayer)
    {
        FVector ObjToPlayerVect = MarcinPlayer->GetActorLocation() - GetActorLocation();
        ObjToPlayerVect.Z = 0.0;
        ObjToPlayerVect.Normalize();

        FVector ForwardVect = GetActorForwardVector();
        ForwardVect.Z = 0.0;

        float Angle = FGenericPlatformMath::Acos(FVector::DotProduct(ForwardVect, ObjToPlayerVect));

        if (Angle > 0.2)
        {
            AddActorLocalRotation(FRotator(0.0, 2.0, 0.0));
        }

        if (MarcinPlayer->IsPunching && MarcinPlayer->GetDistanceTo(this) < 100.0 && !IsHit)
        {
            IsHit = true;
            GetWorldTimerManager().SetTimer(TimerHandle, 
                [=]() {
                    IsHit = false; 
                    Teleport();
                },
                0.5, false);          
        }
    } 
}

// Called to bind functionality to input
void AStanoski::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AStanoski::Teleport()
{
    if (SpawnPoints.Num() < 1)
    {
        UE_LOG(LogTemp, Error, TEXT("No spawn points!"));
        return;
    }

    if (CurrentSpawnPointId >= SpawnPoints.Num() - 1)
    {
        CurrentSpawnPointId = -1;
    }

    for (auto& spawnPoint : SpawnPoints)
    {
        AStanoskiBaseSpawnPoint* StanoskiSpawnPoint;
        StanoskiSpawnPoint = Cast<AStanoskiBaseSpawnPoint, AActor>(spawnPoint);
        if (spawnPoint)
        {
            if ((StanoskiSpawnPoint->Id) == (CurrentSpawnPointId + 1))
            {
                this->SetActorLocation(StanoskiSpawnPoint->GetActorLocation());
                CurrentSpawnPointId += 1;
                return;
            }
        }
    }
}

void AStanoski::SayHello()
{
    if (!IsSayingHello)
    {
        IsSayingHello = true;
        UE_LOG(LogTemp, Error, TEXT("Say-hello triggered!"));

        GetWorldTimerManager().ClearTimer(SayHelloTimerHandle);

        GetWorldTimerManager().SetTimer(
            SayHelloTimerHandle,
            [=]() { IsSayingHello = false; },
            1.5,
            false,
            0.5
        ); 
    }
}

void AStanoski::SetupSayHelloTriggerTimer()
{
    GetWorldTimerManager().SetTimer(
        SayHelloTriggerTimerHandle,
        this,
        &AStanoski::SayHello,
        7.0,
        true,
        1.0
    );
}

