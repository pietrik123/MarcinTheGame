// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "StanoskiBaseSpawnPoint.generated.h"

UCLASS()
class NAJMAN_API AStanoskiBaseSpawnPoint : public AActor
{
    GENERATED_BODY()
    
public:    
    // Sets default values for this actor's properties
    AStanoskiBaseSpawnPoint();

    // Called every frame
    virtual void Tick(float DeltaTime) override;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    int Id;

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;
};
