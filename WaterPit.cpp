#include "WaterPit.h"
#include"Player.h"
#include"Grid.h"

WaterPit::WaterPit(const CellPosition & waterPitPosition):GameObject(waterPitPosition)
{
}

void WaterPit::Draw(Output * pOut) const
{
	pOut->DrawWaterPit(position);
}

void WaterPit::Apply(Grid* pGrid, GameState* pState, Player* pPlayer)
{

	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();


	pOut->PrintMessage("You drowned in a water pit! Health -3 and resetting to start... Click to continue");
	int x, y;
	pIn->GetPointClicked(x, y);


	int currentHealth = pPlayer->GetHealth();
	pPlayer->SetHealth(currentHealth - 3);


	CellPosition startPos(8, 0);
	pGrid->UpdatePlayerCell(pPlayer, startPos);


	pGrid->UpdateInterface(pState);


	pOut->ClearStatusBar();
}
		///TODO: Implement this function as mentioned in the guideline steps (numbered below) below


		// == Here are some guideline steps (numbered below) to implement this function ==

		// 1- Print a message, make sure to edit this message according to which player wins "You drowned in a water pit. Player (0/1) wins !  Click to continue ..." and wait mouse click

		// 2- Apply the water pit's effect by setting the player's health which drowned to zero and ending the game
		// 3- Update the players info which is displayed (check Grid class and decide which function to use)

GameObject* WaterPit::Clone() const
{
	return new WaterPit(*this);
}

void WaterPit::Save(ofstream& OutFile, ActionType type) {
	if (type == ADD_WATER_PIT) {
		OutFile << position.GetCellNum() << endl;
	}
}

void WaterPit::Load(ifstream& Infile)
{
	int cellNum;
	Infile >> cellNum;
	position = CellPosition::GetCellPositionFromNum(cellNum);
}
ActionType WaterPit::GetType() const
{
	return ADD_WATER_PIT;
}
WaterPit::~WaterPit()
{
}
