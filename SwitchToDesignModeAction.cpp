#include "SwitchToDesignModeAction.h"
#include "ApplicationManager.h"
#include "Grid.h"
#include "Output.h"

SwitchToDesignModeAction::SwitchToDesignModeAction(ApplicationManager* pApp)
	: Action(pApp)
{
}

void SwitchToDesignModeAction::ReadActionParameters()
{
	// No input needed
}

void SwitchToDesignModeAction::Execute()
{
	ReadActionParameters();

	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();

	UI.InterfaceMode = MODE_DESIGN;

	pOut->CreateDesignModeToolBar();

	pManager->UpdateInterface();

	pOut->PrintMessage("Switched to Design Mode");
}

SwitchToDesignModeAction::~SwitchToDesignModeAction()
{
}