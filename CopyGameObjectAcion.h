#pragma once
#include "Action.h"
class CopyGameObjectAction :
    public Action
{
    CellPosition cellPos;
public:
    CopyGameObjectAction(ApplicationManager* pApp);
    virtual void ReadActionParameters();
    virtual void Execute();
    virtual ~CopyGameObjectAction();
};

