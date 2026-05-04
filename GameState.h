#pragma once

#include "UI_Info.h"
#include "DEFS.h"

// Forward declarations (includes are in GameState.cpp)
class Grid;
class Player;
class Output;

// ============================================================
// GameState: owns everything that changes during the game.
//
// Responsibilities:
//   - Which player is currently taking their turn (turn order)
//   - What phase of the round we are in (movement, [shooting bonus])
//   - Whether the game has ended
//   - The Player objects themselves
//
// Responsibilities that do NOT belong here:
//   - The board layout (cells, game objects)  --> Grid
//   - Drawing / input                         --> Grid (via Output/Input)
// ============================================================
class GameState
{
	Player* PlayerList[MaxPlayerCount];

	int currentPlayerNumber;

	PhaseType currentPhase;
	bool endGame;

	Command availableCommands[MaxAvailableCommands];
	int availableCommandsCount;

public:

	GameState(Grid* pGrid);

	~GameState();

	Player* GetCurrentPlayer() const;
	Player* GetPlayerPointer(int playerNum) const;

	void AdvanceCurrentPlayer();
	void SetCurrentPlayer(int playerNum);

	PhaseType GetCurrentPhase() const;
	void SetCurrentPhase(PhaseType phase);
	void AdvancePhase();

	bool GetEndGame() const;
	void SetEndGame(bool end);

	void GenerateAvailableCommands();
	Command GetAvailableCommand(int index) const;
	int GetAvailableCommandsCount() const;
	void RemoveAvailableCommand(int index);

	bool CanShoot(Player* attacker, Player* target) const;
	void ApplyShooting(Grid* pGrid);

	void DrawAllPlayers(Output* pOut) const;
	void AppendPlayersInfo(string& info) const;
};