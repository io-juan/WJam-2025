// Fill out your copyright notice in the Description page of Project Settings.


#pragma once

#include "Pescado.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "InputActionValue.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

// Sets default values
APescado::APescado()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshPescado = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshPescado"));
	RootComponent = MeshPescado;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(MeshPescado);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(SpringArm, FName("Socket"));

}

// Called when the game starts or when spawned
void APescado::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APescado::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APescado::FishMove(const FInputActionValue& Value)
{
	FVector2D Input = Value.Get<FVector2D>();

	FVector Torque = FVector(Input.X * 5, Input.Y, 0) * RollStrength;
	MeshPescado->AddTorqueInRadians(Torque, NAME_None, false);

	UE_LOG(LogTemp, Display, TEXT("Entro"));
}

void APescado::FishJump(const FInputActionValue& Value)
{

}

// Called to bind functionality to input
void APescado::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInput->BindAction(IA_Move, ETriggerEvent::Triggered, this, &APescado::FishMove);
		EnhancedInput->BindAction(IA_Jump, ETriggerEvent::Triggered, this, &APescado::FishJump);
	}

}

