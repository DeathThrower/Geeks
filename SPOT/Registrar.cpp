#include "Registrar.h"
#include "Actions/ActionAddCourse.h"
#include "Actions/ActionLoadStudyPlan.h"

string Registrar::openfilename( char* filter , HWND owner) const {
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
	string fileNameStr;
	if (GetOpenFileName(&ofn)) {
		fileNameStr = fileName;
	}
	return fileNameStr;
}

string Registrar::savefilename( char* filter , HWND owner) const {
	OPENFILENAME ofn;
	char fileName[MAX_PATH] = "";
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

// function to get the course information
CourseInfo Registrar::getCourseInfo(Rules myrules, Course_Code CC) const{
	for (CourseInfo i : myrules.CourseCatalog) {
		if (i.Code == CC) {
			return i;
		}
	}
}

// convert string to SEMESTER
SEMESTER Registrar::str2sem(string semester) const {
	if (semester == "Fall" || semester == "fall") {
		return FALL;
	}
	else if (semester == "Spring" || semester == "spring") {
		return SPRING;
	}
	else if (semester == "Summer" || semester == "summer") {
		return SUMMER;
	}
}

Registrar::Registrar()
{
	pGUI = new GUI;	//create interface object
	pSPlan = new StudyPlan;	//create a study plan.
}

Rules Registrar::getRules() const {
	return RegRules;
}

//returns a pointer to GUI
GUI* Registrar::getGUI() const
{
	return pGUI;
}

//returns the study plan
StudyPlan* Registrar::getStudyPlay() const
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
		RequiredAction = new ActionLoadStudyPlan(this);  //error
		break;

	case LOAD:
		RequiredAction = new ActionLoadStudyPlan(this);
		break;
	//TODO: Add case for each action
	
	/*case EXIT:
		break;
		*/
	}
	return RequiredAction;
}

//Executes the action, Releases its memory, and return true if done, false if cancelled
bool Registrar::ExecuteAction(Action*& pAct)
{
	bool done = pAct->Execute();
	//delete pAct;	//free memory of that action object (either action is exec or cancelled)
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
				int x =4;
				UpdateInterface();
		}
		delete pAct;
		pAct = nullptr;
	}
}


void Registrar::UpdateInterface()
{
	pGUI->UpdateInterface();	//update interface items
	pSPlan->DrawMe(pGUI);		//make study plan draw itself
}

Registrar::~Registrar()
{
	delete pGUI;
}
