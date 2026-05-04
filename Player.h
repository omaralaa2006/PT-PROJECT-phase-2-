#pragma once

#include "Grid.h"
#include "Cell.h"

// Forward declaration: GameState is needed for Move() but we don't include it
// here to avoid a circular dependency (GameState.h includes Player.h).
class GameState;

class Player
{
	Cell* pCell;           // Pointer to the cell the player currently occupies
	const int playerNum;   // Player index 0..MaxPlayerCount-1 (constant after construction)

	Direction currDirection; // The direction the player is currently facing
	int health;              // Player's current health points

	// ---- Saved Commands (the player's "program" for this round) ----
	Command savedCommands[MaxSavedCommandsWithExtendedMemory];
	int savedCommandCount;

	// ---- [OPTIONAL BONUS] Shooting Phase data members ----
	int laserDamage;
	bool isHacked;

	// ---- [OPTIONAL BONUS] Workshop Consumables data members ----
	bool hasExtendedMemory;
	bool hasToolkit;
	bool hasHackDevice;

public:

	Player(Cell* pCell, int playerNum); // Initialises all data members

	// ====== Setters and Getters ======

	void  SetCell(Cell* cell);
	Cell* GetCell() const;

	void SetHealth(int h);
	int  GetHealth() const;

	Direction GetDirection() const;
	void      SetDirection(Direction d);

	int GetPlayerNum() const;

	int GetLaserDamage() const;
	void SetLaserDamage(int damage);

	bool HasExtendedMemory() const;
	void SetExtendedMemory(bool value);

	bool HasToolkit() const;
	void SetToolkit(bool value);

	bool HasHackDevice() const;
	void SetHackDevice(bool value);

	bool IsHacked() const;
	void SetHacked(bool value);

	int GetMaxSavedCommands() const;

	///TODO: Add more setters/getters here as needed

	// ====== Saved Commands ======

	void    AddSavedCommand(Command cmd);
	void    ClearSavedCommands();
	int     GetSavedCommandCount() const;
	Command GetSavedCommand(int index) const;

	// ====== Drawing ======

	void Draw(Output* pOut) const;
	void ClearDrawing(Output* pOut) const;

	// ====== Game Logic ======

	void Move(Grid* pGrid, GameState* pState);

	void AppendPlayerInfo(string& playersInfo) const;

	void Rotate(bool clockwise);
};