// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayer3.h"
#include "Components/InputComponent.h"

// Sets default values
AMyPlayer3::AMyPlayer3()
{
     // Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    mesh = CreateDefaultSubobject<UStaticMeshComponent>("mesh");
    springArm = CreateDefaultSubobject<USpringArmComponent>("springArm");
    camera = CreateDefaultSubobject<UCameraComponent>("camera");

    RootComponent = mesh;
    springArm->SetupAttachment(mesh);
    camera->SetupAttachment(springArm);

    mesh->SetSimulatePhysics(true);
    movementForce = 100000;
}

// Called when the game starts or when spawned
void AMyPlayer3::BeginPlay()
{
    Super::BeginPlay();
    
}

// Called every frame
void AMyPlayer3::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyPlayer3::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAxis("X_axis", this, &AMyPlayer3::moveUp);
    PlayerInputComponent->BindAxis("Y_axis", this, &AMyPlayer3::moveRight);
}

void AMyPlayer3::moveUp(float value)
{
    FVector forceToAdd = FVector(1, 0, 0) * movementForce * value;
    mesh->AddForce(forceToAdd);
}

void AMyPlayer3::moveRight(float value)
{
    FVector forceToAdd = FVector(0, 1, 0) * movementForce * value;
    mesh->AddForce(forceToAdd);
}


