#include "AddRotatingGearAction.h"

AddRotatingGearAction::AddRotatingGearAction(ApplicationManager * pApp):Action(pApp)
{
}

void AddRotatingGearAction::ReadActionParameters()
{
	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below


	// == Here are some guideline steps (numbered below) to implement this function ==

	// 1- Get a Pointer to the Input / Output Interfaces
	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();
	pOut->PrintMessage("Click on the cell to place the Rotating gear....");
	// 2- Read the gearPos
	gearPos = pIn->GetCellClicked();
	// 3- Read whether the direction will be clockwise or not

	// 4- Make the needed validations on the read parameters
	if (!gearPos.IsValidCell()||gearPos.GetCellNum()==1||gearPos.GetCellNum()==55)
	{
		pOut->PrintMessage("Error ! invalid cell position.");
		gearPos = CellPosition(-1, -1);
		return;
	}
	pOut->PrintMessage("Enter Rotation:1 for cw ,0 for ccw");
	int dir = pIn->GetInteger(pOut);
	clockwise = (dir == 1);
	// 5- Clear status bar
	pOut->ClearStatusBar();
}

void AddRotatingGearAction::Execute()
{
	// The first line of any Action Execution is to read its parameter first 
	// and hence initializes its data members
	ReadActionParameters();
	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below
	// == Here are some guideline steps (numbered below) to implement this function ==

	// 1-Create a rotating gear object
	if (gearPos.IsValidCell()) 
	{
		RotatingGear* pGear = new RotatingGear(gearPos, clockwise);
		Grid* pGrid = pManager->GetGrid();
		Output* pOut = pManager->GetOutput();
	
		if (!pGrid->AddObjectToCell(pGear))
		{
			pOut->PrintMessage("Error!Cell alredy occupied!");
			delete pGear;
		}
	}
	// 2-get a pointer to the Grid from the ApplicationManager
	// 3-Add the rotating object to the GameObject of its Cell:
	// 4-Check if the rotating gear was added and print an errror message if flag couldn't be added
}

AddRotatingGearAction::~AddRotatingGearAction()
{
}
