// Copyright Epic Games, Inc. All Rights Reserved.

#include "EndlessRunnerCharacter.h"

#include "Components/InputComponent.h"


void AEndlessRunnerCharacter::MoveLeft()
{
	// Move player left one lane
	if (LaneIndex == 0)
	{
		return;
	}
	LaneIndex--;
	SetActorLocation(LanePositions[LaneIndex]);
}

void AEndlessRunnerCharacter::MoveRight()
{
	// Move player right one lane
	if (LaneIndex == 2)
	{
		return;
	}
	LaneIndex++;
	SetActorLocation(LanePositions[LaneIndex]);
}

void AEndlessRunnerCharacter::OnParry()
{
	// Parry a platform if its close enough to the player - nuke the map of platforms and enemies
}

void AEndlessRunnerCharacter::SetupCharacterActor()
{
	USceneComponent* TransformComponent = CreateDefaultSubobject<USceneComponent>(TEXT("TransformComponent"));
	RootComponent = TransformComponent;

	PlayerMesh = CreateDefaultSubobject<UStaticMeshComponent>("PlayerMesh");
	static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMesh(TEXT("/Engine/BasicShapes/Cube"));
	if (CubeMesh.Succeeded())
	{
		PlayerMesh->SetStaticMesh(CubeMesh.Object);
	}

	PlayerMesh->SetRelativeScale3D(FVector(1.f, 1.f, 2.f));
	PlayerMesh->SetupAttachment(TransformComponent);

	PlayerInput = CreateDefaultSubobject<UPlayerInput>(TEXT("PlayerInput"));
}

void AEndlessRunnerCharacter::SetLanePositions()
{
	LanePositions.Add(FVector(3950, 800, 140));
	LanePositions.Add(FVector(3950, 1200, 140));
	LanePositions.Add(FVector(3950, 1600, 140));
}

AEndlessRunnerCharacter::AEndlessRunnerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	SetupCharacterActor();
}

void AEndlessRunnerCharacter::SetLaneIndex(int Index)
{
	LaneIndex = Index;
}

void AEndlessRunnerCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();
	SetLanePositions();
	// SetupPlayerInputComponent(GetController()->InputComponent);
}

void AEndlessRunnerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Left", IE_Pressed, this, &AEndlessRunnerCharacter::MoveLeft);
	PlayerInputComponent->BindAction("Right", IE_Pressed, this, &AEndlessRunnerCharacter::MoveRight);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AEndlessRunnerCharacter::OnParry);
}

void AEndlessRunnerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
