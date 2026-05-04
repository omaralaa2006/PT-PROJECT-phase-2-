#include "LoadAction.h"
#include<fstream>
#include "Grid.h"
#include"Flag.h"
#include"Belt.h"
#include"Antenna.h"
#include"DangerZone.h"
#include"RotatingGear.h"
#include"WaterPit.h"
#include"Workshop.h"
using namespace std;
LoadAction::LoadAction(ApplicationManager* pApp):Action(pApp)
{
}
void LoadAction::ReadActionParameters()
{
}
void LoadAction::Execute() {
    ReadActionParameters();
    ifstream InFile("AutoSave.txt");

    if (InFile.is_open()) {
        Grid* pGrid = pManager->GetGrid();
        const GameState* pState = pManager->GetGameState();
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
        InFile >> count;
        for (int i = 0; i < count; i++) {
            Antenna* pAntenna = new Antenna(CellPosition(-1));
            pAntenna->Load(InFile);
            pGrid->AddObjectToCell(pAntenna);
        }
        InFile >> count;
        for (int i = 0; i < count; i++) {
            DangerZone* pDz = new DangerZone(CellPosition(-1));
            pDz->Load(InFile);
            pGrid->AddObjectToCell(pDz);
        }
        InFile >> count;
        for (int i = 0; i < count; i++) {
            RotatingGear* prg = new RotatingGear(CellPosition(-1),true);
            prg->Load(InFile);
            pGrid->AddObjectToCell(prg);
        }
        InFile >> count;
        for (int i = 0; i < count; i++) {
            WaterPit* pw = new WaterPit(CellPosition(-1));
            pw->Load(InFile);
            pGrid->AddObjectToCell(pw);
        }
        InFile >> count;
        for (int i = 0; i < count; i++) {
            Workshop* pws = new Workshop(CellPosition(-1));
            pws->Load(InFile);
            pGrid->AddObjectToCell(pws);
        }
        InFile.close();
        pGrid->UpdateInterface(pState);
        pManager->GetOutput()->PrintMessage("grid loaded successfully!");
    }
}