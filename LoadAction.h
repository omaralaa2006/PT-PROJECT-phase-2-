#pragma once
#include "Action.h"
class LoadAction :
    public Action
{
    string FileName;
    LoadAction(ApplicationManager* pApp);
    //virtual void ReadActionParameters(); // Usually empty for Save
    virtual void Execute();
};

