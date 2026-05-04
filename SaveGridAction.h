#pragma once
#include "Action.h"
class SaveGridAction :
    public Action
{
public:
    string FileName;
    SaveGridAction(ApplicationManager* pApp);
    virtual void ReadActionParameters(); // Usually empty for Save
    virtual void Execute();
};

