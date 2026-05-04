#include "SaveGridAction.h"
#include "Grid.h"
#include <fstream>
using namespace std;
SaveGridAction::SaveGridAction(ApplicationManager* pApp) : Action(pApp) {}

void SaveGridAction::ReadActionParameters() {
   // Output* pOut = pManager->GetOutput();
   // Input* pIn = pManager->GetInput();
   // pOut->PrintMessage("please type the name of the file you want to save to (without extension) and click to continue ...");
    //FileName = pIn->GetSrting(pOut);
   // FileName += ".txt";

}

void SaveGridAction::Execute() {
    ofstream OutFile("AutoSave.txt"); // This creates the file
    if (OutFile.is_open()) {
        Grid* pGrid = pManager->GetGrid();
        pGrid->SaveAll(OutFile, SET_FLAG_CELL);
        pGrid->SaveAll(OutFile, ADD_WATER_PIT);
        pGrid->SaveAll(OutFile, ADD_BELT);
        pGrid->SaveAll(OutFile, ADD_ANTENNA);
        pGrid->SaveAll(OutFile, ADD_DANGER_ZONE);
        pGrid->SaveAll(OutFile, ADD_WORKSHOP);
        pGrid->SaveAll(OutFile, ADD_ROTATINGGEAR);
        pGrid->SaveAll(OutFile,ADD_WORKSHOP);
        OutFile.close();
        pManager->GetOutput()->PrintMessage("Design saved");
    }
}

