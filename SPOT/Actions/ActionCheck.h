#pragma once
#include "Action.h"
#include "..\Registrar.h"
//Class responsible for checking everything
class ActionCheck :
	public Action
{
public:
	ActionCheck(Registrar*);
	bool Execute();
	void checkPreCo() const;
	void checkProReq() const;
	virtual ~ActionCheck();
};
