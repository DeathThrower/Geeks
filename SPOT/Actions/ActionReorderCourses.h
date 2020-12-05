#pragma once
#include "Action.h"
//Class responsible for replacinging course action
class ActionReorderCourses :
	public Action
{
public:
	ActionReorderCourses(Registrar*);
	bool Execute();
	virtual ~ActionReorderCourses();
};
