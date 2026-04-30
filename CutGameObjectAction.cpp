#include "CutGameObjectAction.h"

#include "Input.h"
#include "Output.h"
#include "Grid.h"

CutGameObjectAction::CutGameObjectAction(ApplicationManager* pApp) : Action(pApp)
{
}
void CutGameObjectAction::ReadActionParameters() {
    Input* pIn = pManager->GetInput();
    Output* pOut = pManager->GetOutput();

    pOut->PrintMessage("Click on the object you want to cut...");
    cellPos = pIn->GetCellClicked();
    if (!cellPos.IsValidCell()) {
        pOut->PrintMessage("Error: Clicked outside the grid!");
        cellPos = CellPosition(-1, -1);
    }
}
void CutGameObjectAction::Execute() {
    ReadActionParameters();

    if (cellPos.IsValidCell()) {
        Grid* pGrid = pManager->GetGrid();
        Output* pOut = pManager->GetOutput();

        // Use the function we just implemented
        Cell* pCell = pGrid->GetCell(cellPos);

        if (pCell != NULL) {

            GameObject* pObj = pCell->GetGameObject();

            if (pObj != NULL) {
                pGrid->SetClipboard(pObj);
                pGrid->RemoveObjectFromCell(cellPos);
                pOut->PrintMessage("Object deleted and copied to clipboard!");
            }
            else {
                pOut->PrintMessage("Error: The clicked cell is empty!");
            }
        }
    }
}
CutGameObjectAction::~CutGameObjectAction()
{
}
