#pragma once
#include <string>
using namespace std;

#include "..\DEFs.h"
#include "CMUgraphicsLib\CMUgraphics.h"

class Course;
class AcademicYear;
//user interface class
class GUI
{
	
	enum MENU_ITEM //The items of the menu (you should add more items)
	{
		//Note: Items are ordered here as they appear in the menu
		//If you want to change the menu items order, just change the order here
		ITM_ADD,		//Add a new course

						//TODO: Add more items names here
		ITM_ex1,
		ITM_ex2,
		ITM_ex3,
		ITM_ex4,
		ITM_ex5,
		ITM_ex6,
		ITM_ex7,



		ITM_EXIT,		//Exit item

		ITM_CNT			//no. of menu items ==> This should be the last line in this enum

	};
	string MenuItemImages[ITM_CNT];
	//Some constants for GUI
	static const int	WindWidth = 1360, WindHeight = 745,	//Window width and height
		wx = 15, wy = 15,		//Window starting coordinates
		StatusBarHeight = 50,	//Status Bar Height
		MenuBarHeight = 75,		//Menu Bar Height (distance from top of window to bottom line of menu bar)
		MenuItemWidth = 50;		//Width of each item in the menu



	color DrawColor = BLACK;		//Drawing color
	color FillColor = SALMON;		//Filling color (for courses)
	color HiColor = RED;			//Highlighting color
	color ConnColor = GREEN;		//Connector color
	color MsgColor = WHITE;			//Messages color
	color BkGrndColor = WHITE;	//Background color
	color StatusBarColor = BROWN;//statusbar color
	string WindTitle = "Study-Plan Organizational Tool (SPOT)";

	window* pWind;
public:
	GUI();
	void CreateMenu() const;
	void ClearDrawingArea() const;
	void ClearStatusBar() const;	//Clears the status bar

	//output functions
	void PrintMsg(string msg) const;		//prints a message on status bar

	//Drawing functions
	void DrawCourse(const Course* );
	void DrawAcademicYear(const AcademicYear*);
	void UpdateInterface() const;
	
	//input functions
	ActionData GUI::GetUserAction(string msg = "") const;
	string GetSrting() const;
	
	window* getWindow() const;

	Course* Drag_Drop(Course* c);


	

	~GUI();
};

