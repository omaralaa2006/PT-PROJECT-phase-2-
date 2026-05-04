#include "ExecuteCommandsAction.h"
#include "ApplicationManager.h"
#include "Grid.h"
#include "GameState.h"
#include "Player.h"

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

	if (pState->GetEndGame())
		return;

	Player* pPlayer = pState->GetCurrentPlayer();

	if (pPlayer == NULL)
		return;

	pPlayer->Move(pGrid, pState);

	if (!pState->GetEndGame())
		pState->AdvanceCurrentPlayer();

	pManager->UpdateInterface();
}

ExecuteCommandsAction::~ExecuteCommandsAction()
{
}