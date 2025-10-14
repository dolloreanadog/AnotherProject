// Fill out your copyright notice in the Description page of Project Settings.


#include "Wagon_Character.h"

// Sets default values
AWagon_Character::AWagon_Character()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AWagon_Character::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWagon_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	/*
	MoveForward(moveSpeed * DeltaTime); // Move constantly
	Rotate(rotationSpeed * DeltaTime); // Rotate based on rotation speed and delta time
	*/
}

// Called to bind functionality to input
void AWagon_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Bind movement functions to input axes
	PlayerInputComponent->BindAxis("MoveForward", this, &AWagon_Character::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AWagon_Character::MoveRight);
	// Bind rotation function to input axis
	PlayerInputComponent->BindAxis("Rotate", this, &AWagon_Character::CameraRotate);
	// Bind jump action to input action
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AWagon_Character::Jump);

}

void AWagon_Character::MoveForward(float value)
{
	AddMovementInput(GetActorForwardVector(), value * moveSpeed);
}

void AWagon_Character::MoveRight(float value)
{
	AddMovementInput(GetActorRightVector(), value * moveSpeed);
}

void AWagon_Character::CameraRotate(float value)
{
	AddControllerYawInput(value);
}

void AWagon_Character::StartJump()
{
	Jump();
}