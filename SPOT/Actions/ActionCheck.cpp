#include "ActionCheck.h"

ActionCheck::ActionCheck(Registrar* p) :Action(p)
{
}
ActionCheck::~ActionCheck()
{
}

string ActionCheck::checkPreCo() const {
	return "";
}

bool ActionCheck::Execute() {
	return true;
}