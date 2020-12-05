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
	pGUI->PrintMsg("Enter Code Title :");
	string Title = pGUI->GetSrting();
	pGUI->PrintMsg("Enter Code Credits :");
	string crds = pGUI->GetSrting();
	int crd = std::stoi(crds);
	/*co = pReg->getCourseInfo(pReg->getRules(), code);
	while (co.Code == "") {
		pGUI->PrintMsg("Error!! unknown course code, please try again");
		Course_Code code = pGUI->GetSrting();
		co = pReg->getCourseInfo(code);
	}*/



	ActionData actData = pGUI->GetUserAction("Select a year to add coures to:(To be implemented in phase1) we will just draw coures where user clicks");
	//TODO: add input validation

	int x, y;

	if (actData.actType == DRAW_AREA)	//user clicked inside drawing area
	{
		//get coord where user clicked
		x = actData.x;
		y = actData.y;



		//graphicsInfo gInfo{ x, y };

		//TODO: given course code, get course title, crd hours from registrar
		//For now, we will add any dummy values
		//string Title = "Test101";
		//int crd = 0;
		string Title = "Hello";
		Course* pC = new Course(code, Title, crd);
		//pC->setPreReq(co.PreReqList);
		//pC->setCoReq(co.CoReqList);
		//pC->setType(pReg->getCourseType(co.Code));
		//pC->setGfxInfo(gInfo);

		//TODO: Ask registrar to add course to the year selected by the user
		//TODO: add the course to the correct year obtained from registrar

		//For the seke of demo, we will add the course to the 1st year, 1st semester
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
			g.x = year * 265 + 175;
			g.y = 180;
		}
		pC->setGfxInfo(g);
		pS->AddCourse(pC, year + 1, SEM);
	}


	//TODO:


	return true;
}


ActionAddCourse::~ActionAddCourse()
{
}
