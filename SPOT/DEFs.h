#pragma once

//This header file contains some defenitions to be used all over the application
#include <string>
using namespace std;
typedef string Course_Code;


//Semesters
enum SEMESTER
{
	FALL,
	SPRING,
	SUMMER,
	SEM_CNT	//number of semesters 
};


//All possible actions
enum ActionType
{
	ADD_CRS,	//Add a course to study plan
	DEL_CRS,	//Delete a course from study plan


	SAVE,		//Save a study plan to file
	LOAD,		//Load a study plan from a file

	REPLACE,											//UNDO,		//Undo the last Action preformed
	REORDER,										//REDO,		//Redo the last Action canceled

	NOTES,
	CHECK,
	TOGGLEVIEW,
	EXIT,		//Exit the application

	STATUS_BAR,	//A click on the status bar
	MENU_BAR,	//A click on an empty place in the menu bar
	DRAW_AREA,	//A click in the drawing area

	CANCEL,		//ESC key is pressed
	RIGHTCLICK,

	SMAJOR,
	SD_MAJOR,
	SCON,
	SD_CON,
	SMINOR,
	SGPA,
	//TODO: Add more action types

};

//to sotre data related to the last action
struct ActionData
{
	ActionType actType;
	int x, y;
	
};

/*enum Major {
	CIE,
	ENV,
	NANOE,
	REE,
	SPC,
	PEU,
	BMS,
	MS,
	NANOS,
	Major_NUM
};*/

enum CStatus {
	Done,
	InProgress,
	Pending,
	NStatus
};
