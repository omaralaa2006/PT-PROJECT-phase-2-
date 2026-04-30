#pragma once
#include "Action.h"

class AddDangerZoneAction : public Action
{
    CellPosition zonePos; 
public:
    AddDangerZoneAction(ApplicationManager* pApp);
    virtual void ReadActionParameters(); 
    virtual void Execute(); 
    virtual ~AddDangerZoneAction();
};
