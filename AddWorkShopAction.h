#pragma once
#include "Action.h"
class AddWorkShopAction :
    public Action
{
    CellPosition workshopPos; 
public:
    AddWorkShopAction(ApplicationManager* pApp);
    virtual void ReadActionParameters(); 
    virtual void Execute(); 
    virtual ~AddWorkShopAction();
};

