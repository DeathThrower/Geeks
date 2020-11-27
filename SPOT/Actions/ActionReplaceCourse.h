#pragma once
#include "Action.h"
//Class responsible for replacinging course action
class ActionReplaceCourse :
	public Action
{
public:
	ActionReplaceCourse(Registrar*);
	bool virtual Execute();
	virtual ~ActionReplaceCourse();
};
