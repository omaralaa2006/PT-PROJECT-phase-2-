#include "AddDangerZoneAction.h"
#include "Input.h"
#include "Output.h"
#include "Grid.h"
#include "DangerZone.h" 

AddDangerZoneAction::AddDangerZoneAction(ApplicationManager* pApp) : Action(pApp)
{
}

void AddDangerZoneAction::ReadActionParameters() {
    Input* pIn = pManager->GetInput();
    Output* pOut = pManager->GetOutput();

    pOut->PrintMessage("Click on the cell to place a Danger Zone...");
    zonePos = pIn->GetCellClicked();
     if (!zonePos.IsValidCell() || zonePos.GetCellNum() == 1 || zonePos.GetCellNum() == 55) 
     {
         pOut->PrintMessage("Error: Invalid cell position.");
         zonePos = CellPosition(-1, -1);
     }
     pOut->ClearStatusBar();
}

void AddDangerZoneAction::Execute() {
    ReadActionParameters(); 
    if (zonePos.IsValidCell())
    {
        DangerZone* pZone = new DangerZone(zonePos);
        Grid* pGrid = pManager->GetGrid();
        bool added = pGrid->AddObjectToCell(pZone);
        if (!added) 
        {
            pManager->GetOutput()->PrintMessage("Error: Cell already occupied!");
            delete pZone; 
        }
        else 
        {
            pManager->GetOutput()->PrintMessage("Danger Zone added successfully.");
        }
    }
}

AddDangerZoneAction::~AddDangerZoneAction() {}