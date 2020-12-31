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

		Course* course = pReg->getStudyPlan()->getCourse(x, y);
		if (course == NULL) {
			pReg->getGUI()->PrintMsg("Error!!! there is no course here ... press any key to exit this state");
			char temp;
			pReg->getGUI()->getWindow()->WaitKeyPress(temp);
			return false;
		}

		course->setSelected(true);  //making a frame around the course
		pReg->UpdateInterface();

		//getting the course info from course catalog according to the course code given from the user
		CourseInfo co;
		pGUI->PrintMsg("Add Course to plan: Enter course Code(e.g. CIE202):");
		Course_Code code = pGUI->GetSrting();
		co = pReg->getCourseInfo(code);
		while (co.Code == "") {
			pGUI->PrintMsg("Error!! unknown course code, please try again");
			Course_Code code = pGUI->GetSrting();
			co = pReg->getCourseInfo(code);
		}
		//setting every thing in the old course with the info given from getcourseinfo funtion
		course->setCode(co.Code);
		course->setCredits(co.Credits);
		course->setPreReq(co.PreReqList);
		course->setCoReq(co.CoReqList);
		course->setTitle(co.Title);
		course->setType(pReg->getCourseType(co.Code));

		course->setSelected(false);  // clear the frame 
		pReg->UpdateInterface();
		return true;
	}
	return false;
}


ActionReplaceCourse::~ActionReplaceCourse()
{
}
