// Copyright Epic Games, Inc. All Rights Reserved.

#include "EndlessRunnerCharacter.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"


AEndlessRunnerCharacter::AEndlessRunnerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	USceneComponent* TransformComponent = CreateDefaultSubobject<USceneComponent>(TEXT("TransformComponent"));
	RootComponent = TransformComponent;

	PlayerMesh = CreateDefaultSubobject<UStaticMeshComponent>("PlayerMesh");

	if (static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMesh(TEXT("/Engine/BasicShapes/Cube")); CubeMesh.
		Succeeded())
	{
		PlayerMesh->SetStaticMesh(CubeMesh.Object);
	}

	PlayerMesh->SetRelativeScale3D(FVector(1.f, 1.f, 2.f));
	PlayerMesh->SetupAttachment(TransformComponent);

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = JumpHeight;
	GetCharacterMovement()->AirControl = 0.2f;
}

void AEndlessRunnerCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();
}

void AEndlessRunnerCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	const FVector2D Input = Movementinput.GetSafeNormal();
	const FVector Direction = FVector(Input.Y, Input.X, 0.f);
	const float Speed = MovementSpeed * Input.Size();
	AddMovementInput(Direction, Speed);

	if (!bIsJumping && GetVelocity().Z > 0.f)
	{
		bIsJumping = true;
	}
}


//////////////////////////////////////////////////////////////////////////
// Input

void AEndlessRunnerCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	PlayerInputComponent->BindAxis("MoveRight", this, &AEndlessRunnerCharacter::MoveRight);
	PlayerInputComponent->BindAxis("MoveUp", this, &AEndlessRunnerCharacter::MoveUp);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AEndlessRunnerCharacter::Jump);
}

void AEndlessRunnerCharacter::MoveRight(float value)
{
	Movementinput.Y = value;
}

void AEndlessRunnerCharacter::MoveUp(float value)
{
	Movementinput.X = value;
}

void AEndlessRunnerCharacter::JumpPressed()
{
	if (bIsJumping)
	{
		bIsJumping = true;
		FVector JumpImpulse(0.f, 0.f, JumpHeight);
		LaunchCharacter(JumpImpulse, false, true);
	}

	bJumpPressed = true;
	bIsJumping = true;
}
