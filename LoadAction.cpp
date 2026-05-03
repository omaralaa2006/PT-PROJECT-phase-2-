#include "LoadAction.h"
#include<fstream>
#include "Grid.h"
#include"Flag.h"
#include"Belt.h"

using namespace std;
LoadAction::LoadAction(ApplicationManager* pApp):Action(pApp)
{
}
void LoadAction::Execute() {
    ReadActionParameters();
    ifstream InFile(FileName);

    if (InFile.is_open()) {
        Grid* pGrid = pManager->GetGrid();
        pGrid->ClearGrid(); 
        int count;
        InFile >> count;
        for (int i = 0; i < count; i++) {
            Flag* pFlag = new Flag(CellPosition(-1));
            pFlag->Load(InFile);
            pGrid->AddObjectToCell(pFlag);
        }
        InFile >> count;
        for (int i = 0; i < count; i++) {
            Belt* pBelt = new Belt(CellPosition(-1), CellPosition(-1));
            pBelt->Load(InFile);
            pGrid->AddObjectToCell(pBelt);
        }
        InFile.close();
    }
}