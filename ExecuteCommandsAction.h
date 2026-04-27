#pragma once
#include "Action.h"
class ExecuteCommandsAction : public Action
{
public:
	ExecuteCommandsAction(ApplicationManager* pApp);
	virtual void ReadActionParameters();
	virtual void Execute();
	virtual ~ExecuteCommandsAction();
};