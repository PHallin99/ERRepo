// Copyright Epic Games, Inc. All Rights Reserved.

#include "EndlessRunnerCharacter.h"
#include "Components/InputComponent.h"


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
}

void AEndlessRunnerCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();
}

void AEndlessRunnerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
