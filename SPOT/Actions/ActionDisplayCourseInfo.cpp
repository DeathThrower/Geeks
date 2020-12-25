#include "ActionDisplayCourseInfo.h"
#include "..\Registrar.h"
#include "../Courses/UnivCourse.h"


ActionDisplayCourseInfo::ActionDisplayCourseInfo(Registrar* p) :Action(p)
{
}

bool ActionDisplayCourseInfo::Execute() { return true; }
bool ActionDisplayCourseInfo::Execute(int cx, int cy) //overload 
{
	char temp;  //just char will be used only in wait key presses function
	Course* course = pReg->getStudyPlan()->getCourse(cx, cy);
	if (course == NULL) {
		pReg->getGUI()->PrintMsg("Error!!! there is no course here ... Press any key if finished");
		pReg->getGUI()->getWindow()->WaitKeyPress(temp);
		return false;
	}

	course->setSelected(true);  //making a frame around the course

	// Creating the course info string that will be displayed in the screen
	string courseInfo = "Title: "+course->getTitle()+" | Code: " + course->getCode() + " | credits: " + 
						to_string(course->getCredits()) + " | Type: " + course->getType() + " | PreReq: ";
	for (auto pre : course->getPreReq()) {
		courseInfo += pre + ",";
	}
	courseInfo += " | CoreReq: ";
	for (auto co : course->getCoReq()) {
		courseInfo += co + ",";
	}
	//printing the the course info 
	pReg->getGUI()->PrintMsg(courseInfo + " ... Press any key if finished");
	
	 
	pReg->getGUI()->getWindow()->WaitKeyPress(temp);  // wait for the user to finish reading the course info
	course->setSelected(false);  // clear the frame 
	return true;
}


ActionDisplayCourseInfo::~ActionDisplayCourseInfo()
{
}
