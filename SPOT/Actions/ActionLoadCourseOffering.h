#pragma once
#include "Action.h"
#include "..\Registrar.h"


//Class responsible for importing Course Offering from file
class ActionLoadCourseOffering : public Action {
public:
	ActionLoadCourseOffering(Registrar*);
	bool virtual Execute();
	virtual ~ActionLoadCourseOffering();
};