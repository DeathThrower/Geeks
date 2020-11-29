#pragma once
#include "Action.h"
#include "..\Registrar.h"


//Class responsible for importing Course Offering from file
class ActionLoadCourseOffering : public Action {
public:
	ActionLoadCourseOffering(Registrar*);
	bool Execute();
	virtual ~ActionLoadCourseOffering();
};