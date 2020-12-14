#include "ActionReorderCourses.h"
#include "..\Registrar.h"
#include <iostream>

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

	int year,sem;

	Course* course = NULL;
	int cX=0, cY=0;				// the coordinates of the course while draging it
	int cXold=0, cYold=0;		// the initial coordinates of the course

	int RectWidth = 75;
	int RectHight = 40;

	int iX = 0, iY = 0;

	int iXOld = 0;
	int iYOld = 0;
	pReg->getGUI()->PrintMsg("Now drag and drop ,,,, Press ""Esc"" if finished ");
	char cKeyData;
	// Loop until there escape is pressed
	while (pWind->GetKeyPress(cKeyData) != ESCAPE)
	{
		pReg->getGUI()->PrintMsg("Now drag and drop ,,,, Press ""Esc"" if finished ");
		// Dragging voodoo
		if (bDragging == false) {
			if (pWind->GetButtonState(LEFT_BUTTON, iX, iY) == BUTTON_DOWN) {
				// if the left button is pressed I will get an x and y of the click and get the corresponding
				//course if found
				course = pReg->getStudyPlan()->getCourse(iX, iY);
				if (course != NULL) {
					cXold = course->getGfxInfo().x;	//storing the initial values of cY and cX
					cYold = course->getGfxInfo().y;

					cX = course->getGfxInfo().x;	//setting the cX and cY with the x and y
					cY = course->getGfxInfo().y;	//of the course
					bDragging = true;
					iXOld = iX; iYOld = iY;			//setting the ixold and iyold with the x and y the new one
				}
			}
		}
		else {
			if (pWind->GetButtonState(LEFT_BUTTON, iX, iY) == BUTTON_UP) {
				// after leaving the left button, first check if it was holding a course or not
				// if so automatically set the correct x and y of the course (getting it from the year and sem)
				bDragging = false;
				if (cX !=0 && cY != 0) {
					//getting the year and sem from the current cX and cY
					year = ((iX - 15) / 263) + 1;
					sem = (((iX - 15) % 263) / 88);
					
					//updating the cX, cY and x and y of the course
					cY = 215 + (((iY-215)/45)) * 45;
					cX = (year - 1) * 263 + 20 + sem * 88;
					course->setGfxInfo(graphicsInfo{ cX, cY });
					
					//error checking if the user put a course on another course					 uncompleted 
					
					if (pReg->getStudyPlan()->getnCourse(iX, iY) > 1) {  // if there is more than 1 course has inside the current x and y that's mean that
																		 // there is another course other than our course has inside the current x and y
																		 // reset the x and y of the course to the initial x and y and sleep for 5 seconds
						course->setGfxInfo(graphicsInfo{ cXold, cYold });
						pReg->getGUI()->PrintMsg("Error!!! you can't put course over another course, wait a second and continue drag and drop ");
						Sleep(5000);
					}
					else {
						//moving the course inside the study plan by adding and deleting
						Course* copyCourse(course);
						pReg->getStudyPlan()->DeleteCourse(cX, cY);
						pReg->getStudyPlan()->AddCourse(copyCourse, year, static_cast<SEMESTER>(sem));
					}

					//update the interface
					pReg->UpdateInterface();
				}
				cX = 0;
				cY = 0;
			}
			else {
				//moving the box of the course according to the x and y of the mouse
				if (iX != iXOld) {
					cX = cX + (iX - iXOld);
					iXOld = iX;
				}
				if (iY != iYOld) {
					cY = cY + (iY - iYOld);
					iYOld = iY;
				}
				course->setGfxInfo(graphicsInfo{ cX,cY });
				pReg->UpdateInterface();
			}
		}
	}

	pWind->SetBuffering(false);
    return true;
}


ActionReorderCourses::~ActionReorderCourses()
{
}
