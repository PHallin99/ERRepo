// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "EndlessRunnerCharacter.h"
#include "GameFramework/GameModeBase.h"
#include "EndlessRunnerGameMode.generated.h"

UCLASS(minimalapi)
class AEndlessRunnerGameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:
	void SetupCamera() const;
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Players")
	TObjectPtr<AEndlessRunnerCharacter>  Player1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Players")
	TObjectPtr<AEndlessRunnerCharacter>  Player2;
	

public:
	AEndlessRunnerGameMode();
};



