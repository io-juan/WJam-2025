// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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

	//Variables Core
	int Health = 100;

	// Components
	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* MeshPescado;

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
