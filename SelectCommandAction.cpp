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
	ReadActionParameters();

	if (selectedCommand == NO_COMMAND)
		return;

	GameState* pState = pManager->GetGameState();
	Player* pPlayer = pState->GetCurrentPlayer();
	Output* pOut = pManager->GetGrid()->GetOutput();

	if (pPlayer == NULL)
		return;

	int maxAllowed = (pPlayer->GetHealth() < 5) ? pPlayer->GetHealth() : 5;

	if (pPlayer->GetSavedCommandCount() >= maxAllowed)
	{
		pOut->PrintMessage("You reached max commands");
		return;
	}

	pPlayer->AddSavedCommand(selectedCommand);

	pManager->UpdateInterface();
}

SelectCommandAction::~SelectCommandAction()
{
}