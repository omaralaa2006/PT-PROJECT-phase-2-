#include "CopyGameObjectAction.h"
#include "DeleteGameObjectAction.h"
#include "Input.h"
#include "Output.h"
#include "Grid.h"

CopyGameObjectAction::CopyGameObjectAction(ApplicationManager* pApp) : Action(pApp)
{
}
void CopyGameObjectAction::ReadActionParameters() {
    Input* pIn = pManager->GetInput();
    Output* pOut = pManager->GetOutput();

    pOut->PrintMessage("Click on the object you want to copy...");
    cellPos = pIn->GetCellClicked();
    if (!cellPos.IsValidCell()) {
        pOut->PrintMessage("Error: Clicked outside the grid!");
        cellPos = CellPosition(-1, -1);
    }
}
void CopyGameObjectAction::Execute() {
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
                pOut->PrintMessage("Object copied to clipboard!");
            }
            else {
                pOut->PrintMessage("Error: The clicked cell is empty!");
            }
        }
    }
}
CopyGameObjectAction::~CopyGameObjectAction()
{
}
