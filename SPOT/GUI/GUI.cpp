#include "GUI.h"
#include "../Courses/Course.h"
#include "../StudyPlan/AcademicYear.h"
#include <sstream>

GUI::GUI()
{ 
	pWind = new window(1920, 1080,-10,0);
	pWind->ChangeTitle(WindTitle);
	ClearDrawingArea();
	ClearStatusBar();
	CreateMenu();
}

window* GUI::getWindow() const{
	return pWind;
}

//Clears the status bar
void GUI::ClearDrawingArea() const
{
	pWind->SetBrush(BkGrndColor);
	pWind->SetPen(BkGrndColor);
	pWind->DrawRectangle(0, MenuBarHeight, WindWidth, WindHeight -StatusBarHeight);

}

void GUI::ClearStatusBar() const
{
	pWind->SetBrush(StatusBarColor);
	pWind->SetPen(StatusBarColor);
	pWind->DrawRectangle(0, WindHeight - StatusBarHeight, WindWidth, WindHeight);
}

void GUI::CreateMenu() const
{
	pWind->SetBrush(StatusBarColor);
	pWind->SetPen(StatusBarColor);
	pWind->DrawRectangle(0, 0, WindWidth, MenuBarHeight);

	//You can draw the menu icons any way you want.

	//First prepare List of images paths for menu item
	char result[MAX_PATH];
	string str = string(result, GetModuleFileName(NULL, result, MAX_PATH));
	str = str.erase(str.length() - 18, 18);
	int ind = str.find("\\");
	while (ind != string::npos) {
		str.replace(ind, 1, "/");
		ind = str.find("\\");
	}
	string MenuItemImages[ITM_CNT];
	MenuItemImages[ITM_ADD] = str+"SPOT/GUI/Images/Menu/add.jpg";
	MenuItemImages[ITM_EXIT] = str+"SPOT/GUI/Images/Menu/Exit.jpg";

	//TODO: Prepare image for each menu item and add it to the list

	//Draw menu items one image at a time
	for (int i = 0; i<ITM_CNT; i++)
		pWind->DrawImage(MenuItemImages[i], i*MenuItemWidth, 0, MenuItemWidth, MenuBarHeight);
}

////////////////////////    Output functions    ///////////////////

//Prints a message on the status bar
void GUI::PrintMsg(string msg) const
{
	ClearStatusBar();	//Clear Status bar to print message on it
						// Set the Message offset from the Status Bar
	int MsgX = 25;
	int MsgY = StatusBarHeight - 10;

	// Print the Message
	pWind->SetFont(20, BOLD , BY_NAME, "Arial");
	pWind->SetPen(MsgColor);
	pWind->DrawString(MsgX, WindHeight - MsgY, msg);
}

//////////////////////////////////////////////////////////////////////////
void GUI::UpdateInterface() const
{
	
	pWind->SetBuffering(true);
	//Redraw everything
	CreateMenu();
	ClearStatusBar();
	ClearDrawingArea();
	pWind->UpdateBuffer();
	pWind->SetBuffering(false);

}

////////////////////////    Drawing functions    ///////////////////
void GUI::DrawCourse(const Course* pCrs)
{
	if (pCrs->isSelected())
		pWind->SetPen(HiColor, 2);
	else
	pWind->SetPen(DrawColor, 2);
	pWind->SetBrush(FillColor);
	graphicsInfo gInfo = pCrs->getGfxInfo();
	pWind->DrawRectangle(gInfo.x, gInfo.y, gInfo.x + CRS_WIDTH, gInfo.y + CRS_HEIGHT);
	pWind->DrawLine(gInfo.x, gInfo.y + CRS_HEIGHT / 2, gInfo.x + CRS_WIDTH, gInfo.y + CRS_HEIGHT / 2);
	
	//Write the course code and credit hours.
	int Code_x = gInfo.x + CRS_WIDTH * 0.15;
	int Code_y = gInfo.y + CRS_HEIGHT * 0.05;
	pWind->SetFont(CRS_HEIGHT * 0.4, BOLD , BY_NAME, "Gramound");
	pWind->SetPen(MsgColor);

	ostringstream crd;
	crd<< "crd:" << pCrs->getCredits();
	pWind->DrawString(Code_x, Code_y, pCrs->getCode());
	pWind->DrawString(Code_x, Code_y + CRS_HEIGHT/2, crd.str());
}

