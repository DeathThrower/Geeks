#pragma once
#include "GUI\GUI.h"
#include "Actions\Action.h"
#include "Rules.h"
#include "StudyPlan/StudyPlan.h"



//The maestro class for the application
class Registrar
{
	GUI *pGUI;	//pointer to GUI 
	Rules RegRules;	//Registration rules
	StudyPlan *pSPlan;

public:
	Registrar();
	GUI* getGUI() const;
	Action* CreateRequiredAction();
	Rules getRules() const;
	bool ExecuteAction(Action*&);
	void UpdateInterface();
	StudyPlan* getStudyPlay() const;

	void Run();

	//helper functions
	CourseInfo getCourseInfo(Rules myrules, Course_Code CC) const;
	SEMESTER str2sem(string str) const;
	string sem2str(SEMESTER sem) const;
	string openfilename(char* filter = "Text Documents (*.txt)\0*.txt\0", HWND owner = NULL) const;
	string savefilename(char* filter = "Text Documents (*.txt)\0*.txt\0", HWND owner = NULL) const;

	~Registrar();
};

