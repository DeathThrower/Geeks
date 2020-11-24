#pragma once
#include "Action.h"
#include "..\Registrar.h"


//Class responsible for importing studyplan from file
class ActionLoadStudyPlan : public Action {
public:
	ActionLoadStudyPlan(Registrar*);
	bool virtual Execute();
	virtual ~ActionLoadStudyPlan();
};