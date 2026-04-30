#include "AddWaterPitAction.h"

AddWaterPitAction::AddWaterPitAction(ApplicationManager* pApp) :Action(pApp)
{

}

void AddWaterPitAction::ReadActionParameters() {
    Input* pIn = pManager->GetInput();
    Output* pOut = pManager->GetOutput();

    pOut->PrintMessage("Click on the cell to place the Water Pit...");

    pitPos = pIn->GetCellClicked();
     if (!pitPos.IsValidCell() || pitPos.GetCellNum() == 1 || pitPos.GetCellNum() == 55) 
     {
         pOut->PrintMessage("Error: Invalid cell position.");
         pitPos = CellPosition(-1, -1); // Set to invalid to prevent execution
     }
     pOut->ClearStatusBar();
}
void AddWaterPitAction::Execute() {
    ReadActionParameters(); // Step 1: Get parameters

    if (pitPos.IsValidCell()) {
        // Step 2: Create WaterPit object
        WaterPit* pPit = new WaterPit(pitPos);

        Grid* pGrid = pManager->GetGrid();
    
         bool added = pGrid->AddObjectToCell(pPit);

        if (!added) {
            pManager->GetOutput()->PrintMessage("Error: Cell already occupied!");
            delete pPit;
        }
        else {
            pManager->GetOutput()->PrintMessage("Water Pit added successfully.");
        }
    }
}