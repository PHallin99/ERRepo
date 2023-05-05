#include "EndlessRunnerGameMode.h"
#include "EndlessRunnerCharacter.h"
#include "ERPlayerController.h"
#include "ER_Factory.h"
#include "GameCameraActor.h"
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

	const FVector P1SpawnLocation = FVector(810, 1110, 140);
	const FVector P2SpawnLocation = FVector(810, 1470, 140);
	const FRotator SpawnRotation = FRotator::ZeroRotator;

	Player1 = GetWorld()->SpawnActor<AEndlessRunnerCharacter>(AEndlessRunnerCharacter::StaticClass(), P1SpawnLocation,
	                                                          SpawnRotation, SpawnParameters);

	Player2 = GetWorld()->SpawnActor<AEndlessRunnerCharacter>(AEndlessRunnerCharacter::StaticClass(), P2SpawnLocation,
	                                                          SpawnRotation, SpawnParameters);

	if (Player1 && Player2)
	{
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
	PlatformFactory->Initialize(500.f, 3.f);
}

AEndlessRunnerGameMode::AEndlessRunnerGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(
		TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
