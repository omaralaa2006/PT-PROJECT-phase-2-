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
	Grid* pGrid = pManager->GetGrid();
	for (int i = 0; i < NumVerticalCells; i++) {
		for (int j = 0; j < NumHorizontalCells; j++) {
			GameObject* pObj = pGrid->GetCell(CellPosition(i, j))->GetGameObject();

			// Check if the object is a Flag
			if (pObj != NULL && pObj->GetType() == SET_FLAG_CELL) {
				pGrid->PrintErrorMessage("Error: Only one flag is allowed on the grid!");
				return; // Stop the action immediately
			}
		}
	}
	// --- NEW CHECK END ---

	// If we reached here, no flag was found. Proceed with normal adding:
	ReadActionParameters();
	Flag* pFlag = new Flag(flagPos);
	bool added = pGrid->AddObjectToCell(pFlag);

	if (!added) {
		pGrid->PrintErrorMessage("Error: Cell is already occupied!");
		delete pFlag;
	}
}




AddFlagAction::~AddFlagAction()
{

}