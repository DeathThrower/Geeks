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
	void clearStudyPlan();
	void clearRules();

	void Run();

	//helper functions:
	Course* getCourse(int x, int y) const;
	// function to get the course information
	CourseInfo getCourseInfo(Rules* myrules, Course_Code CC) const;

	// function to display the course info
	void displayCourseInfo( int x, int y);

	// convert string to SEMESTER
	SEMESTER str2sem(string str) const;

	//convert SEMESTER to string
	string sem2str(SEMESTER sem) const;

	//open a file selection window and return the path of the file
	string openfilename(string title,char* filter = "Text Documents (*.txt)\0*.txt\0", HWND owner = NULL) const;

	//open a save file window and return the path 
	string savefilename(char* filter = "Text Documents (*.txt)\0*.txt\0", HWND owner = NULL) const;

	~Registrar();
};

