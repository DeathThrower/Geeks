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
	void generateReport() const;
	virtual ~ActionCheck();
};
