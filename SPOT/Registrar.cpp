#include "Registrar.h"
#include "Actions/ActionAddCourse.h"
#include "Actions/ActionLoadStudyPlan.h"
#include "Actions/ActionSaveStudyPlan.h"
#include "Actions/ActionLoadCourseOffering.h"
#include "Actions/ActionReplaceCourse.h"
#include "Actions/ActionDeleteCourse.h"
#include "Actions/ActionLoadRules.h"
#include "Actions/ActionImportCatalog.h"
#include "Actions/ActionDisplayCourseInfo.h"
#include "Actions/ActionAddNotes.h"
#include "Actions/ActionReorderCourses.h"
#include "Actions/ActionCheck.h"
#include "Actions/ActionSelectCourseStatus.h"
#include  <algorithm>
#include <iostream>



CourseInfo Registrar::getCourseInfo(Course_Code CC) const {
	transform(CC.begin(), CC.end(), CC.begin(), ::tolower);
	CC.erase(remove_if(CC.begin(), CC.end(), ::isspace), CC.end());
	Course_Code code;
	for (CourseInfo i : pRegRules->CourseCatalog) {
		code = i.Code;
		transform(code.begin(), code.end(), code.begin(), ::tolower);
		code.erase(remove_if(code.begin(), code.end(), ::isspace), code.end());
		if (code == CC) {
			return i;
		}
	}
	CourseInfo empty;
	empty.Code = "";
	return empty;
}

string Registrar::getCourseType(Course_Code CC) const {
	for (auto &code : pRegRules->UnivCompulsory) {
		if (CC == code) return "UNIV";
	}
	for (auto &code : pRegRules->UnivElective) {
		if (CC == code) return "UNIV";
	}
	for (auto &code : pRegRules->TrackCompulsory) {
		if (CC == code) return "TRACK";
	}
	for (auto &code : pRegRules->TrackElective) {
		if (CC == code) return "TRACK";
	}
	for (auto &code : pRegRules->MajorCompulsory) {
		if (CC == code) return "MAJOR";
	}
	for (auto &code : pRegRules->MajorElective) {
		if (CC == code) return "MAJOR";
	}
	for (auto &vecCode : pRegRules->ConCompulsory) {
		for (auto &code : vecCode) {
			if (CC == code) return "CON";
		}
	}
	for (auto &vecCode : pRegRules->ConElective) {
		for (auto &code : vecCode) {
			if (CC == code) return "CON";
		}
	}
	return "NOT";
}

SEMESTER Registrar::str2sem(string str) {
	transform(str.begin(), str.end(), str.begin(), ::tolower);
	if (str == "fall") {
		return FALL;
	}
	else if (str == "spring") {
		return SPRING;
	}
	else if (str == "summer") {
		return SUMMER;
	}
	return SEM_CNT;
}

