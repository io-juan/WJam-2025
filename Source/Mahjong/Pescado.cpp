// Fill out your copyright notice in the Description page of Project Settings.


#include "Pescado.h"

// Sets default values
APescado::APescado()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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

// Called to bind functionality to input
void APescado::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

