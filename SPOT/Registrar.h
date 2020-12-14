#pragma once
#include "GUI\GUI.h"
#include "Actions\Action.h"
#include "Rules.h"
#include "StudyPlan/StudyPlan.h"


class StudyPlan;
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
	void clearRules();

	void Run();

	//helper functions:

	
	// function to get the course information
	CourseInfo getCourseInfo(Course_Code CC) const;

	//return the type of the course (UNIV, Track, ......)
	string getCourseType(Course_Code CC) const;

	// function to display the course info
	void displayCourseInfo( int x, int y);

	// convert string to SEMESTER
	static SEMESTER str2sem(string str) ;

	//convert SEMESTER to string
	static string sem2str(SEMESTER sem) ;

	//convert string to Major
	//static Major  str2maj(string str);

	~Registrar();
};

