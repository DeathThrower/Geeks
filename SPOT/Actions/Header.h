#pragma once
#include "Action.h"
//Class responsible for deleting course action
class ActionDeleteCourse :
	public Action
{
public:
	ActionDeleteCourse(Registrar*);
	bool virtual Execute();
	virtual ~ActionDeleteCourse();
};
