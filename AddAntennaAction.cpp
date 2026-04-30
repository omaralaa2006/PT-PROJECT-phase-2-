#include "AddAntennaAction.h"
#include"Antenna.h"
#include"Grid.h"
AddAntennaAction::AddAntennaAction(ApplicationManager* pApp):Action(pApp)
{
}

void AddAntennaAction::ReadActionParameters()
{
	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();
	pOut->PrintMessage("Click on a cell to place the Antenna...");
	antennaPos = pIn->GetCellClicked();
	//validation
	if (!antennaPos.IsValidCell() || antennaPos.GetCellNum() == 1 || antennaPos.GetCellNum() == 55)
	{
		pOut->PrintMessage("Error! invalid cell position");
		antennaPos = CellPosition(-1, -1);
	}
	pOut->ClearStatusBar();
}

void AddAntennaAction::Execute()
{
	ReadActionParameters();
	if (antennaPos.IsValidCell())
	{
		Antenna* pAntenna = new Antenna(antennaPos);
		Grid* pGrid = pManager->GetGrid();
		bool added = pGrid->AddObjectToCell(pAntenna);
		if (!added)
		{
			pManager->GetOutput()->PrintMessage("Error! Cell already occupied.");
			delete pAntenna;
		}
		else
		{
			pManager->GetOutput()->PrintMessage("Antenna Added successfully. ");
		}
	}
}

AddAntennaAction::~AddAntennaAction()
{
}
