#pragma once
#include "Action.h"
#include "..\Registrar.h"


//Class responsible for importing studyplan from file
class ActionLoadRules : public Action {
public:
	ActionLoadRules(Registrar*);
	bool virtual Execute();
	virtual ~ActionLoadRules();
};