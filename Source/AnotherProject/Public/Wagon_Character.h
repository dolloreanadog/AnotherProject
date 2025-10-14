// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Wagon_Character.generated.h"

UCLASS()
class ANOTHERPROJECT_API AWagon_Character : public ACharacter
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, Category="Movement")
	float moveSpeed = 100.0f;
	UPROPERTY(EditAnywhere, Category = "Movement")
	float rotationSpeed = 50.0f;

public:
	// Sets default values for this character's properties
	AWagon_Character();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveForward(float value);
	void MoveRight(float value);
	void CameraRotate(float value);
	void StartJump();
};
