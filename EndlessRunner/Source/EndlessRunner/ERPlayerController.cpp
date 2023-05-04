// Fill out your copyright notice in the Description page of Project Settings.


#include "ERPlayerController.h"


// Sets default values
AERPlayerController::AERPlayerController()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AERPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
}

void AERPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("Left", IE_Pressed, this, &AERPlayerController::OnLeftPressed);
	InputComponent->BindAction("LeftA", IE_Pressed, this, &AERPlayerController::OnLeftAPressed);
	InputComponent->BindAction("Right", IE_Pressed, this, &AERPlayerController::OnRightPressed);
	InputComponent->BindAction("RightD", IE_Pressed, this, &AERPlayerController::OnRightDPressed);
	InputComponent->BindAction("Jump", IE_Pressed, this, &AERPlayerController::OnJumpPressed);
	InputComponent->BindAction("JumpW", IE_Pressed, this, &AERPlayerController::OnJumpWPressed);
}

void AERPlayerController::OnLeftPressed()
{
	// RIGHT LEFTING
}

void AERPlayerController::OnLeftAPressed()
{
	// LEFT LEFTING
}

void AERPlayerController::OnRightPressed()
{
	// RIGHT RIGHTING
}

void AERPlayerController::OnRightDPressed()
{
	// LEFT RIGHTING
}

void AERPlayerController::OnJumpPressed()
{
	// RIGHT JUMPAGE
}

void AERPlayerController::OnJumpWPressed()
{
	// LEFT JUMPAGE
}

// Called every frame
void AERPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

