// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MyPlayer3.generated.h"

UCLASS()
class NAJMAN_API AMyPlayer3 : public APawn
{
    GENERATED_BODY()

public:
    // Sets default values for this pawn's properties
    AMyPlayer3();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:    
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    // Called to bind functionality to input
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    UFUNCTION()
    void moveUp(float value);
    
    UFUNCTION()
    void moveRight(float value);

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    UStaticMeshComponent* mesh;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    USpringArmComponent* springArm;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    UCameraComponent* camera;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    float movementForce;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float JumpImpulse;

    UFUNCTION(BlueprintImplementableEvent)
    void jump();
};
