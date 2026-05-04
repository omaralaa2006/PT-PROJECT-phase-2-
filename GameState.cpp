#include "GameState.h"
#include "Grid.h"
#include "Player.h"
#include "Cell.h"
#include "Output.h"
#include <cstdlib>
#include <ctime>

GameState::GameState(Grid* pGrid)
{
	srand((unsigned int)time(NULL));

	Cell* startCell = pGrid->GetStartCell();
	Output* pOut = pGrid->GetOutput();

	for (int i = 0; i < MaxPlayerCount; i++)
	{
		PlayerList[i] = new Player(startCell, i);
		PlayerList[i]->Draw(pOut);
	}

	currentPlayerNumber = 0;
	currentPhase = PHASE_MOVEMENT;
	endGame = false;

	GenerateAvailableCommands();
}

GameState::~GameState()
{
	for (int i = 0; i < MaxPlayerCount; i++)
		delete PlayerList[i];
}

Player* GameState::GetCurrentPlayer() const
{
	return PlayerList[currentPlayerNumber];
}

Player* GameState::GetPlayerPointer(int playerNum) const
{
	if (playerNum >= 0 && playerNum < MaxPlayerCount)
		return PlayerList[playerNum];

	return NULL;
}

void GameState::AdvanceCurrentPlayer()
{
	currentPlayerNumber = (currentPlayerNumber + 1) % MaxPlayerCount;
	GenerateAvailableCommands();
}

void GameState::SetCurrentPlayer(int playerNum)
{
	if (playerNum >= 0 && playerNum < MaxPlayerCount)
	{
		currentPlayerNumber = playerNum;
		GenerateAvailableCommands();
	}
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

void GameState::GenerateAvailableCommands()
{
	Player* pPlayer = GetCurrentPlayer();

	if (pPlayer == NULL)
	{
		availableCommandsCount = 0;
		return;
	}

	availableCommandsCount = pPlayer->GetHealth();

	if (availableCommandsCount > MaxAvailableCommands)
		availableCommandsCount = MaxAvailableCommands;

	for (int i = 0; i < availableCommandsCount; i++)
	{
		int randomCommand = rand() % 8;

		if (randomCommand == 0)
			availableCommands[i] = MOVE_FORWARD_ONE_STEP;
		else if (randomCommand == 1)
			availableCommands[i] = MOVE_BACKWARD_ONE_STEP;
		else if (randomCommand == 2)
			availableCommands[i] = MOVE_FORWARD_TWO_STEPS;
		else if (randomCommand == 3)
			availableCommands[i] = MOVE_BACKWARD_TWO_STEPS;
		else if (randomCommand == 4)
			availableCommands[i] = MOVE_FORWARD_THREE_STEPS;
		else if (randomCommand == 5)
			availableCommands[i] = MOVE_BACKWARD_THREE_STEPS;
		else if (randomCommand == 6)
			availableCommands[i] = ROTATE_CLOCKWISE;
		else
			availableCommands[i] = ROTATE_COUNTERCLOCKWISE;
	}

	for (int i = availableCommandsCount; i < MaxAvailableCommands; i++)
		availableCommands[i] = NO_COMMAND;
}

Command GameState::GetAvailableCommand(int index) const
{
	if (index >= 0 && index < availableCommandsCount)
		return availableCommands[index];

	return NO_COMMAND;
}

int GameState::GetAvailableCommandsCount() const
{
	return availableCommandsCount;
}

void GameState::RemoveAvailableCommand(int index)
{
	if (index < 0 || index >= availableCommandsCount)
		return;

	for (int i = index; i < availableCommandsCount - 1; i++)
	{
		availableCommands[i] = availableCommands[i + 1];
	}

	availableCommandsCount--;
	availableCommands[availableCommandsCount] = NO_COMMAND;
}

void GameState::DrawAllPlayers(Output* pOut) const
{
	for (int i = 0; i < MaxPlayerCount; i++)
	{
		if (PlayerList[i] != NULL)
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

	info += " | Curr = " + to_string(currentPlayerNumber + 1);
}