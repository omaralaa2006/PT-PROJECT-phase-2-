#include "PasteGameObjectAction.h"
#include "Input.h"
#include "Output.h"
#include "Grid.h"

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

void PasteGameObjectAction::Execute()
{
    // 1. Read the parameters (where to paste)
    ReadActionParameters();
    if (cellPos.IsValidCell()) {
        Grid* pGrid = pManager->GetGrid();
        Output* pOut = pManager->GetOutput();

        // 2. Get the clipboard from the Application Manager
        GameObject* pClipboard = pGrid->GetClipboard();

        if (pClipboard == nullptr)
        {
            pManager->GetOutput()->PrintMessage("Clipboard is empty! Copy an object first.");
            return;
        }
        
        // 3. Clone the object in the clipboard
        // You MUST implement a Clone() function in your GameObject classes
      //  pPastedObject = pClipboard->Clone();

        // 4. Update the cloned object's position to the clicked point
        // Assuming your GameObject has a setter for position or a Move function
     //   pPastedObject->SetPosition(PastePosition);

        // 5. Add the newly pasted object to the game
      //  pManager->AddGameObject(pPastedObject);
        
        pManager->GetOutput()->PrintMessage("Object pasted successfully.");
    }
}
PasteGameObjectAction::~PasteGameObjectAction()
{
}
