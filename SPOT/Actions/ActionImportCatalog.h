#pragma once
#include "Action.h"
#include "..\Registrar.h"


//Class responsible for saveing studyplan to a file
class ActionImportCatalog : public Action {
public:
	ActionImportCatalog(Registrar*);
	bool Execute();
	virtual ~ActionImportCatalog();
};