#include "GUI.h"
#include "../Courses/Course.h"
#include "../StudyPlan/AcademicYear.h"
#include <sstream>

GUI::GUI()
{ 
	pWind = new window(1360, 768,-10,0);
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
	MenuItemImages[ITM_ADD] = str+"SPOT/GUI/Images/Menu/add-file.jpg";
	MenuItemImages[ITM_ex1] = str+"SPOT/GUI/Images/Menu/test-icon-28.jpg";
	MenuItemImages[ITM_ex2] = str + "SPOT/GUI/Images/Menu/test-icon-28.jpg";
	MenuItemImages[ITM_ex3] = str + "SPOT/GUI/Images/Menu/test-icon-28.jpg";
	MenuItemImages[ITM_ex4] = str + "SPOT/GUI/Images/Menu/test-icon-28.jpg";
	MenuItemImages[ITM_ex5] = str + "SPOT/GUI/Images/Menu/test-icon-28.jpg";
	MenuItemImages[ITM_ex6] = str + "SPOT/GUI/Images/Menu/test-icon-28.jpg";
	MenuItemImages[ITM_EXIT] = str + "SPOT/GUI/Images/Menu/Exit.jpg";


	//TODO: Prepare image for each menu item and add it to the list

	//Draw menu items one image at a time
	for (int i = 0; i<ITM_CNT-1; i++)
		pWind->DrawImage(MenuItemImages[i], (i*65)+5, 5, MenuItemWidth, 50);

	pWind->DrawImage(MenuItemImages[ITM_EXIT], 1290 , 5, MenuItemWidth, 50);

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

	pWind->SetPen(RED, 5);
	pWind->DrawRectangle(15, 80, 1330, 700, FRAME);
	
	pWind->SetPen(BLUE, 3);
	for (int i = 1; i <= 4; i++)
	{
		pWind->DrawLine(15 + (i * 263), 100, 15 + (i * 263), 680);
	}
	pWind->DrawLine(40, 130, 1310, 130);

	pWind->SetPen(LIGHTBLUE, 2);
	for (int i = 1; i <= 3*5; i++)
	{
		if (i % 3 == 0)
			i++;

		pWind->DrawLine(15 + i*87.67, 140, 15 + i*87.67, 650);

	}

	for (int i = 0; i < 5; i++)
	{
		pWind->DrawLine(30+(i*263), 165, 260+(i*263), 165);
	}

	pWind->SetFont(CRS_HEIGHT * 0.8, BOLD, BY_NAME, "Gramound");
	pWind->SetPen(BROWN);
	pWind->DrawString(100, 95, "Year 1");
	pWind->DrawString(100 + 263, 95, "Year 2");
	pWind->DrawString(100 + 2*263, 95, "Year 3");
	pWind->DrawString(100 + 3*263, 95, "Year 4");
	pWind->DrawString(100 + 4*263, 95, "Year 5");

	pWind->SetFont(CRS_HEIGHT * 0.5, BOLD, BY_NAME, "Gramound");
	pWind->SetPen(DARKGREEN);
	for (int i = 0; i < 5; i++)
	{
		pWind->DrawString(55 + i * 263, 140, "Fall");
		pWind->DrawString(120 + i * 263, 140, "Spring");
		pWind->DrawString(200 + i * 263, 140, "Summer");
	}
	
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
			if (y >= MenuBarHeight && y < WindHeight - StatusBarHeight){
				return ActionData{RIGHTCLICK,x,y};
			}
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
