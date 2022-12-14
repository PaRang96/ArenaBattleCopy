// Fill out your copyright notice in the Description page of Project Settings.


#include "ABGameMode.h"
#include "ABCharacter.h"
#include "ABPlayerController.h"
#include "ABPlayerState.h"
#include "ABGameState.h"

AABGameMode::AABGameMode()
{
	// setting default pawn
	DefaultPawnClass = AABCharacter::StaticClass();

	// setting default player controller
	PlayerControllerClass = AABPlayerController::StaticClass();

	PlayerStateClass = AABPlayerState::StaticClass();

	GameStateClass = AABGameState::StaticClass();
}

void AABGameMode::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	ABGameState = Cast<AABGameState>(GameState);
}

void AABGameMode::PostLogin(APlayerController* NewPlayer)
{
	//ABLOG(Warning, TEXT("PostLogin Begin"));
	Super::PostLogin(NewPlayer);
	//ABLOG(Warning, TEXT("PostLogin End"));

	auto ABPlayerState = Cast<AABPlayerState>(NewPlayer->PlayerState);
	ABCHECK(nullptr != ABPlayerState);
	ABPlayerState->InitPlayerData();
}

void AABGameMode::AddScore(AABPlayerController* ScoredPlayer)
{
	for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
	{
		const auto ABPlayerController = Cast<AABPlayerController>(It->Get());

		if ((nullptr != ABPlayerController) && (ScoredPlayer == ABPlayerController))
		{
			ABPlayerController->AddGameScore();
			break;
		}

		ABGameState->AddGameScore();
	}
}

int32 AABGameMode::GetScore() const
{
	return ABGameState->GetTotalGameScore();
}
