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

}

void SwitchToPlayModeAction::Execute()
{
	ReadActionParameters();

	Output* pOut = pManager->GetGrid()->GetOutput();
	GameState* pState = pManager->GetGameState();

	UI.InterfaceMode = MODE_PLAY;

	pOut->CreatePlayModeToolBar();

	Command saved[MaxSavedCommands] = {
		NO_COMMAND,
		NO_COMMAND,
		NO_COMMAND,
		NO_COMMAND,
		NO_COMMAND
	};

	Command available[8] = {
		MOVE_FORWARD_ONE_STEP,
		MOVE_BACKWARD_ONE_STEP,
		MOVE_FORWARD_TWO_STEPS,
		MOVE_BACKWARD_TWO_STEPS,
		MOVE_FORWARD_THREE_STEPS,
		MOVE_BACKWARD_THREE_STEPS,
		ROTATE_CLOCKWISE,
		ROTATE_COUNTERCLOCKWISE
	};

	pOut->CreateCommandsBar(saved, MaxSavedCommands, available, 8);

	pState->SetCurrentPhase(PHASE_MOVEMENT);

	pManager->UpdateInterface();

	pOut->PrintMessage("Switched to Play Mode");
}

SwitchToPlayModeAction::~SwitchToPlayModeAction()
{
}