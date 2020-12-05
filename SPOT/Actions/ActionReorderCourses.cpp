#include "ActionReorderCourses.h"
#include "..\Registrar.h"
#include  <iostream>

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
		pReg->getGUI()->PrintMsg("now drag and drop");
		// Dragging voodoo
		if (bDragging == false) {
			cout << "1" << endl;
			if (pWind->GetButtonState(LEFT_BUTTON, iX, iY) == BUTTON_DOWN) {
				cout << "2" << endl;
				if (((iX > RectULX) && (iX < (RectULX + RectWidth))) && ((iY > RectULY) && (iY < (RectULY + RectHight)))) {
					cout << "3"<<endl;
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
		std::cout << iXOld << iYOld;
		// Draw course
		course->setGfxInfo(graphicsInfo{ RectULX, RectULY });
		pReg->UpdateInterface();
	}

	pWind->SetBuffering(false);
    return true;
}


ActionReorderCourses::~ActionReorderCourses()
{
}