void GUI::DrawAcademicYear(const AcademicYear* pY) 
{
	graphicsInfo gInfo = pY->getGfxInfo();

	///TODO: compelete this function to:
	//		1- Draw a rectangle for the academic year 
	//		2- Draw a sub-rectangle for each semester
	//Then each course should be drawn inside rect of its year/sem

	// Drawing the borders of the acadimic plan:
	pWind->SetPen(BLACK, 3);
	pWind->DrawLine(265, 55, 265, 600);
	pWind->DrawLine(2* 265, 55, 2* 265, 600);
	pWind->DrawLine(3* 265, 55, 3* 265, 600);
	pWind->DrawLine(4* 265, 55, 4* 265, 600);
	pWind->DrawLine(5 * 265, 55, 5 * 265, 600);
	pWind->DrawLine(0, 600, 1920, 600);
	pWind->DrawLine(0, 100, 1920, 100);
	pWind->DrawLine(0, 55, 1920, 55);

	pWind->SetPen(BLUE, 2);
	pWind->DrawLine(0, 150, 1920, 150);
	pWind->DrawLine(88, 100, 88, 600);
	pWind->DrawLine(2* 88, 100, 2* 88, 600);
	pWind->DrawLine(4* 88, 100, 4* 88, 600);
	pWind->DrawLine(5* 88, 100, 5* 88, 600);
	pWind->DrawLine(7 * 88, 100, 7 * 88, 600);
	pWind->DrawLine(8 * 88, 100, 8 * 88, 600);
	pWind->DrawLine(10 * 88, 100, 10 * 88, 600);
	pWind->DrawLine(11 * 88, 100, 11 * 88, 600);
	pWind->DrawLine(13 * 88, 100, 13 * 88, 600);
	pWind->DrawLine(14 * 88, 100, 14 * 88, 600);
	pWind->DrawLine(16 * 87, 100, 16 * 87, 600);
	pWind->DrawLine(17 * 87, 100, 17 * 87, 600);

	
	// Headlines printing:

	pWind->DrawString(100, 75, " YEAR 1 ");
	pWind->DrawString(100 + (256), 75, " YEAR 2 ");
	pWind->DrawString(100 + (2 * 256), 75, " YEAR 3 ");
	pWind->DrawString(100 + (3 * 256), 75, " YEAR 4 ");
	pWind->DrawString(100 + (4 * 256), 75, " YEAR 5 ");
	pWind->DrawString(100 + (5 * 256), 75, " YEAR 6 ");


	pWind->DrawString(30, 120, " FALL ");
	pWind->DrawString(30+88, 120, " SPRING ");
	pWind->DrawString(30+(2*88), 120, " SUMMER ");
	pWind->DrawString(30 + (3 * 88), 120, " FALL ");
	pWind->DrawString(30 + (4 * 88), 120, " SPRING ");
	pWind->DrawString(30 + (5 * 88), 120, " SUMMER ");
	pWind->DrawString(30 + (6 * 88), 120, " FALL ");
	pWind->DrawString(30 + (7 * 88), 120, " SPRING ");
	pWind->DrawString(30 + (8 * 88), 120, " SUMMER ");
	pWind->DrawString(30 + (9 * 88), 120, " FALL ");
	pWind->DrawString(30 + (10 * 88), 120, " SPRING ");
	pWind->DrawString(30 + (11 * 88), 120, " SUMMER ");
	pWind->DrawString(30 + (12 * 88), 120, " FALL ");
	pWind->DrawString(30 + (13 * 88), 120, " SPRING ");
	pWind->DrawString(30 + (14 * 88), 120, " SUMMER ");

	
}


////////////////////////    Input functions    ///////////////////
//This function reads the position where the user clicks to determine the desired action
//If action is done by mouse, actData will be the filled by mouse position
ActionData GUI::GetUserAction(string msg) const
{
	keytype ktInput;
	clicktype ctInput;
	char cKeyData;

	
	// Flush out the input queues before beginning
	pWind->FlushMouseQueue();
	pWind->FlushKeyQueue();
	
	PrintMsg(msg);

	while (true)
	{
		int x, y;
		ctInput = pWind->GetMouseClick(x, y);	//Get the coordinates of the user click
		ktInput = pWind->GetKeyPress(cKeyData);

		if (ktInput == ESCAPE)	//if ESC is pressed,return CANCEL action
		{
			return ActionData{ CANCEL };
		}

		
		if (ctInput == LEFT_CLICK)	//mouse left click
		{
			//[1] If user clicks on the Menu bar
			if (y >= 0 && y < MenuBarHeight)
			{
				//Check whick Menu item was clicked
				//==> This assumes that menu items are lined up horizontally <==
				int ClickedItemOrder = (x / MenuItemWidth);
				//Divide x coord of the point clicked by the menu item width (int division)
				//if division result is 0 ==> first item is clicked, if 1 ==> 2nd item and so on

				switch (ClickedItemOrder)
				{
				case ITM_ADD: return ActionData{ ADD_CRS };	//Add course
				case ITM_EXIT: return ActionData{ EXIT };		//Exit

				default: return ActionData{ MENU_BAR };	//A click on empty place in menu bar
				}
			}

			//[2] User clicks on the drawing area
			if (y >= MenuBarHeight && y < WindHeight - StatusBarHeight)
			{
				return ActionData{ DRAW_AREA,x,y };	//user want clicks inside drawing area
			}

			//[3] User clicks on the status bar
			return ActionData{ STATUS_BAR };
		}
		else if(ctInput == RIGHT_CLICK){
			// put here the function that display course info
			return ActionData{RIGHTCLICK,x,y};
		}
	}//end while

}

string GUI::GetSrting() const
{
	//Reads a complete string from the user until the user presses "ENTER".
	//If the user presses "ESCAPE". This function should return an empty string.
	//"BACKSPACE" is also supported
	//User should see what he is typing at the status bar

	

	string userInput;
	char Key;
	while (1)
	{
		pWind->WaitKeyPress(Key);

		switch (Key)
		{
		case 27: //ESCAPE key is pressed
			PrintMsg("");
			return ""; //returns nothing as user has cancelled the input

		case 13:		//ENTER key is pressed
			return userInput;

		case 8:		//BackSpace is pressed
			if (userInput.size() > 0)
				userInput.resize(userInput.size() - 1);
			break;

		default:
			userInput += Key;
		};

		PrintMsg(userInput);
	}

}




GUI::~GUI()
{
	delete pWind;
}
