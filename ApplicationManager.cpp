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
#include "CopyGameObjectAcion.h"
#include "CutGameObjectAction.h"
#include "DeleteGameObjectAction.h"
#include "AddWaterPitAction.h"
#include "AddAntennaAction.h"
#include "AddDangerZoneAction.h"
#include "AddWorkShopAction.h"
#include "PasteGameObjectAction.h"
#include "SaveGridAction.h"
#include"LoadAction.h"
#include "GameState.h"

ApplicationManager::ApplicationManager()
{
	pOut = new Output();
	pIn = pOut->CreateInput();
	pGrid = new Grid(pIn, pOut);
	pGameState = new GameState(pGrid);
}

ApplicationManager::~ApplicationManager()
{
	delete pGameState;
	delete pGrid;
}

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
	pGrid->UpdateInterface(pGameState);
}

ActionType ApplicationManager::GetUserAction() const
{
	return pIn->GetUserAction();
}

void ApplicationManager::ExecuteAction(ActionType ActType)
{
	Action* pAct = NULL;

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

	case ADD_DANGER_ZONE:
		pAct = new AddDangerZoneAction(this);
		break;

	case ADD_WORKSHOP:
		pAct = new AddWorkShopAction(this);
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

	case PASTE_OBJECT:
		pAct = new PasteGameObjectAction(this);
		break;
    case SAVE_GRID:
		pAct = new SaveGridAction(this);
		break;
    case LOAD_GRID:
		pAct = new LoadAction(this);
		break;
	case NEW_GAME:
		pAct = new NewGameAction(this);
		break;

	case EXECUTE_COMMANDS:
		pAct = new ExecuteCommandsAction(this);
		break;

	case SELECT_COMMAND:
		pAct = new SelectCommandAction(this);
		break;

	case TO_DESIGN_MODE:
		pAct = new SwitchToDesignModeAction(this);
		break;

	case EXIT_Play:
		break;

	case REBOOT_REPAIR:
		pAct = new RebootRepairAction(this); // added case yargoola
		break;
    
	case STATUS:
		return;
	}

	if (pAct != NULL)
	{
		pAct->Execute();
		delete pAct;
		pAct = NULL;
	}
}