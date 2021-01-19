#include "GUI.h"
#include "../Courses/Course.h"
#include "../StudyPlan/AcademicYear.h"
#include <sstream>
#include <iostream>

GUI::GUI()
{ 
	pWind = new window(1920, 745,-10,0);
	pWind->ChangeTitle(WindTitle);
	ClearDrawingArea();
	ClearStatusBar();
	CreateMenu();
}

window* GUI::getWindow() const{
	return pWind;
}

Course* GUI::Drag_Drop(Course* course)
{

    // Flush out the input queues before beginning
    pWind->FlushMouseQueue();
    pWind->FlushKeyQueue();

    pWind->SetBuffering(true);
    bool bDragging = false;

	int RectULX = course->getGfxInfo().x;
	int RectULY = course->getGfxInfo().y;
	int RectWidth = 75;
	int RectHight = 40;

    int iX = 0 , iY = 0;
	
    int iXOld = 0;
    int iYOld = 0;

    char cKeyData;
	// Loop until there escape is pressed
	while (pWind->GetKeyPress(cKeyData) != ESCAPE)
	{
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
		std::cout << iXOld << iYOld;
		// Draw course
		course->setGfxInfo(graphicsInfo{iXOld, iYOld});
		DrawCourse(course);

        // Update the screen buffer
        pWind->UpdateBuffer();
 
    }
    
	pWind->SetBuffering(false);



	return course;
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
	color BarColor = color(54, 74, 94);
	//pWind->SetBrush(StatusBarColor);
	//pWind->SetPen(StatusBarColor);
	pWind->SetBrush(BarColor);
	pWind->SetPen(BarColor);
	pWind->DrawRectangle(0, WindHeight - StatusBarHeight, WindWidth, WindHeight);
}