string Registrar::sem2str(SEMESTER sem) {
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



Registrar::Registrar()
{
	pGUI = new GUI;	//create interface object
	pSPlan = new StudyPlan;	//create a study plan.
	pRegRules = new Rules;  // create a Rules struct
	ActionImportCatalog(this).Execute();
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
	string str;
	int index = 0;
	switch (actData.actType)
	{
	case DRAW_AREA:
		ActionDisplayCourseInfo(this).Execute(actData.x, actData.y);
		break;
	case ADD_CRS:
		RequiredAction = new ActionAddCourse(this);
		break;
	case DEL_CRS:
		RequiredAction = new ActionDeleteCourse(this);
		break;
	case SAVE:
		RequiredAction = new ActionSaveStudyPlan(this);
		break;
	case LOAD:
		RequiredAction = new ActionLoadStudyPlan(this);
		break;
	case REPLACE:
		RequiredAction = new ActionReplaceCourse(this);
		break;
	case RIGHTCLICK:
		ActionSelectCourseStatus(this).Execute(actData.x, actData.y);
		break;
	case REORDER:
		RequiredAction = new ActionReorderCourses(this);
		break;
	case NOTES:
		RequiredAction = new ActionAddNotes(this);
		break;
	case CHECK:
		ActionCheck(this).Execute();
		break;
	case SMAJOR:
		pGUI->PrintMsg("Enter your major");
		str = pGUI->GetSrting();
		transform(str.begin(), str.end(), str.begin(), ::toupper);
		str.erase(remove_if(str.begin(), str.end(), ::isspace), str.end());
		pSPlan->setMajor(str);
		if (!ActionLoadRules(this).Execute()) {
			pGUI->PrintMsg("Error undefined major");
			Sleep(3000);
		}
		break;
	case SD_MAJOR:
		pGUI->PrintMsg("Enter your double major");
		str = pGUI->GetSrting();
		transform(str.begin(), str.end(), str.begin(), ::toupper);
		str.erase(remove_if(str.begin(), str.end(), ::isspace), str.end());
		pSPlan->setD_Major(str);
		if (!pSPlan->loadDMajor(str, pRegRules)) {
			pGUI->PrintMsg(">>> Either the Major itself or the Major File doesn't exist");
			Sleep(3000);
		}
		else {
			pGUI->PrintMsg(">>> Major Requirement Loaded successfully.");
			Sleep(3000);
		}
		
			break;
		
	case SCON:
		pGUI->PrintMsg("Enter your concentration");
		str = pGUI->GetSrting();
		str.erase(remove_if(str.begin(), str.end(), ::isspace), str.end());
		if (stoi(str) <= pRegRules->NumConcentration && stoi(str) > 0) {
			pSPlan->setCon(str);
		}
		break;
	case SD_CON:
		if (pSPlan->getD_Con() != "") {
			index = stoi(pSPlan->getD_Con())-1;
			pRegRules->totalCredit -= (pRegRules->ReqConCredits[index]);
		}
		pGUI->PrintMsg("Enter your double concentration");
		str = pGUI->GetSrting();
		str.erase(remove_if(str.begin(), str.end(), ::isspace), str.end());
		if (stoi(str) <= pRegRules->NumConcentration && stoi(str) > 0) {
			index = stoi(str) - 1;
			pSPlan->setD_Con(str);
			pRegRules->totalCredit += (pRegRules->ReqConCredits[index]);
		}
		else {
			pGUI->PrintMsg("Error undefined concentration");
			Sleep(3000);
		}
		break;
	case SMINOR: //SMINOR 
		pGUI->PrintMsg("Enter your minor[All Caps]:");
		str = pGUI->GetSrting();
		transform(str.begin(), str.end(), str.begin(), ::toupper);
		str.erase(remove_if(str.begin(), str.end(), ::isspace), str.end());
		if (!pSPlan->loadMinor(str, pRegRules))
		{
			pGUI->PrintMsg(">>> Either the Minor itself or the Minor File doesn't exist");
			Sleep(3000);
		}
		else {
			pSPlan->setMinor(str);
			pGUI->PrintMsg(">>> Minor Requirement Loaded successfully.");
			Sleep(3000);
		}
		break;
	case SGPA:
		pSPlan->calculateGPA(this);
		break;
	case TOGGLEVIEW:
		pGUI->PrintMsg("Select View Filter: [1]All [2]Year [3]Semster [4]Major [5]University [6]Track");
		str = pGUI->GetSrting();
		transform(str.begin(), str.end(), str.begin(), ::toupper);
		str.erase(remove_if(str.begin(), str.end(), ::isspace), str.end());
		if (stoi(str) == 1) {
			pSPlan->viewFilter(true, 0, 0, false, false, false);
		}
		else if(stoi(str) == 2)
		{
			pGUI->PrintMsg("Select Year Number: 1-2-3-4-5 ");
			str = pGUI->GetSrting();
			transform(str.begin(), str.end(), str.begin(), ::toupper);
			str.erase(remove_if(str.begin(), str.end(), ::isspace), str.end());
			pSPlan->viewFilter(false, stoi(str) , 0, false, false, false);
			
		}else if (stoi(str) == 3)
		{
			pGUI->PrintMsg("Select Semester Number: a number from 1-2-3- .... -15 ");
			str = pGUI->GetSrting();
			transform(str.begin(), str.end(), str.begin(), ::toupper);
			str.erase(remove_if(str.begin(), str.end(), ::isspace), str.end());
			pSPlan->viewFilter(false, 0,stoi(str), false, false, false);
		}
		else if (stoi(str) == 4)
		{
			pSPlan->viewFilter(false, 0, 0, true, false, false);
		}
		else if (stoi(str) == 5)
		{
			pSPlan->viewFilter(false, 0, 0, false, true, false);
		}
		else if (stoi(str) == 6)
		{
			pSPlan->viewFilter(false, 0, 0, false, false, true);
		}
		break;
	case EXIT:
		exit(1);
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


Registrar::~Registrar()
{
	delete pGUI;
	delete pSPlan;
	delete pRegRules;
}