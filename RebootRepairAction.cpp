#include "RebootRepairAction.h"
#include "ApplicationManager.h"
#include "Grid.h"
#include "GameState.h"
#include "Player.h"
#include "Output.h"

RebootRepairAction::RebootRepairAction(ApplicationManager* pApp)
	: Action(pApp)
{
}

void RebootRepairAction::ReadActionParameters()
{
}

void RebootRepairAction::Execute()
{
	ReadActionParameters();

	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	GameState* pState = pManager->GetGameState();

	Player* pPlayer = pState->GetCurrentPlayer();

	int health = pPlayer->GetHealth();
	pPlayer->SetHealth(health + 2);

	pPlayer->ClearSavedCommands();

	pState->AdvanceCurrentPlayer();

	pManager->UpdateInterface();

	pOut->PrintMessage("Robot rebooted and repaired");
}

RebootRepairAction::~RebootRepairAction()
{
}