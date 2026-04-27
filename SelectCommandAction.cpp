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
	Output* pOut = pGrid->GetOutput();

	int index = pIn->GetSelectedCommandIndex();

	if (index == 0)
		selectedCommand = MOVE_FORWARD_ONE_STEP;
	else if (index == 1)
		selectedCommand = MOVE_BACKWARD_ONE_STEP;
	else if (index == 2)
		selectedCommand = ROTATE_CLOCKWISE;
	else if (index == 3)
		selectedCommand = ROTATE_COUNTERCLOCKWISE;
	else
		selectedCommand = NO_COMMAND;
}

void SelectCommandAction::Execute()
{
	ReadActionParameters();

	if (selectedCommand == NO_COMMAND)
		return;

	GameState* pState = pManager->GetGameState();
	Player* pPlayer = pState->GetCurrentPlayer();

	pPlayer->AddSavedCommand(selectedCommand);
}

SelectCommandAction::~SelectCommandAction()
{
}