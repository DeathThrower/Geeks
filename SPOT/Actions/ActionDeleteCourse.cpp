#include "ActionDeleteCourse.h"
#include "..\Registrar.h"
#include "../Courses/UnivCourse.h"

ActionDeleteCourse::ActionDeleteCourse(Registrar* p) :Action(p)
{
}
ActionDeleteCourse::~ActionDeleteCourse()
{
}

bool ActionDeleteCourse::Execute()
{
	GUI* pGUI = pReg->getGUI();
	ActionData actData = pGUI->GetUserAction("Select a Course to be deleted");
	//TODO: add input validation
	int x, y;
	if (actData.actType == DRAW_AREA)	//user clicked inside drawing area
	{
		//get coord where user clicked
		x = actData.x;
		y = actData.y;
		StudyPlan* pS = pReg->getStudyPlan();
		pS->DeleteCourse(x, y);
		return true;
	}
	return false;
}


