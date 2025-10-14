// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "Wagon_Door.h"
#include "Wagon_Character.h"
#include "Wagon_Key.generated.h"


/**
 * 
 */
UCLASS()
class ANOTHERPROJECT_API AWagon_Key : public ATriggerBox
{
	GENERATED_BODY()
	
public:
	AWagon_Key();
	
	UPROPERTY(EditAnywhere)
	AWagon_Door* Door; // Reference to the door that this key will unlock

	UFUNCTION()
	bool IsPlayerCharacter(class AActor* Actor); // Function to check if the overlapping actor is the player character
	UFUNCTION()
	void TryOpenDoor(class AActor* OverlappingActor, class AActor* OtherActor); // Function to attempt to open the door when the player overlaps the key
	void OpenDoor(); // Function to open the door
};
