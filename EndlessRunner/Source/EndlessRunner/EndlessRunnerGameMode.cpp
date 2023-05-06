#include "EndlessRunnerGameMode.h"
#include "EndlessRunnerCharacter.h"
#include "ERPlayerController.h"
#include "ER_Factory.h"
#include "GameCameraActor.h"
#include "Platform.h"
#include "SaveSystem.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"

void AEndlessRunnerGameMode::SetupCamera() const
{
	AGameCameraActor* CameraActor = Cast<AGameCameraActor>(
		UGameplayStatics::GetActorOfClass(this, AGameCameraActor::StaticClass()));

	if (APlayerController* FirstPlayerController = GetWorld()->GetFirstPlayerController())
	{
		FirstPlayerController->SetViewTarget(CameraActor);
	}

	CameraActor->SetActorLocation(FVector(90.f, 1160.f, 590.f));
}

void AEndlessRunnerGameMode::SpawnPlayers()
{
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	const FVector P1SpawnLocation = FVector(810, 800, 140);
	const FVector P2SpawnLocation = FVector(810, 1600, 140);
	const FRotator SpawnRotation = FRotator::ZeroRotator;

	Player1 = GetWorld()->SpawnActor<AEndlessRunnerCharacter>(AEndlessRunnerCharacter::StaticClass(), P1SpawnLocation,
	                                                          SpawnRotation, SpawnParameters);

	Player2 = GetWorld()->SpawnActor<AEndlessRunnerCharacter>(AEndlessRunnerCharacter::StaticClass(), P2SpawnLocation,
	                                                          SpawnRotation, SpawnParameters);

	if (Player1 && Player2)
	{
		Player1->SetLaneIndex(0);
		Player2->SetLaneIndex(2);

		const TObjectPtr<AERPlayerController> player1Controller = GetWorld()->SpawnActor<AERPlayerController>(
			AERPlayerController::StaticClass(), FVector::ZeroVector, SpawnRotation, SpawnParameters);

		const TObjectPtr<AERPlayerController> player2Controller = GetWorld()->SpawnActor<AERPlayerController>(
			AERPlayerController::StaticClass(), FVector::ZeroVector, SpawnRotation, SpawnParameters);

		if (player1Controller && player2Controller)
		{
			player1Controller->Possess(Player1);
			player2Controller->Possess(Player2);
		}
	}
}

void AEndlessRunnerGameMode::BeginPlay()
{
	Super::BeginPlay();
	SetupCamera();
	SpawnPlayers();

	const FActorSpawnParameters SpawnParams;
	PlatformFactory = GetWorld()->SpawnActor<AER_Factory>(AER_Factory::StaticClass(), FVector::ZeroVector,
	                                                      FRotator::ZeroRotator, SpawnParams);
	PlatformFactory->ERGameMode = this;
}

AEndlessRunnerGameMode::AEndlessRunnerGameMode()
{
	LivesLeft = 3;
}

void AEndlessRunnerGameMode::AddScore(int Score)
{
	SessionScore += Score;
}

void AEndlessRunnerGameMode::RemoveLife()
{
	PlatformFactory->RemoveAll();
	LivesLeft--;
	if (LivesLeft <= 0)
	{
		// SAVE SESSION SCORE -> RESET SESSION SCORE INT
		PlatformFactory->RemoveAll();
		PlatformFactory->Stop();
		if (SessionScore > USaveSystem::LoadScore())
		{
			USaveSystem::SaveScore(SessionScore);
		}
	}
}

bool AEndlessRunnerGameMode::CheckCollision(const APlatform* Platform) const
{
	if (Player1->LaneIndex != Platform->LaneIndex && Player2->LaneIndex != Platform->LaneIndex)
	{
		return false;
	}

	if (Player1->LaneIndex == Platform->LaneIndex)
	{
		// DEATH
		UE_LOG(LogTemp, Display, TEXT("Player1 Death"))
		return true;
	}

	if (Player2->LaneIndex == Platform->LaneIndex)
	{
		// DEATH
		UE_LOG(LogTemp, Display, TEXT("Player2 Death"))
		return true;
	}
	return false;
}
