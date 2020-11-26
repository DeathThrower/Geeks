#pragma once
#include "GUI\GUI.h"
#include "Actions\Action.h"
#include "Rules.h"
#include "StudyPlan/StudyPlan.h"



//The maestro class for the application
class Registrar
{
	GUI *pGUI;	//pointer to GUI 
	Rules *pRegRules;	//Registration rules
	StudyPlan *pSPlan;

public:
	Registrar();
	GUI* getGUI() const;
	Action* CreateRequiredAction();
	Rules* getRules() const;
	bool ExecuteAction(Action*&);
	void UpdateInterface();
	StudyPlan* getStudyPlan() const;

	void Run();

	//helper functions:

	// function to get the course information
	CourseInfo getCourseInfo(Rules* myrules, Course_Code CC) const;

	// convert string to SEMESTER
	SEMESTER str2sem(string str) const;

	//convert SEMESTER to string
	string sem2str(SEMESTER sem) const;

	//open a file selection window and return the path of the file
	string openfilename(char* filter = "Text Documents (*.txt)\0*.txt\0", HWND owner = NULL) const;

	//open a save file window and return the path 
	string savefilename(char* filter = "Text Documents (*.txt)\0*.txt\0", HWND owner = NULL) const;

	~Registrar();
};

