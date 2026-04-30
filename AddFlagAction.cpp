#include "AddFlagAction.h"
#include "Input.h"
#include"Output.h"
#include"Flag.h"
#include"Grid.h"
AddFlagAction::AddFlagAction(ApplicationManager *pApp) : Action(pApp)
{
	// Initializes the pManager pointer of Action with the passed pointer
}


void AddFlagAction::ReadActionParameters()
{

	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	pOut->PrintMessage("Click on the cell to place the flag...");
	flagPos = pIn->GetCellClicked();
	if (!flagPos.IsValidCell() || flagPos.GetCellNum() == 1 || flagPos.GetCellNum() == 55)
	{
		pOut->PrintMessage("Error! Invalid cell . cannot place flag here");
		flagPos = CellPosition(-1, -1);
	}
	// == Here are some guideline steps (numbered below) to implement this function ==

	// 1- Get a Pointer to the Input / Output Interfaces

	// 2- Read the flagPos

	// 4- Make the needed validations on the read parameters

	// 5- Clear status bar
	pOut->ClearStatusBar();
}

void AddFlagAction::Execute()
{
	// The first line of any Action Execution is to read its parameter first 
	// and hence initializes its data members
	ReadActionParameters();
	if (flagPos.IsValidCell())
	{
		Flag* pFlag = new Flag(flagPos);
		Grid* pGrid = pManager->GetGrid();
		bool added = pGrid->AddObjectToCell(pFlag);
		if (!added) {
			pManager->GetOutput()->PrintMessage("Error! Cell aleardy occupied!");
			delete pFlag;
		}
		else {
			pManager->GetOutput()->PrintMessage("Flag added successfully. ");
		}

	}

	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below
	// == Here are some guideline steps (numbered below) to implement this function ==

	// 1-Create a flag object
	// 2-get a pointer to the Grid from the ApplicationManager
	// 3-Add the flag object to the GameObject of its Cell:
	// 4-Check if the flag was added and print an errror message if flag couldn't be added
	
}


AddFlagAction::~AddFlagAction()
{

}