// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "GameFramework/Pawn.h"
#include "Pescado.generated.h"

UCLASS()
class MAHJONG_API APescado : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APescado();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Methods
	void FishMove(const FInputActionValue& Value);

	void FishJump(const FInputActionValue& Value);

	void ResetJumpCooldown();

	//Variables Core

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Health = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int ImpulseHorizontal = 5;

	FVector2D CachedMoveInput = FVector2D::ZeroVector;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float CachedJumpInput = 0.0f;

	bool bCanJump = true;

	UPROPERTY(EditAnywhere, Category = "Jump")
	float JumpCooldown = 3.0f;

	FTimerHandle JumpCooldownTimer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int RollStrength = 2000;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int JumpStrength = 200;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MaxAngularVel = 10000;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float YTorqueMultiplier = 0.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float XTorqueMultiplier = 5.0f;

	// Components
	UPROPERTY(VisibleAnywhere)
	class USkeletalMeshComponent* MeshPescado;

	UPROPERTY(VisibleAnywhere)
	class UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere)
	class USpringArmComponent* SpringArm;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UInputMappingContext* MappingContextMain;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UInputAction* IA_Move;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UInputAction* IA_Jump;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
