#pragma once
#include "Action.h"
//Class responsible for adding notes action
class ActionAddNotes :
	public Action
{
public:
	ActionAddNotes(Registrar*);
	bool Execute();
	virtual ~ActionAddNotes();
};

#pragma once
