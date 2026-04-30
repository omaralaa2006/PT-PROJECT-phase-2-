#pragma once
#include "Action.h"
class PasteGameObjectAction :
    public Action
{
private:
    CellPosition cellPos; 

public:
  
    PasteGameObjectAction(ApplicationManager* pApp);

  
    virtual void ReadActionParameters();

    // El-manteq el-fay'aly bta' el-Paste
    virtual void Execute();
    ~PasteGameObjectAction();
};

