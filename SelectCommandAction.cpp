#include "SelectCommandAction.h"
#include "ApplicationManager.h"
#include "Grid.h"
#include "Input.h"
#include "Output.h"
#include "GameState.h"
#include "Player.h"

SelectCommandAction::SelectCommandAction(ApplicationManager* pApp)
	: Action(pApp)
{
	selectedCommand = NO_COMMAND;
}

void SelectCommandAction::ReadActionParameters()
{
	Grid* pGrid = pManager->GetGrid();
	Input* pIn = pGrid->GetInput();
	GameState* pState = pManager->GetGameState();

	int index = pIn->GetSelectedCommandIndex();

	selectedCommand = pState->GetAvailableCommand(index);

	if (selectedCommand != NO_COMMAND)
		pState->RemoveAvailableCommand(index);
}

void SelectCommandAction::Execute()
{
	GameState* pState = pManager->GetGameState();

	if (pState->GetEndGame())
		return;

	if (pState->GetCurrentPhase() != PHASE_MOVEMENT)
		return;

	ReadActionParameters();

	if (selectedCommand == NO_COMMAND)
		return;

	Player* pPlayer = pState->GetCurrentPlayer();

	if (pPlayer == NULL)
		return;

	if (pPlayer->GetSavedCommandCount() >= pPlayer->GetMaxSavedCommands())
		return;

	pPlayer->AddSavedCommand(selectedCommand);

	pManager->UpdateInterface();
}

SelectCommandAction::~SelectCommandAction()
{
}