#include "EndlessRunnerGameMode.h"

#include "EndlessRunnerCharacter.h"
#include "EngineUtils.h"
#include "EnhancedInputSubsystems.h"
#include "ERPlayerController.h"
#include "ER_Factory.h"
#include "GameCameraActor.h"
#include "LifeBox.h"
#include "Platform.h"
#include "SaveSystem.h"
#include "Components/TextRenderComponent.h"
#include "Engine/TextRenderActor.h"
#include "Engine/World.h"
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

	Player1Spawned = GetWorld()->SpawnActor<AEndlessRunnerCharacter>(BPEndlessCharacter, P1SpawnLocation, SpawnRotation,
	                                                                 SpawnParameters);

	Player2Spawned = GetWorld()->SpawnActor<AEndlessRunnerCharacter>(BPEndlessCharacter, P2SpawnLocation, SpawnRotation,
	                                                                 SpawnParameters);

	if (Player1Spawned && Player2Spawned)
	{
		Player1Spawned->SetLaneIndex(0);
		Player2Spawned->SetLaneIndex(2);


		const TObjectPtr<AERPlayerController> player1Controller = GetWorld()->SpawnActor<AERPlayerController>(
			ERPlayerControllerBP, FVector::ZeroVector, SpawnRotation, SpawnParameters);

		const TObjectPtr<AERPlayerController> player2Controller = GetWorld()->SpawnActor<AERPlayerController>(
			ERPlayerControllerBP, FVector::ZeroVector, SpawnRotation, SpawnParameters);

		if (player1Controller && player2Controller)
		{
			player1Controller->Possess(Player1Spawned);
			if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<
				UEnhancedInputLocalPlayerSubsystem>(player1Controller->GetLocalPlayer()))
			{
				Subsystem->AddMappingContext(player1Controller->MappingContext, 0);
				UE_LOG(LogTemp, Warning, TEXT("Sub System"))
			}
			player2Controller->Possess(Player2Spawned);
			if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<
				UEnhancedInputLocalPlayerSubsystem>(player2Controller->GetLocalPlayer()))
			{
				Subsystem->AddMappingContext(player2Controller->MappingContext, 0);
				UE_LOG(LogTemp, Warning, TEXT("Sub System"))
			}
		}
	}
}

void AEndlessRunnerGameMode::SpawnFactory()
{
	const FActorSpawnParameters SpawnParams;
	PlatformFactory = GetWorld()->SpawnActor<AER_Factory>(AER_Factory::StaticClass(), FVector::ZeroVector,
	                                                      FRotator::ZeroRotator, SpawnParams);
	PlatformFactory->ERGameMode = this;
}

void AEndlessRunnerGameMode::SpawnLives()
{
	const FActorSpawnParameters SpawnParams;
	LivesBoxes.Add(GetWorld()->SpawnActor<ALifeBox>(ALifeBox::StaticClass(), FVector(400, 1060, 140),
	                                                FRotator::ZeroRotator, SpawnParams));
	LivesBoxes.Add(GetWorld()->SpawnActor<ALifeBox>(ALifeBox::StaticClass(), FVector(400, 1170, 140),
	                                                FRotator::ZeroRotator, SpawnParams));
	LivesBoxes.Add(GetWorld()->SpawnActor<ALifeBox>(ALifeBox::StaticClass(), FVector(400, 1280, 140),
	                                                FRotator::ZeroRotator, SpawnParams));
}

void AEndlessRunnerGameMode::UpdateHighScoreUI() const
{
	if (const TActorIterator<ATextRenderActor> ActorIterator(GetWorld()); ActorIterator)
	{
		const ATextRenderActor* TextRenderActor = *ActorIterator;
		const FText HighScoreText = FText::FromString(FString::Printf(TEXT("HighScore: %d"), USaveSystem::LoadScore()));
		TextRenderActor->GetTextRender()->SetText(HighScoreText);
	}
}

void AEndlessRunnerGameMode::BeginPlay()
{
	Super::BeginPlay();

	SetupCamera();
	SpawnPlayers();
	SpawnFactory();
	SpawnLives();
	UpdateHighScoreUI();
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
	LivesBoxes[LivesLeft - 1]->StaticMesh->SetVisibility(false);
	LivesLeft--;

	if (LivesLeft <= 0)
	{
		PlatformFactory->RemoveAll();
		PlatformFactory->Stop();
		if (SessionScore > USaveSystem::LoadScore())
		{
			USaveSystem::SaveScore(SessionScore);
			UpdateHighScoreUI();
		}
	}
}

void AEndlessRunnerGameMode::ParryAttempt(int LaneIndex) const
{
	if (!PlatformFactory->TryParry(LaneIndex))
	{
		return;
	}

	PlatformFactory->RemoveAll();
}

bool AEndlessRunnerGameMode::CheckCollision(const APlatform* Platform) const
{
	if (Player1Spawned->LaneIndex != Platform->LaneIndex && Player2Spawned->LaneIndex != Platform->LaneIndex)
	{
		return false;
	}

	if (Player1Spawned->LaneIndex == Platform->LaneIndex)
	{
		// DEATH
		UE_LOG(LogTemp, Display, TEXT("Player1 Death"))
		return true;
	}

	if (Player2Spawned->LaneIndex == Platform->LaneIndex)
	{
		// DEATH
		UE_LOG(LogTemp, Display, TEXT("Player2 Death"))
		return true;
	}
	return false;
}
