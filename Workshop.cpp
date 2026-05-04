#include "Workshop.h"
#include "Player.h"
#include "Grid.h"
#include "GameState.h"
#include "Output.h"
#include "Input.h"

Workshop::Workshop(const CellPosition& workshopPosition) : GameObject(workshopPosition)
{

}

void Workshop::Draw(Output* pOut) const
{
	pOut->DrawWorkshop(position);
}

void Workshop::Apply(Grid* pGrid, GameState* pState, Player* pPlayer)
{
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	pOut->PrintMessage("Workshop: 1-Repair 2-ExtendedMemory 3-Toolkit 4-Hack 5-DoubleLaser");

	int choice = pIn->GetInteger(pOut);

	if (choice == 1)
	{
		int maxHealth = 10;
		pPlayer->SetHealth(maxHealth);
	}
	else if (choice == 2)
	{
		pPlayer->SetExtendedMemory(true);
	}
	else if (choice == 3)
	{
		pPlayer->SetToolkit(true);
	}
	else if (choice == 4)
	{
		pPlayer->SetHackDevice(true);

		for (int i = 0; i < MaxPlayerCount; i++)
		{
			Player* other = pState->GetPlayerPointer(i);

			if (other != NULL && other != pPlayer)
			{
				other->SetHacked(true);
			}
		}
	}
	else if (choice == 5)
	{
		pPlayer->SetLaserDamage(2);
	}

	pOut->ClearStatusBar();

	///TODO: Implement this function
	// Apply the workshop's effect on the player
	// [OPTIONAL BONUS] Consumables can be given to the player here
	// BONUS IMPLEMENTED:
	// 1- Repair: restores player's health to maximum
	// 2- Extended Memory: allows player to save up to 6 commands instead of 5
	// 3- Toolkit: gives player a consumable (can be used later if extended logic added)
	// 4- Hack Device: hacks the opponent and skips their next turn
	// 5- Double Laser: increases laser damage from 1 to 2 during shooting phase
}

GameObject* Workshop::Clone() const
{
	return new Workshop(*this);
}

void Workshop::Save(ofstream& OutFile, ActionType type)
{
	if (type == ADD_WORKSHOP)
	{
		OutFile << position.GetCellNum() << endl;
	}
}

void Workshop::Load(ifstream& Infile)
{
	int cellNum;
	Infile >> cellNum;
	position = CellPosition::GetCellPositionFromNum(cellNum);
}

ActionType Workshop::GetType() const
{
	return ADD_WORKSHOP;
}

Workshop::~Workshop()
{
}