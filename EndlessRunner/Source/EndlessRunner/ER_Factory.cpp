#include "ER_Factory.h"
#include "Platform.h"

AER_Factory::AER_Factory()
{
	PrimaryActorTick.bCanEverTick = true;
	SpawnLocations.Add(FVector(3950, 800, 140));
	SpawnLocations.Add(FVector(3950, 1200, 140));
	SpawnLocations.Add(FVector(3950, 1600, 140));
	PlatformMovementSpeed = 500.f;
	PlatformSpawnInterval = 3.f;
}

void AER_Factory::Stop()
{
	GetWorldTimerManager().ClearTimer(PlatformSpawnTimer);
}

void AER_Factory::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(PlatformSpawnTimer, this, &AER_Factory::SpawnPlatform, PlatformSpawnInterval, true);
}

void AER_Factory::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AER_Factory::RemoveAll()
{
	for (auto Platform : SpawnedPlatforms)
	{
		if (Platform != nullptr)
		{
			Platform->Destroy();
		}
	}
	SpawnedPlatforms.Empty();
	PlatformMovementSpeed = 500.f;
	PlatformSpawnInterval = 3.f;
	GetWorldTimerManager().SetTimer(PlatformSpawnTimer, this, &AER_Factory::SpawnPlatform, PlatformSpawnInterval, true);
}

void AER_Factory::SpawnPlatform()
{
	const int Index = FMath::RandRange(0, 2);
	const FVector SpawnLocation = SpawnLocations[Index];
	const FRotator SpawnRotation(GetActorRotation());
	const FActorSpawnParameters SpawnParams;
	const bool UsePlatformScale = FMath::RandBool();
	const FVector SpawnScale = UsePlatformScale ? FVector(1.f, 4.f, 1.f) : FVector(1.f, 4.f, 2.75f);

	if (AActor* SpawnedActor = GetWorld()->SpawnActor<APlatform>(APlatform::StaticClass(), SpawnLocation, SpawnRotation,
	                                                             SpawnParams))
	{
		APlatform* SpawnedPlatform = Cast<APlatform>(SpawnedActor);
		SpawnedPlatform->SetActorScale3D(SpawnScale);
		SpawnedPlatform->MovementDirection = FVector(-1.f, 0.f, 0.f);
		SpawnedPlatform->MovementSpeed = PlatformMovementSpeed;
		SpawnedPlatform->EndlessRunnerGameMode = ERGameMode;
		SpawnedPlatform->SetLaneIndex(Index);
		SpawnedPlatforms.Add(SpawnedPlatform);
		if (!ERGameMode)
		{
			SpawnedPlatform->Destroy();
		}
	}

	PlatformMovementSpeed *= 1.05f;
	PlatformSpawnInterval *= 0.95f;
	GetWorldTimerManager().SetTimer(PlatformSpawnTimer, this, &AER_Factory::SpawnPlatform, PlatformSpawnInterval, true);
}
