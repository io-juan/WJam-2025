// Fill out your copyright notice in the Description page of Project Settings.


#pragma once

#include "Pescado.h"
#include "Components/AudioComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/StaticMeshComponent.h"
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

	MeshPescado = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MeshPescado"));
	RootComponent = MeshPescado;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(MeshPescado);

	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("Audio"));
	AudioComponent->SetupAttachment(MeshPescado);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(SpringArm, FName("Socket"));

}

// Called when the game starts or when spawned
void APescado::BeginPlay()
{
	Super::BeginPlay();
	MeshPescado->SetPhysicsMaxAngularVelocityInRadians(MaxAngularVel, false, NAME_None);
}

// Called every frame
void APescado::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);



	// Apply Torque
	if (!CachedMoveInput.IsNearlyZero())
	{
		FVector Direction = FVector(CachedMoveInput.X, CachedMoveInput.Y, 0.f).GetSafeNormal();
		FVector Torque = Direction * RollStrength;

		// Convert to local space
		FVector LocalTorque = MeshPescado->GetComponentTransform().InverseTransformVectorNoScale(Torque);
		LocalTorque.X *= XTorqueMultiplier;
		LocalTorque.Y *= YTorqueMultiplier;
		LocalTorque.Z = 0.f;

		// Back to world space
		FVector ScaledTorque = MeshPescado->GetComponentTransform().TransformVectorNoScale(LocalTorque);
		MeshPescado->AddTorqueInRadians(ScaledTorque, FName("Bone"), false);

		UE_LOG(LogTemp, Display, TEXT("Torque: %s"), *ScaledTorque.ToString());

		int HeightMultiplier = FMath::Clamp(GetActorLocation().Z / 100,0,100);
		FVector ImpulseDir = FVector(CachedMoveInput.Y, -CachedMoveInput.X, 0);

		MeshPescado->AddImpulse(ImpulseDir * ImpulseHorizontal * HeightMultiplier);

	}

	// Apply Jump/Impulse
	if (CachedJumpInput > 0.1f && bCanJump)
	{
		FVector Impulse = FVector(0, 0, CachedJumpInput * JumpStrength);
		MeshPescado->AddImpulse(Impulse, NAME_None, true);

		AudioComponent->Play();

		UE_LOG(LogTemp, Display, TEXT("Jump Impulse Applied: %s"), *Impulse.ToString());

		bCanJump = false;
		GetWorld()->GetTimerManager().SetTimer(JumpCooldownTimer, this, &APescado::ResetJumpCooldown, JumpCooldown, false);

		CachedJumpInput = 0.f; // One-shot
	}
}

void APescado::ResetJumpCooldown()
{
	bCanJump = true;
	CachedJumpInput = 0.0f;
}

void APescado::FishMove(const FInputActionValue& Value)
{
	CachedMoveInput = Value.Get<FVector2D>();
}

void APescado::FishJump(const FInputActionValue& Value)
{
	CachedJumpInput = Value.Get<float>();
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

