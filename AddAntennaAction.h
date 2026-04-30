#pragma once
#include "Action.h"
class AddAntennaAction :
    public Action
{
    CellPosition antennaPos;
public:
    AddAntennaAction(ApplicationManager* pApp);
    virtual void ReadActionParameters();
    virtual void Execute();
    virtual ~AddAntennaAction();
};

