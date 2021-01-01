#pragma once
#include <vector>
#include "AcademicYear.h"
#include "../GUI/Drawable.h"

//A full study plan for as student
class StudyPlan:public Drawable
{
	int TotalCredits=0;		//total no. of credit hours for courses registred in this year
	int TotalUnivCredits=0, TotalMajorCredits=0,
		TotalTrackCredits=0, TotalConcentrationCredits=0,
		TotalMinorCredits=0;
	string major;
	vector<AcademicYear*> plan;	//plan is a list of academic years

	int coursesStatus[3]{ 0,0,0 };  // array represent how many (Done(index 0), In progress(index 1), Pending(index 2)) course credits

	string PlanNotes;
public:
	StudyPlan(int yearnum=5);
	vector<AcademicYear*> getPlan() const;
	//get the course using x and y coordinates if the course is not found return null
	Course* getCourse(int x, int y) const;

	//find how many courses who have the x and y coordinates inside of it. --inputs: x and y integers --outputs: n int represent the number of the courses
	int getnCourse(int x, int y) const;

	bool AddCourse(Course*, int year, SEMESTER , Registrar* pReg);
	//delete a course from a specific x and y coordinates (erase the course pointer from the vector) the inputs are the x and y coordinates
	bool DeleteCourse(int ,int);

	//return a semester and year in a vector of int and the inputs are a x and y coordinates
	vector<int> getSem_Year(int, int);

	string getMajor();
	void setMajor(string nmajor);

	//save the study plan into a file the inputs is the file object (ofstream)
	void saveStudyPlan(ofstream& outdata) const;

	//clear all the content of the plan (clear the courses in each year in each semester)
	void clearStudyPlan();

	//return the position of the course return -1 if not found || (position to int: year*3+semester)
	int getCoursePosition(Course_Code) const;

	//check the preReq and coReq and return a string represent a message to the user
	string checkpreReqCoreReq() const;

	//check the program requirement 
	string checkProgramReq(Rules* r) const;


	//check Number of credits per semester is within Range 
	string checkCrSem(Rules* r) const;
	//decrease the old status credits in the coursesStatus array and increase the new status credits
	void changeCStatusCrd(CStatus Old, CStatus New, int crd);

	void virtual DrawMe(GUI*) const;
	virtual ~StudyPlan();
};

