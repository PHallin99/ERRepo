// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "EndlessRunnerCharacter.generated.h"


UCLASS(config=Game)
class AEndlessRunnerCharacter : public ACharacter
{
	GENERATED_BODY()
	TObjectPtr<UStaticMeshComponent> PlayerMesh;

	void MoveRight(float value);
	void MoveUp(float value);
	void JumpPressed();
	void JumpReleased();

public:
	AEndlessRunnerCharacter();

protected:
	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// To add mapping context
	virtual void BeginPlay();

public:
	virtual void Tick(float DeltaSeconds) override;

private:
	float MovementSpeed = 200.0f;
	FVector2D Movementinput;
	bool bJumpPressed;
	bool bIsJumping;
	float JumpHeight = 300.0f;
};
