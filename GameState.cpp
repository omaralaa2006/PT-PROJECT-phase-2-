#include "GameState.h"
#include "Grid.h"
#include "Player.h"
#include "Cell.h"
#include "Output.h"

GameState::GameState(Grid* pGrid)
{
	Cell* startCell = pGrid->GetStartCell();
	Output* pOut = pGrid->GetOutput();

	for (int i = 0; i < MaxPlayerCount; i++)
	{
		PlayerList[i] = new Player(startCell, i);
		PlayerList[i]->Draw(pOut);
	}

	currPlayerNumber = 0;
	currentPhase = PHASE_MOVEMENT;
	endGame = false;
}

GameState::~GameState()
{
	for (int i = 0; i < MaxPlayerCount; i++)
		delete PlayerList[i];
}

Player* GameState::GetCurrentPlayer() const
{
	return PlayerList[currPlayerNumber];
}

Player* GameState::GetPlayer(int playerNum) const
{
	if (playerNum >= 0 && playerNum < MaxPlayerCount)
		return PlayerList[playerNum];
	return nullptr;
}

void GameState::AdvanceCurrentPlayer()
{
	currPlayerNumber = (currPlayerNumber + 1) % MaxPlayerCount;
}

void GameState::SetFirstPlayer(int playerNum)
{
	if (playerNum >= 0 && playerNum < MaxPlayerCount)
		currPlayerNumber = playerNum;
}

PhaseType GameState::GetCurrentPhase() const
{
	return currentPhase;
}

void GameState::SetCurrentPhase(PhaseType phase)
{
	currentPhase = phase;
}

void GameState::AdvancePhase()
{
	currentPhase = PHASE_MOVEMENT;
}

bool GameState::GetEndGame() const
{
	return endGame;
}

void GameState::SetEndGame(bool end)
{
	endGame = end;
}

void GameState::DrawAllPlayers(Output* pOut) const
{
	for (int i = 0; i < MaxPlayerCount; i++)
	{
		if (PlayerList[i])
			PlayerList[i]->Draw(pOut);
	}
}

void GameState::AppendPlayersInfo(string& info) const
{
	for (int i = 0; i < MaxPlayerCount; i++)
	{
		PlayerList[i]->AppendPlayerInfo(info);
		if (i < MaxPlayerCount - 1)
			info += ", ";
	}
	info += " | Curr = " + to_string(currPlayerNumber);
}