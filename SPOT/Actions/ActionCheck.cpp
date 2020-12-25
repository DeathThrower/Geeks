#include "ActionCheck.h"

ActionCheck::ActionCheck(Registrar* p) :Action(p)
{
}
ActionCheck::~ActionCheck()
{
}

void ActionCheck::checkPreCo() const {
	string Msg = pReg->getStudyPlan()->checkpreReqCoreReq();
	pReg->getGUI()->PrintMsg(Msg + " ... Press any key if you finished reading");
	char temp;
	pReg->getGUI()->getWindow()->WaitKeyPress(temp);  // wait for the user to finish reading the message
}

bool ActionCheck::Execute() {
	checkPreCo();
	return true;
}