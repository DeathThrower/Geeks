#include "Registrar.h"
#include "Actions/ActionAddCourse.h"
#include "Actions/ActionLoadStudyPlan.h"
#include "Actions/ActionSaveStudyPlan.h"
#include "Actions/ActionLoadCourseOffering.h"
#include "Actions/ActionReplaceCourse.h"
#include "Actions/ActionDeleteCourse.h"
#include "Actions/ActionLoadRules.h"
#include<iostream>

string Registrar::openfilename(string title ,char* filter , HWND owner) const {
	OPENFILENAME ofn;
	char fileName[MAX_PATH]="";
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = owner;
	ofn.lpstrFilter = filter;
	ofn.lpstrFile = fileName;
	ofn.nMaxFile = MAX_PATH;
	ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
	ofn.lpstrDefExt = "";
	ofn.lpstrTitle = title.c_str();
	string fileNameStr="";
	if (GetOpenFileName(&ofn)) {
		fileNameStr = fileName;
	}
	return fileNameStr;
}

string Registrar::savefilename( char* filter , HWND owner) const {
	OPENFILENAME ofn;
	char fileName[MAX_PATH] = ".txt";
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = owner;
	ofn.lpstrFilter = filter;
	ofn.lpstrFile = fileName;
	ofn.nMaxFile = MAX_PATH;
	ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
	ofn.lpstrDefExt = "";
	string fileNameStr;
	if (GetSaveFileName(&ofn)) {
		fileNameStr = fileName;
	}
	return fileNameStr;
}


CourseInfo Registrar::getCourseInfo(Rules* myrules, Course_Code CC) const{
	for (CourseInfo i : myrules->CourseCatalog) {
		if (i.Code == CC) {
			return i;
		}
	}
	CourseInfo empty;
	empty.Code = "";
	return empty;
}


SEMESTER Registrar::str2sem(string str) const {
	if (str == "Fall" || str == "fall") {
		return FALL;
	}
	else if (str == "Spring" || str == "spring") {
		return SPRING;
	}
	else if (str == "Summer" || str == "summer") {
		return SUMMER;
	}
	return SEM_CNT;
}

string Registrar::sem2str(SEMESTER sem) const {
	switch (sem)
	{
	case FALL:
		return "Fall";
		break;
	case SPRING:
		return "Spring";
		break;
	case SUMMER:
		return "Summer";
		break;
	case SEM_CNT:
		return "";
		break;
	default:
		return "";
		break;
	}
}



Course* Registrar::getCourse(int x, int y) const
{
	int cX, cY;
	for (auto year : getStudyPlan()->getPlan())
	{
		for (int sem = 0; sem <= 2; sem++)
		{
			for (auto course : year->getCourses(sem))
			{
				//height =40 width=80
				graphicsInfo ginfo = course->getGfxInfo();
				cX = ginfo.x; cY = ginfo.y;
				if ( cX <= x && cX+80 >= x && cY <= y && cY + 40 >= y) {
					return course;
				}
			}
		}
	}
	Course* p = &Course("", "", 0);
	return p;
}

void Registrar::displayCourseInfo( int x, int y)
{
	Course* course = getCourse(x, y);
	getGUI()->PrintMsg("Course Name: " + course->getCode() + " No. of credits: " + to_string(course->getCredits()));
}

Registrar::Registrar()
{
	pGUI = new GUI;	//create interface object
	pSPlan = new StudyPlan;	//create a study plan.
	pRegRules = new Rules;  // create a Rules struct
	ActionLoadCourseOffering(this).Execute();
}

//return a pointer to Rules
Rules* Registrar::getRules() const {
	return pRegRules;
}

//returns a pointer to GUI
GUI* Registrar::getGUI() const
{
	return pGUI;
}

//returns the study plan
StudyPlan* Registrar::getStudyPlan() const
{
	return pSPlan;
}

Action* Registrar::CreateRequiredAction() 
{	
	ActionData actData = pGUI->GetUserAction("Pick and action...");
	Action* RequiredAction = nullptr;

	switch (actData.actType)
	{
	case ADD_CRS:	//add_course action
		RequiredAction = new ActionLoadStudyPlan(this);// ActionAddCourse(this);  //error don't forget to fix it
		break;

	case LOAD:
		RequiredAction = new ActionLoadStudyPlan(this);
		break;
	case RIGHTCLICK:
		displayCourseInfo(actData.x,actData.y);
		int x, y;
		getGUI()->getWindow()->WaitMouseClick(x,y);
		break;
	//TODO: Add case for each action
	
	case EXIT:
		RequiredAction = new ActionDeleteCourse(this);//exit(1);
		break;
	}
	return RequiredAction;
}

//Executes the action, Releases its memory, and return true if done, false if cancelled
bool Registrar::ExecuteAction(Action*& pAct)
{
	bool done = pAct->Execute();
	delete pAct;	//free memory of that action object (either action is exec or cancelled)
	return done;
}

void Registrar::Run()
{
	while (true)
	{
		//update interface here as CMU Lib doesn't refresh itself
		//when window is minimized then restored
		UpdateInterface();

		Action* pAct = CreateRequiredAction();
		if (pAct)	//if user doesn't cancel
		{
			
			if (ExecuteAction(pAct))	//if action is not cancelled
				UpdateInterface();
		}
	}
}


void Registrar::UpdateInterface()
{
	pGUI->UpdateInterface();	//update interface items
	pSPlan->DrawMe(pGUI);		//make study plan draw itself
}

void Registrar::clearRules() {
	pRegRules->totalCredit = 0;
	pRegRules->ReqUnivCredits = 0;
	pRegRules->ReqTrackCredits = 0;
	pRegRules->ReqMajorCredits = 0;
	pRegRules->NumConcentration = 0;
	pRegRules->ReqConCredits.clear();
	pRegRules->UnivCompulsory.clear();
	pRegRules->UnivElective.clear();
	pRegRules->TrackCompulsory.clear();
	pRegRules->TrackElective.clear();
	pRegRules->MajorCompulsory.clear();
	pRegRules->MajorElective.clear();
	pRegRules->ConCompulsory.clear();
	pRegRules->ConElective.clear();
	pRegRules->SemMaxCredit = 0;
	pRegRules->SemMinCredit = 0;
}

void Registrar::clearStudyPlan() {
	pSPlan->getPlan().clear();
}

Registrar::~Registrar()
{
	delete pGUI;
	delete pSPlan;
	delete pRegRules;
}
