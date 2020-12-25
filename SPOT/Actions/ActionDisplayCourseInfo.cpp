#include "ActionDisplayCourseInfo.h"
#include "..\Registrar.h"
#include "../Courses/UnivCourse.h"


ActionDisplayCourseInfo::ActionDisplayCourseInfo(Registrar* p) :Action(p)
{
}

bool ActionDisplayCourseInfo::Execute() { return true; }
bool ActionDisplayCourseInfo::Execute(int cx, int cy) //overload 
{
	
	Course* course = pReg->getStudyPlan()->getCourse(cx, cy);
	if (course == NULL) return false;

	// Creating the course info string that will be displayed in the screen
	string courseInfo = "Course Title: "+course->getTitle()+" | Course Code: " + course->getCode() + " | No. credits: " + to_string(course->getCredits()) + " | CoreReq: ";
	for (auto pre : course->getPreReq()) {
		courseInfo += pre + ",";
	}
	courseInfo += " | CoreReq: ";
	for (auto co : course->getCoReq()) {
		courseInfo += co + ",";
	}
	//printing the the course info 
	pReg->getGUI()->PrintMsg(courseInfo);
	
	return true;
}


ActionDisplayCourseInfo::~ActionDisplayCourseInfo()
{
}
