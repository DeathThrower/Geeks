#pragma once
#include "Action.h"
//Class responsible for selecting course status
class ActionSelectCourseStatus :
	public Action
{
public:
	ActionSelectCourseStatus(Registrar*);
	bool Execute();
	bool Execute(int cx, int cy);
	virtual ~ActionSelectCourseStatus();
};