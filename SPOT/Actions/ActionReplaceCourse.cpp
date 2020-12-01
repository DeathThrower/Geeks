#include "ActionReplaceCourse.h"
#include "..\Registrar.h"

ActionReplaceCourse::ActionReplaceCourse(Registrar* p) :Action(p)
{
}

bool ActionReplaceCourse::Execute()
{
	GUI* pGUI = pReg->getGUI();
	ActionData actData = pGUI->GetUserAction("Select a Course to be replaced");
	//TODO: add input validation
	int x, y;
	if (actData.actType == DRAW_AREA)	//user clicked inside drawing area
	{
		//get coord where user clicked
		x = actData.x;
		y = actData.y;
		//CourseInfo co;
		pGUI->PrintMsg("Add Course to plan: Enter course Code(e.g. CIE202):");
		Course_Code code = pGUI->GetSrting();
		/*co = pReg->getCourseInfo(pReg->getRules(), code);
		while (co.Code == "") {
			pGUI->PrintMsg("Error!! unknown course code, please try again");
			Course_Code code = pGUI->GetSrting();
			co = pReg->getCourseInfo(pReg->getRules(), code);
		}*/
		Course * course = pReg->getStudyPlan()->getCourse(x, y);
		course->setCode(code);
		course->setCredits(2);
		/*course->setDone(done);
		course->setPreReq(PreReq);
		course->setCoReq(CoReq);
		course->setTitle(title);*/
		return true;
	}
	return false;
}


ActionReplaceCourse::~ActionReplaceCourse()
{
}
