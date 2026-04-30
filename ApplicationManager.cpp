#include "ApplicationManager.h"
#include "Grid.h"
#include "RebootRepairAction.h"
#include "SelectCommandAction.h"
#include "ExecuteCommandsAction.h"
#include "NewGameAction.h"
#include "AddBeltAction.h"
#include "AddRotatingGearAction.h"
#include "AddFlagAction.h"
#include "SwitchToPlayModeAction.h"
#include "SwitchToDesignModeAction.h"
///TODO: Add #include for all action types
#include "CopyGameObjectAction.h"
#include "CutGameObjectAction.h"
#include "DeleteGameObjectAction.h"
#include "AddWaterPitAction.h"
#include "AddAntennaAction.h"

#include "GameState.h"

ApplicationManager::ApplicationManager()
{
	// Creation order matters:
	//   1. Output / Input  (needed by Grid)
	//   2. Grid            (needed by GameState -- provides the start Cell)
	//   3. GameState       (creates and draws initial players)
	pOut = new Output();
	pIn  = pOut->CreateInput();
	pGrid      = new Grid(pIn, pOut);
	pGameState = new GameState(pGrid);
}

ApplicationManager::~ApplicationManager()
{
	// Deletion order is the reverse of creation:
	//   GameState owns the Players -- delete it first.
	//   Grid owns pIn and pOut     -- delete it last.
	delete pGameState;
	delete pGrid;
}

//==================================================================================//
//								Interface Management Functions						//
//==================================================================================//

Grid* ApplicationManager::GetGrid() const
{
	return pGrid;
}

GameState* ApplicationManager::GetGameState() const
{
	return pGameState;
}

void ApplicationManager::UpdateInterface() const
{
	// Grid draws the board; GameState provides player data for drawing.
	pGrid->UpdateInterface(pGameState);
}

//==================================================================================//
//								Actions Related Functions							//
//==================================================================================//

ActionType ApplicationManager::GetUserAction() const
{
	// Ask the input to get the action from the user.
	return pIn->GetUserAction();
}

////////////////////////////////////////////////////////////////////////////////////

// Creates an action and executes it
void ApplicationManager::ExecuteAction(ActionType ActType)
{
	Action* pAct = NULL;

	// According to Action Type, create the corresponding action object
	switch (ActType)
	{
	case SET_FLAG_CELL:
		pAct = new AddFlagAction(this);
		break;
	case EXIT:
		break;
	case TO_PLAY_MODE:
		pAct = new SwitchToPlayModeAction(this);
		break;
	case ADD_ANTENNA:
		pAct = new AddAntennaAction(this);
		break;
	case ADD_BELT:
		pAct = new AddBeltAction(this);
		break;
	case ADD_WATER_PIT:
		pAct = new AddWaterPitAction(this);
		break;


	case ADD_ROTATINGGEAR:
		pAct = new AddRotatingGearAction(this);
		break;

	


	case COPY_OBJECT:
		pAct = new CopyGameObjectAction(this);
		break;
	case CUT_OBJECT:
		pAct = new CutGameObjectAction(this);
		break;
	case DELETE_OBJECT:
		pAct = new DeleteGameObjectAction(this);
		break;


	

	///TODO: Add a case for EACH remaining Design Mode action type

	case TO_DESIGN_MODE:
		pAct = new SwitchToDesignModeAction(this);
		break;

	///TODO: Add a case for EACH remaining Play Mode action type
	case SELECT_COMMAND:
		pAct = new SelectCommandAction(this);
		break;

	case EXECUTE_COMMANDS:
		pAct = new ExecuteCommandsAction(this);
		break;
	case REBOOT_REPAIR:
		pAct = new RebootRepairAction(this); // added case yargoola
		break;
	case NEW_GAME:
		pAct = new NewGameAction(this);
		break;
	case STATUS:	// a click on the status bar ==> no action
		return;
	}

	//men hna bedayat el code elasasi
	// Execute the created action
	if(pAct != NULL)
	{
		pAct->Execute(); // Execute
		delete pAct;	 // Action is not needed any more after executing ==> delete it
		pAct = NULL;
	}
}
