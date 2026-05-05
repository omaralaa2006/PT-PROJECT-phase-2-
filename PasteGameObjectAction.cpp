#include"PasteGameObjectAction.h"
#include "Grid.h"
#include"CopyGameObjectAcion.h"
#include"Output.h"
#include"Input.h"
#include"GameObject.h"
#include"Antenna.h"
#include"Flag.h"
#include"Belt.h"
#include"DangerZone.h"
#include"RotatingGear.h"
#include"WaterPit.h"
#include"Workshop.h"

PasteGameObjectAction::PasteGameObjectAction(ApplicationManager* pApp):Action(pApp)
{
}

void PasteGameObjectAction::ReadActionParameters() {
    Grid* pGrid = pManager->GetGrid();
    Output* pOut = pManager->GetOutput();
    Input* pIn = pManager->GetInput();

    pOut->PrintMessage("Click on the cell where you want to paste...");
    cellPos = pIn->GetCellClicked(); 
    pOut->ClearStatusBar();
}

void PasteGameObjectAction::Execute() {
    ReadActionParameters();
    Grid* pGrid = pManager->GetGrid();
    GameObject* pCopySource = pGrid->GetClipboard();
    Cell* ptargetcell = pGrid->GetCell(cellPos);
    if (pCopySource == NULL) {
        pGrid->PrintErrorMessage("Error: Clipboard is empty! Copy something first.");
        return;
    }

    // Check if the destination cell is already occupied
    if (ptargetcell->GetGameObject() != NULL) {
        pGrid->PrintErrorMessage("Error: Destination cell is occupied!");
        return;
    }
    GameObject* pClipboardObj = pGrid->GetClipboard();
    ActionType type = pClipboardObj->GetType();
    GameObject* pNewObj = NULL;
    if(type == SET_FLAG_CELL) {
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
        pNewObj = new Flag(cellPos);
	}
    else if (type == ADD_ROTATINGGEAR) {
        RotatingGear* pOldGear = dynamic_cast<RotatingGear*>(pClipboardObj);
        bool dir = pOldGear->GetisClockWise();
        pNewObj = new RotatingGear(cellPos, dir);
    }
    else if (type == ADD_BELT)
    {
        Belt* pOldBelt = dynamic_cast<Belt*>(pClipboardObj);

        // 1. Get the original start and end
        CellPosition oldStart = pOldBelt->GetPosition();
        CellPosition oldEnd = pOldBelt->GetEndPosition();

        // 2. Calculate the "Length" (distance)
        int diffV = oldEnd.VCell() - oldStart.VCell();
        int diffH = oldEnd.HCell() - oldStart.HCell();

        // 3. Create the NEW end based on the NEW click + the distance
        CellPosition newEnd(cellPos.VCell() + diffV, cellPos.HCell() + diffH);

        pNewObj = new Belt(cellPos, newEnd);
    }
    else if (type == ADD_ANTENNA) {
        pNewObj = new Antenna(cellPos);
    }
    else if (type == ADD_DANGER_ZONE) {
        pNewObj = new DangerZone(cellPos);
    }
    else if (type == ADD_WATER_PIT) {
        pNewObj = new WaterPit(cellPos);
    }
    else if (type == ADD_WORKSHOP) {
        pNewObj = new Workshop(cellPos);
    }
    if (pNewObj != NULL) {
        pGrid->AddObjectToCell(pNewObj);

    }
}

PasteGameObjectAction::~PasteGameObjectAction()
{
}
