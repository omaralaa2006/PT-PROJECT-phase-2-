#include "PasteGameObjectAction.h"
#include "Input.h"
#include "Output.h"
#include "Grid.h"
#include "GameObject.h"

PasteGameObjectAction::PasteGameObjectAction(ApplicationManager* pApp) : Action(pApp)
{
}

void PasteGameObjectAction::ReadActionParameters()
{
    Input* pIn = pManager->GetInput();
    Output* pOut = pManager->GetOutput();

    pOut->PrintMessage("Click on where you want to paste...");
    cellPos = pIn->GetCellClicked();
    if (!cellPos.IsValidCell()) {
        pOut->PrintMessage("Error: Clicked outside the grid!");
        cellPos = CellPosition(-1, -1);
    }
}

void PasteGameObjectAction::Execute() {}
/*/
    // 1. Read parameters (the cell where the user wants to paste)
    ReadActionParameters();

    Grid* pGrid = pManager->GetGrid();
    Output* pOut = pManager->GetOutput();

    // 2. Check if the target cell is valid
    if (!cellPos.IsValidCell()) {
        pOut->PrintMessage("Invalid cell! Action aborted.");
        return;
    }

    // 3. Get the clipboard
    GameObject* pClipboard = pGrid->GetClipboard();
    if (pClipboard == nullptr) {
        pOut->PrintMessage("Clipboard is empty! Copy an object first.");
        return;
    }

    // 4. Check if the cell is already occupied (optional but recommended)
    if (pGrid->GetGameObject(cellPos) != nullptr) {
        pOut->PrintMessage("Cell is already occupied!");
        return;
    }

    // 5. Create a copy of the object from the clipboard
    // IMPORTANT: You need a virtual 'Copy' function in your GameObject class
    // that returns a new instance of the same type.
    GameObject* pNewObj = pClipboard->Copy();

    // 6. Set the position of the new object to the target cell
    pNewObj->SetPosition(cellPos);

    // 7. Add the new object to the grid
    if (pGrid->AddObject(pNewObj)) {
        // 8. Draw the object
        pNewObj->Draw(pOut);
        pOut->PrintMessage("Object pasted successfully.");
    }
    else {
        pOut->PrintMessage("Error: Could not add object to grid.");
        delete pNewObj; // Cleanup if adding fails
    }
}*/
PasteGameObjectAction::~PasteGameObjectAction()
{
}
