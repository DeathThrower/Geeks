#include "ActionSelectCourseStatus.h"
#include "..\Registrar.h"

ActionSelectCourseStatus::ActionSelectCourseStatus(Registrar* p) :Action(p)
{
}
ActionSelectCourseStatus::~ActionSelectCourseStatus()
{
}
bool ActionSelectCourseStatus::Execute() { return true; }
bool ActionSelectCourseStatus::Execute(int cx, int cy) {   //overload 
	char temp;  //just char will be used only in wait key presses function
	Course* course = pReg->getStudyPlan()->getCourse(cx, cy);  // getting the course by the click coordinates
	if (course == NULL) { // error checking if the user does nnot pressed on a course
		pReg->getGUI()->PrintMsg("Error!!! there is no course here to set its status ... Press any key if finished");
		pReg->getGUI()->getWindow()->WaitKeyPress(temp);
		return false;
	}
	CStatus OldStatus = course->getStatus(); // getting the old status

	course->setSelected(true);  //making a frame around the course
	pReg->UpdateInterface();    //update the GUI

	pReg->getGUI()->PrintMsg("Select the course status (0 for Done, 1 for In Progress, 2 for Pending) :"); //display a message to the user
	CStatus NewStatus = static_cast<CStatus>(stoi(pReg->getGUI()->GetSrting()));  // getting the newstatus
	if (NewStatus<0 || NewStatus>2) { //error checking if the user entered out of range index
		pReg->getGUI()->PrintMsg("Error!!! undefined chose ... Press any key if finished reading this error message");
		pReg->getGUI()->getWindow()->WaitKeyPress(temp);
		return false;
	}
	course->setSatus(NewStatus);

	pReg->getStudyPlan()->changeCStatusCrd(OldStatus, NewStatus,course->getCredits());

	course->setSelected(false);  //making a frame around the course
	pReg->UpdateInterface();    //update the GUI
	return true;
}