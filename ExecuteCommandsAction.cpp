#include "ExecuteCommandsAction.h"
#include "ApplicationManager.h"
#include "Grid.h"
#include "GameState.h"
#include "Player.h"
#include "Output.h"

ExecuteCommandsAction::ExecuteCommandsAction(ApplicationManager* pApp)
	: Action(pApp)
{
}

void ExecuteCommandsAction::ReadActionParameters()
{

}

void ExecuteCommandsAction::Execute()
{
	ReadActionParameters();

	Grid* pGrid = pManager->GetGrid();
	GameState* pState = pManager->GetGameState();
	Output* pOut = pGrid->GetOutput();

	if (pState->GetEndGame())
		return;

	Player* pPlayer = pState->GetCurrentPlayer();

	if (pPlayer == NULL)
		return;

	// ===== Movement Phase =====
	if (pState->GetCurrentPhase() == PHASE_MOVEMENT)
	{
		if (pPlayer->IsHacked())
		{
			pOut->PrintMessage("Player is hacked! Turn skipped.");
			pPlayer->SetHacked(false);
			pState->AdvanceCurrentPlayer();
		}
		else
		{
			pPlayer->Move(pGrid, pState);

			if (!pState->GetEndGame())
				pState->SetCurrentPhase(PHASE_SHOOTING);
		}
	}
	// ===== Shooting Phase =====
	else if (pState->GetCurrentPhase() == PHASE_SHOOTING)
	{
		pState->ApplyShooting(pGrid);

		if (!pState->GetEndGame())
			pState->AdvanceCurrentPlayer();
	}

	pManager->UpdateInterface();
}

ExecuteCommandsAction::~ExecuteCommandsAction()
{
}