// Fill out your copyright notice in the Description page of Project Settings.


#include "Wagon_Key.h"

AWagon_Key::AWagon_Key()
{
	UE_LOG(LogTemp, Warning, TEXT("Wagon_Key initialized."));
	OnActorBeginOverlap.AddDynamic(this, &AWagon_Key::TryOpenDoor);
}

bool AWagon_Key::IsPlayerCharacter(AActor* Actor)
{
	return Actor && Actor->IsA<AWagon_Character>();
}

void AWagon_Key::TryOpenDoor(AActor* OverlappingActor, AActor* OtherActor)
{
	UE_LOG(LogTemp, Warning, TEXT("Overlap detected with actor: %s"), *OtherActor->GetName());
	if (IsPlayerCharacter(OtherActor))
	{
		UE_LOG(LogTemp, Warning, TEXT("Player overlapped with the key."));
		OpenDoor();
		Destroy(); // Destroy the key after use
	}
}

void AWagon_Key::OpenDoor()
{
	UE_LOG(LogTemp, Warning, TEXT("Attempting to open the door..."));
	if (Door)
	{
		// Destroy attached actors first
		TArray<AActor*> AttachedActors;
		Door->GetAttachedActors(AttachedActors);
		for (AActor* AttachedActor : AttachedActors)
		{
			if (AttachedActor)
			{
				AttachedActor->Destroy();
			}
		}

		Door->Destroy(); // Simple way to "open" the door by destroying it

		// Destroy attached actors first
		TArray<AActor*> KeyAttachedActors;
		this->GetAttachedActors(KeyAttachedActors);
		for (AActor* AttachedActor : KeyAttachedActors)
		{
			if (AttachedActor)
			{
				AttachedActor->Destroy();
			}
		}

		// then destroy the key itself
		this->Destroy(); // Destroy the key after use
	}
}