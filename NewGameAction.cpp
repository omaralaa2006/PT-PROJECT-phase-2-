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
	GameState* pNewState = new GameState(pGrid);
	pManager->SetGameState(pNewState);
	pGrid->ClearGrid();
	pManager->UpdateInterface();
	pManager->GetOutput()->PrintMessage("New Game Started!!");

}

NewGameAction::~NewGameAction()
{
}