void GUI::CreateMenu() const
{
	color BarColor = color(54, 74, 94);
	//pWind->SetBrush(StatusBarColor);
	//pWind->SetPen(StatusBarColor);
	pWind->SetBrush(BarColor);
	pWind->SetPen(BarColor);
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
	MenuItemImages[ITM_ADD] = str + "SPOT/GUI/Images/Menu/add-file.jpg";
	MenuItemImages[DEL_CRS] = str + "SPOT/GUI/Images/Menu/delete.jpg";
	MenuItemImages[SAVE] = str + "SPOT/GUI/Images/Menu/save.jpg";
	MenuItemImages[LOAD] = str + "SPOT/GUI/Images/Menu/load.jpg";
	MenuItemImages[REPLACE] = str + "SPOT/GUI/Images/Menu/replace.jpg";
	MenuItemImages[REORDER] = str + "SPOT/GUI/Images/Menu/reorder.jpg";
	MenuItemImages[NOTES] = str + "SPOT/GUI/Images/Menu/notes.jpg";
	MenuItemImages[CHECK] = str + "SPOT/GUI/Images/Menu/check.jpg";
	MenuItemImages[TOGGLEVIEW] = str + "SPOT/GUI/Images/Menu/viewFilter.jpg";
	MenuItemImages[ITM_EXIT] = str + "SPOT/GUI/Images/Menu/exit.jpg";


	//TODO: Prepare image for each menu item and add it to the list
	
	//Draw menu items one image at a time
	for (int i = 0; i<ITM_CNT-1; i++)
		pWind->DrawImage(MenuItemImages[i], (i*65)+5, 5, MenuItemWidth, 50);

	pWind->DrawImage(MenuItemImages[ITM_EXIT], 1485 , 5, MenuItemWidth, 50);

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
	if (pCrs->getVisible())
	{
		string crsType = pCrs->getType();
		string issType = pCrs->getIssue(); 
		int roundWidth = 0; int roundHeight = 0;
		color fontColor = WHITE;
		color borderColor = color(40, 40, 40);
		color fillingColor = color(54, 74, 94);
		if (crsType == "UNIV")
		{
			// fillingColor =RGB(29, 161, 242)
			fillingColor.ucRed = 29;
			fillingColor.ucGreen = 161;
			fillingColor.ucBlue = 242;

		}
		else if (crsType == "TRACK") {
			// fillingColor =RGB(119, 123, 126) 
			fillingColor.ucRed = 119;
			fillingColor.ucGreen = 123;
			fillingColor.ucBlue = 126;
		}
		else if (crsType == "MAJOR") {
			// fillingColor =RGB(28, 32, 73) 17, 72, 128
			fillingColor.ucRed = 17;
			fillingColor.ucGreen = 72;
			fillingColor.ucBlue = 128;
		}
		if (issType == "Critical")
		{
			// fillingColor =RGB(28, 32, 73) 17, 72, 128
			fillingColor.ucRed = 255;
			fillingColor.ucGreen = 50;
			fillingColor.ucBlue = 50;
		}
		else if (issType == "Moderate")
		{
			// fillingColor =RGB(28, 32, 73) 17, 72, 128
			fillingColor.ucRed = 255;
			fillingColor.ucGreen = 255;
			fillingColor.ucBlue = 20;
		}
		//
		if (pCrs->isSelected()) {
			pWind->SetPen(HiColor, 2);
		}
		else {
			pWind->SetPen(DrawColor, 2);
		}
		pWind->SetPen(borderColor, 2);
		//pWind->SetBrush(FillColor); 
		pWind->SetBrush(fillingColor);
		graphicsInfo gInfo = pCrs->getGfxInfo();
		pWind->DrawRectangle(gInfo.x, gInfo.y, gInfo.x + CRS_WIDTH, gInfo.y + CRS_HEIGHT, FILLED, roundWidth, roundHeight);
		pWind->DrawLine(gInfo.x, gInfo.y + CRS_HEIGHT / 2, gInfo.x + CRS_WIDTH - 1, gInfo.y + CRS_HEIGHT / 2);

		//Write the course code and credit hours.
		int Code_x = gInfo.x + CRS_WIDTH * 0.02;
		int Code_y = gInfo.y + CRS_HEIGHT * 0.05;
		pWind->SetFont(CRS_HEIGHT * 0.4, BOLD, BY_NAME, "Gramound");
		//pWind->SetPen(DARKBLUE);
		pWind->SetPen(fontColor);
		ostringstream crd;
		crd << "crd:" << pCrs->getCredits();
		pWind->DrawString(Code_x, Code_y, pCrs->getCode());
		pWind->DrawString(Code_x, Code_y + CRS_HEIGHT / 2, crd.str());
	}
}

