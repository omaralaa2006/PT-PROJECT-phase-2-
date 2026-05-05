#include "Player.h"
#include "GameObject.h"
#include "GameState.h"
#include "Output.h"

Player::Player(Cell* pCell, int playerNum)
	: playerNum(playerNum), health(10), currDirection(RIGHT), savedCommandCount(0)
{
	this->pCell = pCell;

	laserDamage = 1;
	isHacked = false;

	hasExtendedMemory = false;
	hasToolkit = false;
	hasHackDevice = false;

	for (int i = 0; i < MaxSavedCommandsWithExtendedMemory; i++)
		savedCommands[i] = NO_COMMAND;
}

void Player::SetCell(Cell* cell)
{
	pCell = cell;
}

Cell* Player::GetCell() const
{
	return pCell;
}

void Player::SetHealth(int h)
{
	if (h < 0)
		health = 0;
	else if (h > 10)
		health = 10;
	else
		health = h;
}

int Player::GetHealth() const
{
	return health;
}

Direction Player::GetDirection() const
{
	return currDirection;
}

void Player::SetDirection(Direction d)
{
	currDirection = d;
}

int Player::GetPlayerNum() const
{
	return playerNum;
}

int Player::GetLaserDamage() const
{
	return laserDamage;
}

void Player::SetLaserDamage(int damage)
{
	laserDamage = damage;
}

bool Player::HasExtendedMemory() const
{
	return hasExtendedMemory;
}

void Player::SetExtendedMemory(bool value)
{
	hasExtendedMemory = value;
}

bool Player::HasToolkit() const
{
	return hasToolkit;
}

void Player::SetToolkit(bool value)
{
	hasToolkit = value;
}

bool Player::HasHackDevice() const
{
	return hasHackDevice;
}

void Player::SetHackDevice(bool value)
{
	hasHackDevice = value;
}

bool Player::IsHacked() const
{
	return isHacked;
}

void Player::SetHacked(bool value)
{
	isHacked = value;
}

int Player::GetMaxSavedCommands() const
{
	int maxCommands = hasExtendedMemory ? MaxSavedCommandsWithExtendedMemory : MaxSavedCommands;

	if (health < maxCommands)
		return health;

	return maxCommands;
}

void Player::AddSavedCommand(Command cmd)
{
	int maxAllowed = GetMaxSavedCommands();

	if (savedCommandCount < maxAllowed)
		savedCommands[savedCommandCount++] = cmd;
}

void Player::ClearSavedCommands()
{
	for (int i = 0; i < MaxSavedCommandsWithExtendedMemory; i++)
		savedCommands[i] = NO_COMMAND;

	savedCommandCount = 0;
}

int Player::GetSavedCommandCount() const
{
	return savedCommandCount;
}

Command Player::GetSavedCommand(int index) const
{
	if (index >= 0 && index < savedCommandCount)
		return savedCommands[index];

	return NO_COMMAND;
}

void Player::Draw(Output* pOut) const
{
	if (!pOut || !pCell)
		return;

	color playerColor = UI.PlayerColors[playerNum];
	pOut->DrawPlayer(pCell->GetCellPosition(), playerNum, playerColor, currDirection);
}

void Player::ClearDrawing(Output* pOut) const
{
	if (!pOut || !pCell)
		return;

	pOut->DrawCell(pCell->GetCellPosition(), UI.CellColor);
}

void Player::Move(Grid* pGrid, GameState* pState)
{
	if (!pGrid || !pState || !pCell)
		return;

	bool reachedWorkshop = false;

	for (int i = 0; i < savedCommandCount; i++)
	{
		Command cmd = savedCommands[i];

		if (cmd == ROTATE_CLOCKWISE)
		{
			Rotate(true);
		}
		else if (cmd == ROTATE_COUNTERCLOCKWISE)
		{
			Rotate(false);
		}
		else
		{
			int steps = 0;
			Direction moveDirection = currDirection;

			if (cmd == MOVE_FORWARD_ONE_STEP)
				steps = 1;
			else if (cmd == MOVE_FORWARD_TWO_STEPS)
				steps = 2;
			else if (cmd == MOVE_FORWARD_THREE_STEPS)
				steps = 3;
			else if (cmd == MOVE_BACKWARD_ONE_STEP)
				steps = 1;
			else if (cmd == MOVE_BACKWARD_TWO_STEPS)
				steps = 2;
			else if (cmd == MOVE_BACKWARD_THREE_STEPS)
				steps = 3;

			if (cmd == MOVE_BACKWARD_ONE_STEP ||
				cmd == MOVE_BACKWARD_TWO_STEPS ||
				cmd == MOVE_BACKWARD_THREE_STEPS)
			{
				if (currDirection == UP)
					moveDirection = DOWN;
				else if (currDirection == DOWN)
					moveDirection = UP;
				else if (currDirection == RIGHT)
					moveDirection = LEFT;
				else if (currDirection == LEFT)
					moveDirection = RIGHT;
			}

			if (steps > 0)
			{
				CellPosition newPos = pCell->GetCellPosition();
				newPos.AddCellNum(steps, moveDirection);

				if (newPos.IsValidCell())
					pGrid->UpdatePlayerCell(this, newPos);
			}
		}

		GameObject* pObj = pCell->GetGameObject();

		if (pObj != NULL)
		{
			if (pCell->HasWorkShop() != NULL)
				reachedWorkshop = true;
			else
				pObj->Apply(pGrid, pState, this);
		}
	}

	if (reachedWorkshop && pCell->HasWorkShop() != NULL)
	{
		GameObject* pObj = pCell->GetGameObject();

		if (pObj != NULL)
			pObj->Apply(pGrid, pState, this);
	}

	ClearSavedCommands();
}

void Player::AppendPlayerInfo(string& playersInfo) const
{
	string dir;

	if (currDirection == UP)
		dir = "Up";
	else if (currDirection == DOWN)
		dir = "Down";
	else if (currDirection == RIGHT)
		dir = "Right";
	else if (currDirection == LEFT)
		dir = "Left";

	playersInfo += "P" + to_string(playerNum + 1) + "(";
	playersInfo += dir + ", ";
	playersInfo += to_string(health) + ")";

	if (hasExtendedMemory)
		playersInfo += "[M]";
	if (laserDamage == 2)
		playersInfo += "[DL]";
}

void Player::Rotate(bool clockwise)
{
	if (clockwise)
	{
		if (currDirection == UP) currDirection = RIGHT;
		else if (currDirection == RIGHT) currDirection = DOWN;
		else if (currDirection == DOWN) currDirection = LEFT;
		else if (currDirection == LEFT) currDirection = UP;
	}
	else
	{
		if (currDirection == UP) currDirection = LEFT;
		else if (currDirection == LEFT) currDirection = DOWN;
		else if (currDirection == DOWN) currDirection = RIGHT;
		else if (currDirection == RIGHT) currDirection = UP;
	}
}