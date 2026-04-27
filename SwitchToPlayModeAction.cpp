#include "SwitchToPlayModeAction.h"
#include "ApplicationManager.h"
#include "Grid.h"
#include "GameState.h"
#include "Output.h"

SwitchToPlayModeAction::SwitchToPlayModeAction(ApplicationManager* pApp)
	: Action(pApp)
{
}

void SwitchToPlayModeAction::ReadActionParameters()
{
	// No input needed
}

void SwitchToPlayModeAction::Execute()
{
	ReadActionParameters();

	Output* pOut = pManager->GetGrid()->GetOutput();
	GameState* pState = pManager->GetGameState();

	UI.InterfaceMode = MODE_PLAY;

	pOut->CreatePlayModeToolBar();

	pState->SetCurrentPhase(PHASE_MOVEMENT);

	pManager->UpdateInterface();

	pOut->PrintMessage("Switched to Play Mode");
}

SwitchToPlayModeAction::~SwitchToPlayModeAction()
{
}