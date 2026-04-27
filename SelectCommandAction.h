#pragma once
#include "Action.h"
class SelectCommandAction : public Action
{
	Command selectedCommand;

public:
	SelectCommandAction(ApplicationManager* pApp);
	virtual void ReadActionParameters();
	virtual void Execute();
	virtual ~SelectCommandAction();
};