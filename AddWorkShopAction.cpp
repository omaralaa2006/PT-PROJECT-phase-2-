#include "AddWorkShopAction.h"
#include "Input.h"
#include "Output.h"
#include "Grid.h"
#include "Workshop.h" 
AddWorkShopAction::AddWorkShopAction(ApplicationManager* pApp) : Action(pApp) {}

void AddWorkShopAction::ReadActionParameters() {
    Input* pIn = pManager->GetInput();
    Output* pOut = pManager->GetOutput();

    pOut->PrintMessage("Click on the cell to place a Workshop...");
    workshopPos = pIn->GetCellClicked();

    
    if (!workshopPos.IsValidCell() || workshopPos.GetCellNum() == 1 || workshopPos.GetCellNum() == 55) 
    {
        pOut->PrintMessage("Error: Invalid cell position.");
        workshopPos = CellPosition(-1, -1);
    }
    pOut->ClearStatusBar();
}

void AddWorkShopAction::Execute() 
{
    ReadActionParameters();
    if (workshopPos.IsValidCell()) 
    {
        Workshop* pWorkshop = new Workshop(workshopPos);
        Grid* pGrid = pManager->GetGrid();
        bool added = pGrid->AddObjectToCell(pWorkshop);
        if (!added) 
        {
            pManager->GetOutput()->PrintMessage("Error: Cell already occupied!");
            delete pWorkshop;
        }
        else{
                pManager->GetOutput()->PrintMessage("Workshop added successfully.");
            }
        }
}

AddWorkShopAction::~AddWorkShopAction() {}