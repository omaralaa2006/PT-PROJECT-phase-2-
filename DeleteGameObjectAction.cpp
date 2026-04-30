#include "DeleteGameObjectAction.h"
#include "Input.h"
#include "Output.h"
#include "Grid.h"

DeleteGameObjectAction::DeleteGameObjectAction(ApplicationManager* pApp) : Action(pApp) 
{
}

void DeleteGameObjectAction::ReadActionParameters() {
    Input* pIn = pManager->GetInput();
    Output* pOut = pManager->GetOutput();

    pOut->PrintMessage("Click on the object you want to delete...");
    cellPos = pIn->GetCellClicked();
    if (!cellPos.IsValidCell()) {
        pOut->PrintMessage("Error: Clicked outside the grid!");
        cellPos = CellPosition(-1, -1);
    }
}

void DeleteGameObjectAction::Execute() {
    ReadActionParameters();
    if (cellPos.IsValidCell()) {
        Grid* pGrid = pManager->GetGrid();
        Output* pOut = pManager->GetOutput();
        Cell* pCell = pGrid->GetCell(cellPos);

        if (pCell != NULL) {
            GameObject* pObj = pCell->GetGameObject();

            if (pObj != NULL) {
                bool removed = pGrid->RemoveObjectFromCell(cellPos);
                if (removed) {
                    pOut->PrintMessage("Object deleted successfully.");
                }
            }
            else {
                pOut->PrintMessage("Error: No object exists in this cell!");
            }
        }
    }
}

DeleteGameObjectAction::~DeleteGameObjectAction() {}