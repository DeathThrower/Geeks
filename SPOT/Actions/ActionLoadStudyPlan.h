#pragma once
#include "Action.h"
#include "..\Registrar.h"


//Class responsible for importing studyplan from file
class ActionLoadStudyPlan : public Action {
public:
	ActionLoadStudyPlan(Registrar*);
	string openfilename(string title, char* filter = "Text Documents (*.txt)\0*.txt\0", HWND owner = NULL) const;
	bool Execute();
	virtual ~ActionLoadStudyPlan();
};