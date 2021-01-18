#include "ActionAddCourse.h"
#include "..\Registrar.h"
#include "../Courses/UnivCourse.h"
#include<string>
ActionAddCourse::ActionAddCourse(Registrar* p) :Action(p)
{
}

bool ActionAddCourse::Execute()
{
	GUI* pGUI = pReg->getGUI();
	CourseInfo co;
	pGUI->PrintMsg("Add Course to plan: Enter course Code(e.g. CIE202):");
	Course_Code code = pGUI->GetSrting();

	co = pReg->getCourseInfo(code);
	while (co.Code == "") {
		pGUI->PrintMsg("Error!! unknown course code, please try again");
		Course_Code code = pGUI->GetSrting();
		co = pReg->getCourseInfo(code);
	}



	ActionData actData = pGUI->GetUserAction("Select a year to add coures to: ");
	//TODO: add input validation

	int x, y;

	if (actData.actType == DRAW_AREA)	//user clicked inside drawing area
	{
		//get coord where user clicked
		x = actData.x;
		y = actData.y;
		if (!(15 < x && x < 1330 && 205 < y && y < 685)) return false;


		Course* pC = new Course(co.Code, co.Title, co.Credits);
		pC->setPreReq(co.PreReqList);
		pC->setCoReq(co.CoReqList);
		pC->setType(pReg->getCourseType(co.Code));


		StudyPlan* pS = pReg->getStudyPlan();
		vector<int> sy = pS->getSem_Year(x, y);
		int year = sy.at(1);
		int sem = sy.at(0);
		if (sem == -1) { return false; }
		SEMESTER SEM = static_cast<SEMESTER>(sem);
		auto course = pS->getCourse(x, y);
		auto plan = pS->getPlan();
		auto YEAR = plan[year];
		auto SEM_ = YEAR->getCourses(sem);
		graphicsInfo g;
		if (SEM_.size()) {
			auto c = SEM_.end();
			auto f = c - 1;
			g = (*f)->getGfxInfo();
			g.y += 45;
		}
		else {
			g.x = year * 263 + 20 + sem * 88;
			g.y = 215;
		}
		pC->setGfxInfo(g);
		pS->AddCourse(pC, year + 1 , SEM , pReg);
	}


	//TODO:


	return true;
}


ActionAddCourse::~ActionAddCourse()
{
}
