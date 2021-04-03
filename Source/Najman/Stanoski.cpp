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

    APawn* p = UGameplayStatics::GetPlayerPawn(this, 0);

    if (p)
    {
        marcinPlayer = Cast<ANajmanPlayer, APawn>(p);
    }

    UGameplayStatics::GetAllActorsOfClass(this, AStanoskiBaseSpawnPoint::StaticClass(), spawnPoints);

    currentSpawnPointId = 0;

    currentSpawnPoint = nullptr;

    setupSayHelloTriggerTimer();
}

// Called every frame
void AStanoski::Tick(float DeltaTime)
{
    static int cnt = 0;

    Super::Tick(DeltaTime);

    if (marcinPlayer)
    {
        FVector objToPlayerVect = marcinPlayer->GetActorLocation() - GetActorLocation();
        objToPlayerVect.Z = 0.0;
        objToPlayerVect.Normalize();

        FVector forwardVect = GetActorForwardVector();
        forwardVect.Z = 0.0;

        float angle = FGenericPlatformMath::Acos(FVector::DotProduct(forwardVect, objToPlayerVect));

        if (angle > 0.2)
        {
            AddActorLocalRotation(FRotator(0.0, 2.0, 0.0));
        }

        if (marcinPlayer->isPunching && marcinPlayer->GetDistanceTo(this) < 100.0 && !isHit)
        {
            isHit = true;
            GetWorldTimerManager().SetTimer(handle, 
                [=]() {
                    isHit = false; 
                    teleport();
                },
                0.5, false);
            if (cnt % 30 == 0)
            {
                UE_LOG(LogTemp, Log, TEXT("Hit!!!"));
            }
        }
    }
  
    cnt++;
}

// Called to bind functionality to input
void AStanoski::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AStanoski::teleport()
{
    if (spawnPoints.Num() < 1)
    {
        UE_LOG(LogTemp, Error, TEXT("No spawn points!"));
        return;
    }

    if (currentSpawnPointId >= spawnPoints.Num() - 1)
    {
        currentSpawnPointId = -1;
    }

    for (auto& spawnPoint : spawnPoints)
    {
        AStanoskiBaseSpawnPoint* stanoskiSpawnPoint;
        stanoskiSpawnPoint = Cast<AStanoskiBaseSpawnPoint, AActor>(spawnPoint);
        if (spawnPoint)
        {
            if ((stanoskiSpawnPoint->id) == (currentSpawnPointId + 1))
            {
                this->SetActorLocation(stanoskiSpawnPoint->GetActorLocation());
                currentSpawnPointId += 1;
                return;
            }
        }
    }
}

void AStanoski::sayHello()
{
    if (!isSayingHello)
    {
        isSayingHello = true;
        UE_LOG(LogTemp, Error, TEXT("Say-hello triggered!"));

        GetWorldTimerManager().ClearTimer(sayHelloTimerHandle);

        GetWorldTimerManager().SetTimer(
            sayHelloTimerHandle,
            [=]() { isSayingHello = false; },
            1.5,
            false,
            0.5
        ); 
    }
}

void AStanoski::setupSayHelloTriggerTimer()
{
    GetWorldTimerManager().SetTimer(
        sayHelloTriggerTimerHandle,
        this,
        &AStanoski::sayHello,
        7.0,
        true,
        1.0
    );
}

