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

	float _originalMoveSpeed;
	float _originalRotationSpeed;

public:
	// Sets default values for this character's properties
	AWagon_Character();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Handle damage
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	// Handle death
	virtual void Die();

public:	

	UPROPERTY(EditAnywhere, Category="Health")
	float MaxHealth = 100.0f;
	UPROPERTY(VisibleAnywhere, Category = "Health") //VisibleAnywhere
	float _currentHealth;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Status Effects")
	bool _isStunned = false;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveForward(float value);
	void MoveRight(float value);
	void CameraRotate(float value);
	void StartJump();


	// Stun function
	UFUNCTION(BlueprintCallable, Category = "Status Effects") // put no ; here, it needs to be connected to the function body
	void Stun(UPARAM(DisplayName="Duration") float duration);
	//float duration
	//UPARAM(DisplayName="X (Roll)") float Roll,

	// green underline is ok, but sometimes it shows error for some unkown reason because of typical Unreal Engine issues, Do a quick ctrl+x and ctrl+v to fix it if it shows error, or wait
	// These delegates can be used in Blueprints to trigger effects
	// Declare stun delegate, this 
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStunDelegate, float, Duration);

	// So we can use it in Blueprints, can now be broadcasted in C++ and used in Blueprints
	UPROPERTY(BlueprintAssignable);
	FOnStunDelegate OnStun;

	// Also, for the stun end delegate, use:
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnStunEndDelegate);

	// Declare stun end delegate, can now be broadcasted in C++ and used in Blueprints
	UPROPERTY(BlueprintAssignable);
	FOnStunEndDelegate OnStunEnd;

	// Also, for the death delegate, use:
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeathDelegate);

	// Declare death delegate, can now be broadcasted in C++ and used in Blueprints
	UPROPERTY(BlueprintAssignable);
	FOnDeathDelegate OnDeath;
};
