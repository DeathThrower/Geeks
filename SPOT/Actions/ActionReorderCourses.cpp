#include "ActionReorderCourses.h"
#include "..\Registrar.h"

ActionReorderCourses::ActionReorderCourses(Registrar* p) :Action(p)
{
}

bool ActionReorderCourses::Execute()
{
	window* pWind = pReg->getGUI()->getWindow();
	pWind->FlushMouseQueue();
	pWind->FlushKeyQueue();

	pWind->SetBuffering(true);
	bool bDragging = false;

	int x, y;
	pReg->getGUI()->PrintMsg("select course to be reordered");
	pWind->WaitMouseClick(x, y);
	Course* course = pReg->getStudyPlan()->getCourse(x, y);
	if (course==NULL) {
		return false;
	}
	pReg->getGUI()->PrintMsg("Select a course");

	int RectULX = course->getGfxInfo().x;
	int RectULY = course->getGfxInfo().y;
	int RectWidth = 75;
	int RectHight = 40;

	int iX = 0, iY = 0;

	int iXOld = 0;
	int iYOld = 0;

	char cKeyData;
	// Loop until there escape is pressed
	while (pWind->GetKeyPress(cKeyData) != ESCAPE)
	{
		pReg->getGUI()->PrintMsg("Now drag and drop ,,,, Press ""Esc"" if finished ");
		// Dragging voodoo
		if (bDragging == false) {
			if (pWind->GetButtonState(LEFT_BUTTON, iX, iY) == BUTTON_DOWN) {
				if (((iX > RectULX) && (iX < (RectULX + RectWidth))) && ((iY > RectULY) && (iY < (RectULY + RectHight)))) {
					bDragging = true;
					iXOld = iX; iYOld = iY;
				}
			}
		}
		else {
			if (pWind->GetButtonState(LEFT_BUTTON, iX, iY) == BUTTON_UP) {
				bDragging = false;
			}
			else {
				if (iX != iXOld) {
					RectULX = RectULX + (iX - iXOld);
					iXOld = iX;
				}
				if (iY != iYOld) {
					RectULY = RectULY + (iY - iYOld);
					iYOld = iY;
				}
			}

		}
		// Draw course
		course->setGfxInfo(graphicsInfo{ RectULX, RectULY });
		pReg->UpdateInterface();
	}
	int year = ((RectULX-20)/263)+1;
	int sem = (((RectULX - 20) % 263)/88)+1;
	Course* copyCourse(course);
	pReg->getStudyPlan()->DeleteCourse(RectULX, RectULY);
	pReg->getStudyPlan()->AddCourse(copyCourse, year, static_cast<SEMESTER>(sem));
	pWind->SetBuffering(false);
    return true;
}


ActionReorderCourses::~ActionReorderCourses()
{
}
