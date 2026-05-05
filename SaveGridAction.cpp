#include "SaveGridAction.h"
#include "Grid.h"
#include <fstream>
using namespace std;
SaveGridAction::SaveGridAction(ApplicationManager* pApp) : Action(pApp) {}

void SaveGridAction::ReadActionParameters() {}


void SaveGridAction::Execute() {
    ofstream OutFile("GridData.txt");
    if (OutFile.is_open()) {
        Grid* pGrid = pManager->GetGrid();

        // FOLLOW THE INSTRUCTION ORDER EXACTLY
        pGrid->SaveAll(OutFile, SET_FLAG_CELL);
        pGrid->SaveAll(OutFile, ADD_WATER_PIT);
        pGrid->SaveAll(OutFile, ADD_DANGER_ZONE);
        pGrid->SaveAll(OutFile, ADD_BELT);
        pGrid->SaveAll(OutFile, ADD_WORKSHOP);
        pGrid->SaveAll(OutFile, ADD_ANTENNA);
        pGrid->SaveAll(OutFile, ADD_ROTATINGGEAR);

        OutFile.close();
        pGrid->PrintErrorMessage("Grid saved successfully! Click to continue...");
    }
}

