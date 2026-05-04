#pragma once
#include "Action.h"
#include<string>
class LoadAction :
    public Action
{
public:
    string FileName;
    LoadAction(ApplicationManager* pApp);
    virtual void ReadActionParameters(); // Usually empty for Save
    virtual void Execute();
};

