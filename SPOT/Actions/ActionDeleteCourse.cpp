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
		//CourseInfo co;
		//pGUI->PrintMsg("Add Course to plan: Enter course Code(e.g. CIE202):");
		//Course_Code code = pGUI->GetSrting();
		/*co = pReg->getCourseInfo(pReg->getRules(), code);
		while (co.Code == "") {
			pGUI->PrintMsg("Error!! unknown course code, please try again");
			Course_Code code = pGUI->GetSrting();
			co = pReg->getCourseInfo(pReg->getRules(), code);
		}*/
		StudyPlan* pS = pReg->getStudyPlan();
		pS->DeleteCourse(x, y);
		/*course->setDone(done);
		course->setPreReq(PreReq);
		course->setCoReq(CoReq);
		course->setTitle(title);*/
		return true;
	}
	return false;
}


