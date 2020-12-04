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
												//REDO,		//Redo the last Action canceled

	EXIT,		//Exit the application

	STATUS_BAR,	//A click on the status bar
	MENU_BAR,	//A click on an empty place in the menu bar
	DRAW_AREA,	//A click in the drawing area

	CANCEL,		//ESC key is pressed
	RIGHTCLICK   

	//TODO: Add more action types

};

//to sotre data related to the last action
struct ActionData
{
	ActionType actType;
	int x, y;
	
};

enum Major {
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
};

//// convert string to SEMESTER
//SEMESTER str2sem(string str) {
//	if (str == "Fall" || str == "fall") {
//		return FALL;
//	}
//	else if (str == "Spring" || str == "spring") {
//		return SPRING;
//	}
//	else if (str == "Summer" || str == "summer") {
//		return SUMMER;
//	}
//	return SEM_CNT;
//}
//
//
////convert SEMESTER to string
//string sem2str(SEMESTER sem) {
//	switch (sem)
//	{
//	case FALL:
//		return "Fall";
//		break;
//	case SPRING:
//		return "Spring";
//		break;
//	case SUMMER:
//		return "Summer";
//		break;
//	case SEM_CNT:
//		return "";
//		break;
//	default:
//		return "";
//		break;
//	}
//}
