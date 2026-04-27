#include "NewGameAction.h"
#include "ApplicationManager.h"
#include "Grid.h"
#include "GameState.h"

NewGameAction::NewGameAction(ApplicationManager* pApp)
	: Action(pApp)
{
}

void NewGameAction::ReadActionParameters()
{
}

void NewGameAction::Execute()
{
	ReadActionParameters();

	Grid* pGrid = pManager->GetGrid();
	GameState* pState = pManager->GetGameState();

	delete pState;
	pState = new GameState(pGrid);

	pManager->UpdateInterface();
}

NewGameAction::~NewGameAction()
{
}
