#pragma once
#include "Action.h"
class CutGameObjectAction :
    public Action
{
    CellPosition cellPos;
public:
    CutGameObjectAction(ApplicationManager* pApp);
    virtual void ReadActionParameters();
    virtual void Execute();
    virtual ~CutGameObjectAction();
};


