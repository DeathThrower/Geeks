#pragma once
#include "Action.h"
#include "..\Registrar.h"


//Class responsible for saveing studyplan to a file
class ActionSaveStudyPlan : public Action {
public:
	ActionSaveStudyPlan(Registrar*);
	bool virtual Execute();
	virtual ~ActionSaveStudyPlan();
};