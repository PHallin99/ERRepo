// Fill out your copyright notice in the Description page of Project Settings.


#include "SaveSystem.h"

void USaveSystem::SaveScore(int Score)
{
	const FString SaveDirectory = FPaths::ProjectSavedDir() + "SaveData/";

	UE_LOG(LogTemp, Warning, TEXT("Save Directory: %s"), *SaveDirectory);

	if (!FPlatformFileManager::Get().GetPlatformFile().DirectoryExists(*SaveDirectory))
	{
		FPlatformFileManager::Get().GetPlatformFile().CreateDirectory(*SaveDirectory);
	}

	const FString FilePath = SaveDirectory + "SessionScore";
	FFileHelper::SaveStringToFile(FString::FromInt(Score), *FilePath);
}

int USaveSystem::LoadScore()
{
	const FString SaveDirectory = FPaths::ProjectSavedDir() + "SaveData/";

	if (!FPlatformFileManager::Get().GetPlatformFile().DirectoryExists(*SaveDirectory))
	{
		FPlatformFileManager::Get().GetPlatformFile().CreateDirectory(*SaveDirectory);
	}

	const FString FilePath = SaveDirectory + "SessionScore";
	FString FileContent;
	FFileHelper::LoadFileToString(FileContent, *FilePath);

	const int32 Value = FCString::Atoi(*FileContent);

	return Value;
}
