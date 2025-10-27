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
	_currentHealth = MaxHealth;
}

// <summary>
// Handle damage
// </summary>
// <param name="DamageAmount">The amount of damage to apply</param>
// <param name="DamageEvent">The damage event</param>
// <param name="EventInstigator">The controller that instigated the damage</param>
// <param name="DamageCauser">The actor that caused the damage</param>
float AWagon_Character::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	// Apply damage
	_currentHealth -= DamageAmount;

	UE_LOG(LogTemp, Log, TEXT("Character took %f damage, current health: %f"), DamageAmount, _currentHealth);

	// Check for death
	if (_currentHealth <= 0.0f)
	{
		Die();
	}

	return DamageAmount;
}

void AWagon_Character::Die()
{
	// This and we need inplement animations and effects
	moveSpeed = 0.0f; // Stop movement
	rotationSpeed = 0.0f; // Stop rotation

	OnDeath.Broadcast();
}

/*
void AWagon_Character::OnStun()
{
	// Implementation can be done in Blueprint
}

void AWagon_Character::OnDeath()
{
	// Implementation can be done in Blueprint
}
*/

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

void AWagon_Character::Stun(float duration)
{
	// Disable movement and rotation
	moveSpeed = 0.0f;
	rotationSpeed = 0.0f;
	_isStunned = true;

	OnStun.Broadcast(duration);
	// Set a timer to re-enable movement and rotation after the stun duration
	FTimerHandle UnusedHandle;
	GetWorldTimerManager().SetTimer(UnusedHandle, [this]()
		{
			// Re-enable movement and rotation
			moveSpeed = _originalMoveSpeed; // Reset to default or previous speed
			rotationSpeed = _originalRotationSpeed; // Reset to default or previous speed
			_isStunned = false;
			OnStunEnd.Broadcast();
		}, duration, false);
}
