#pragma once
#include "Action.h"
#include "..\Registrar.h"


//Class responsible for importing rules from file
class ActionLoadRules : public Action {
public:
	ActionLoadRules(Registrar*);
	bool Execute();
	virtual ~ActionLoadRules();
};