#include "DangerZone.h"
#include"Player.h"


DangerZone::DangerZone(const CellPosition & dangerZonePosition): GameObject(dangerZonePosition)
{
}

void DangerZone::Draw(Output * pOut) const
{
	pOut->DrawDangerZone(position);
}

void DangerZone::Apply(Grid* pGrid, GameState* pState, Player* pPlayer)
{
	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below


	// == Here are some guideline steps (numbered below) to implement this function ==

	// 1- Print a message "You have reached a danger zone. Click to continue ..." and wait mouse click

	// 2- Apply the danger zone's effect by reducing the health of the player by 1 
	// 3- Update the players info which is displayed (check Grid class and decide which function to use)
	
	
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	
	pOut->PrintMessage("You have reached a danger zone. Health -1! Click to continue ...");
	int x, y;
	pIn->GetPointClicked(x, y);

	
	int currentHealth = pPlayer->GetHealth();
	pPlayer->SetHealth(currentHealth - 1);

	
	pGrid->UpdatePlayerCell(pPlayer, pPlayer->GetCell()->GetCellPosition());


	pOut->ClearStatusBar();


}


DangerZone::~DangerZone()
{
}
