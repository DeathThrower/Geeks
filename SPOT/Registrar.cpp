#include "Registrar.h"
#include "Actions/ActionAddCourse.h"
#include "Actions/ActionLoadStudyPlan.h"
#include "Actions/ActionSaveStudyPlan.h"
#include "Actions/ActionLoadCourseOffering.h"
#include "Actions/ActionReplaceCourse.h"
#include "Actions/ActionDeleteCourse.h"
#include "Actions/ActionLoadRules.h"
//#include<iostream>


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


SEMESTER Registrar::str2sem(string str)  {
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

string Registrar::sem2str(SEMESTER sem)  {
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

void Registrar::displayCourseInfo( int x, int y)
{
	Course* course = getStudyPlan()->getCourse(x, y);
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
		RequiredAction = new ActionReplaceCourse(this);//exit(1);
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
