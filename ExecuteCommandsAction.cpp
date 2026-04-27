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

	Player* pPlayer = pState->GetCurrentPlayer();

	pPlayer->Move(pGrid, pState);

	pState->AdvanceCurrentPlayer();

	pManager->UpdateInterface();
}

ExecuteCommandsAction::~ExecuteCommandsAction()
{
}