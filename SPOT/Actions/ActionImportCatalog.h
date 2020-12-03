#pragma once
#include "Action.h"
#include "..\Registrar.h"


//Class responsible for importing course catalog from a file
class ActionImportCatalog : public Action {
public:
	ActionImportCatalog(Registrar*);
	bool Execute();
	virtual ~ActionImportCatalog();
};