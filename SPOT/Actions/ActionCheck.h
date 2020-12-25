#pragma once
#include "Action.h"
//Class responsible for checking everything
class ActionCheck :
	public Action
{
public:
	ActionCheck(Registrar*);
	bool Execute();
	virtual ~ActionCheck();
};
