#pragma once
#include "Action.h"
#include "..\Registrar.h"


//Class responsible for saveing studyplan to a file
class ActionSaveStudyPlan : public Action {
public:
	ActionSaveStudyPlan(Registrar*);
	string savefilename(char* filter = "Text Documents (*.txt)\0*.txt\0", HWND owner = NULL) const;
	bool Execute();
	virtual ~ActionSaveStudyPlan();
};