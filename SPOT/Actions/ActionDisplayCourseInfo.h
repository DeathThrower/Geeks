#pragma once
#include "Action.h"
//Class responsible for displaying course info
class ActionDisplayCourseInfo :
	public Action
{
public:
	ActionDisplayCourseInfo(Registrar*);
	bool Execute();
	bool Execute(int cx, int cy);
	virtual ~ActionDisplayCourseInfo();
};