void GUI::DrawAcademicYear(const AcademicYear* pY) 
{
	graphicsInfo gInfo = pY->getGfxInfo();
	color masterColor = color(54, 74, 94);
	///TODO: compelete this function to:
	//		1- Draw a rectangle for the academic year 
	//		2- Draw a sub-rectangle for each semester
	//Then each course should be drawn inside rect of its year/sem

	//pWind->SetPen(RED, 5);
	pWind->SetPen(masterColor, 5);
	pWind->DrawRectangle(15, 120, 1330, 685, FRAME);
	
	//pWind->SetPen(RED, 5);
	pWind->SetPen(masterColor, 3);
	pWind->DrawRectangle(1340, 120, 1525, 160, FRAME);
	pWind->SetFont(CRS_HEIGHT * 0.55, ITALICIZED, BY_NAME, "Arial");
	pWind->SetPen(DARKBLUE, 3);
	pWind->DrawString(1350 , 130, "Student Information");

	pWind->SetPen(DARKSLATEBLUE, 2);
	pWind->DrawRectangle(1385, 190, 1500, 215, FRAME);
	pWind->SetPen(DARKCYAN, 3);
	pWind->SetFont(CRS_HEIGHT * 0.5, ITALICIZED, BY_NAME, "Arial");
	pWind->DrawString(1335, 170, "Student Level:");

	pWind->SetPen(DARKSLATEBLUE, 2);
	pWind->DrawRectangle(1385, 225, 1500, 250, FRAME);
	pWind->SetPen(DARKCYAN, 3);
	pWind->SetFont(CRS_HEIGHT * 0.5, ITALICIZED, BY_NAME, "Arial");
	pWind->DrawString(1335, 230, "GPA:");

	pWind->SetPen(DARKSLATEBLUE, 2);
	pWind->DrawRectangle(1385, 260, 1500, 285, FRAME);
	pWind->SetPen(DARKCYAN, 3);
	pWind->SetFont(CRS_HEIGHT * 0.5, ITALICIZED, BY_NAME, "Arial");
	pWind->DrawString(1335, 260, "Major:");

	pWind->SetPen(DARKSLATEBLUE, 2);
	pWind->DrawRectangle(1385, 310, 1500, 335, FRAME);
	pWind->SetPen(DARKCYAN, 3);
	pWind->SetFont(CRS_HEIGHT * 0.5, ITALICIZED, BY_NAME, "Arial");
	pWind->DrawString(1335, 290, "Double Major:");

	pWind->SetPen(DARKSLATEBLUE, 2);
	pWind->DrawRectangle(1385, 365, 1500, 390, FRAME);
	pWind->SetPen(DARKCYAN, 3);
	pWind->SetFont(CRS_HEIGHT * 0.5, ITALICIZED, BY_NAME, "Arial");
	pWind->DrawString(1335, 345, "Concentration:");

	pWind->SetPen(DARKSLATEBLUE, 2);
	pWind->DrawRectangle(1385, 410, 1500, 435, FRAME);
	pWind->SetPen(DARKCYAN, 3);
	pWind->SetFont(CRS_HEIGHT * 0.5, ITALICIZED, BY_NAME, "Arial");
	pWind->DrawString(1335, 390, "Double Concentration:");

	pWind->SetPen(DARKSLATEBLUE, 2);
	pWind->DrawRectangle(1385, 445, 1500, 470, FRAME);
	pWind->SetPen(DARKCYAN, 3);
	pWind->SetFont(CRS_HEIGHT * 0.5, ITALICIZED, BY_NAME, "Arial");
	pWind->DrawString(1335, 450, "Minor:");



	pWind->SetPen(DARKBLUE, 3);
	for (int i = 1; i <= 4; i++)
	{
		pWind->DrawLine(15 + (i * 263), 140, 15 + (i * 263), 670);
	}
	pWind->DrawLine(40, 170, 1310, 170);

	pWind->SetPen(BLUE, 2);
	for (int i = 1; i <= 3*5 - 1; i++)
	{
		if (i % 3 == 0)
			i++;

		pWind->DrawLine(15 + i*87.67, 180, 15 + i*87.67, 650);

	}

	for (int i = 0; i < 5; i++)
	{
		pWind->DrawLine(30+(i*263), 205, 260+(i*263), 205);
	}

	pWind->SetFont(CRS_HEIGHT * 0.8, BOLD, BY_NAME, "Gramound");
	//pWind->SetPen(BROWN);
	pWind->SetPen(masterColor);
	pWind->DrawString(100, 135, "Year 1");
	pWind->DrawString(100 + 263, 135, "Year 2");
	pWind->DrawString(100 + 2*263, 135, "Year 3");
	pWind->DrawString(100 + 3*263, 135, "Year 4");
	pWind->DrawString(100 + 4*263, 135, "Year 5");

	pWind->SetFont(CRS_HEIGHT * 0.5, ITALICIZED, BY_NAME, "Gramound");
	pWind->SetPen(DARKGREEN);
	for (int i = 0; i < 5; i++)
	{
		pWind->DrawString(55 + i * 263, 180, "Fall");
		pWind->DrawString(120 + i * 263, 180, "Spring");
		pWind->DrawString(200 + i * 263, 180, "Summer");
	}



	pWind->SetFont(CRS_HEIGHT * 0.38, ITALICIZED, BY_NAME, "ARIAL");
	pWind->SetPen(WHITE);
	pWind->DrawString(20 , 57, "Add ");
	pWind->DrawString(75, 57, "Delete ");
	pWind->DrawString(150, 57, "Save");
	pWind->DrawString(210, 57, "Load");
	pWind->DrawString(270, 57, "Replace");
	pWind->DrawString(335, 57, "Reorder");
	pWind->DrawString(390, 57, "Add Notes");
	pWind->DrawString(465, 57, "Check");
	pWind->DrawString(465 + 57, 57, "View Filter");
	pWind->DrawString(1500, 57, "Exit");

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
				/*
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
				}*/

				if (5 <= x && x <= 55) {
					return ActionData{ ADD_CRS };
				}
				else if (70 <= x && x <= 120){
					return ActionData{ DEL_CRS };
				}
				else if (135 <= x && x <= 185) {
					return ActionData{ SAVE };
				}
				else if (200 <= x && x <= 250) {
					return ActionData{ LOAD };
				}
				else if (265 <= x && x <= 315) {
					return ActionData{ REPLACE };
				}
				else if (330 <= x && x <= 380) {
					return ActionData{ REORDER };
				}
				else if (395 <= x && x <= 445) {
					return ActionData{ NOTES };
				}
				else if (460 <= x && x <= 510) {
					return ActionData{ CHECK };
				}
				else if (525 <= x && x <= 575) {
					return ActionData{ TOGGLEVIEW };
				}
				else if (1485 <= x && x <= 1900) {
					return ActionData{ EXIT };
				}
			}
			//[2] User clicks on the drawing area
			if (15 < x && x < 1330 && 205 < y && y < 685)
			{
				return ActionData{ DRAW_AREA,x,y };	//user want clicks inside drawing area
			}

			//Change Major
			if (1385 < x && x < 1500 && 260 < y && y < 285)
			{
				return ActionData{ SMAJOR,x,y };	//user want clicks inside the major box
			}
			//Change double major 
			if (1385 < x && x < 1500 && 310 < y && y < 335)
			{
				return ActionData{ SD_MAJOR,x,y };	//user want clicks inside the double major
			}
			//Change concentration
			if (1385 < x && x < 1500 && 365 < y && y < 390)
			{
				return ActionData{ SCON,x,y };	//user want clicks inside the concentration box
			}
			//Change double concentration
			if (1385 < x && x < 1500 && 410 < y && y < 435)
			{
				return ActionData{ SD_CON,x,y };	//user want clicks inside the double concentration box
			}
			//Change minor
			if (1385 < x && x < 1500 && 445 < y && y < 470)
			{
				return ActionData{ SMINOR,x,y };	//user want clicks inside the minor box
			}
			//calculate GPA
			if (1385 < x && x < 1500 && 225 < y && y < 250)
			{
				return ActionData{ SGPA,x,y };	//user want clicks inside the GPA box
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

void GUI::DrawStuInfo(const StudyPlan* plan) const {
	pWind->SetFont(CRS_HEIGHT * 0.45, BOLD, BY_NAME, "Gramound");
	pWind->SetPen(DARKGREEN);
	pWind->DrawString(1405, 195, plan->getStudLevel());
	pWind->DrawString(1405, 230, to_string(plan->getGPA()));
	pWind->DrawString(1405, 265, plan->getMajor());
	pWind->DrawString(1405, 315, plan->getD_Major());
	pWind->DrawString(1405, 370, plan->getCon());
	pWind->DrawString(1405, 415, plan->getD_Con());
	pWind->DrawString(1405, 450, plan->getMinor());
}



GUI::~GUI()
{
	delete pWind;
}
