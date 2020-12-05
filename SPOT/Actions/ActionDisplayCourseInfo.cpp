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
	string courseInfo = "Course Title: "+course->getTitle()+" | Course Name: " + course->getCode() + " | No. of credits: " + to_string(course->getCredits());
	pReg->getGUI()->PrintMsg(courseInfo);
	

	return true;
}


ActionDisplayCourseInfo::~ActionDisplayCourseInfo()
{
}
