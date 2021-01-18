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
	vector<AcademicYear*> plan;	//plan is a list of academic years

	float GPA = 0;
	string major = "";
	string D_major = "";
	string con = "";
	string D_con = "";
	string minor = "";
	
	int coursesStatus[3]{ 0,0,0 };  // array represent how many (Done(index 0), In progress(index 1), Pending(index 2)) course credits
	
	vector<string> msg_errors; //Contains all error messages

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
	
	//getters and setters

	string getMajor() const;
	void setMajor(string nmajor);
	string getD_Major() const;
	void setD_Major(string nmajor);
	string getCon() const;
	void setCon(string nmajor);
	string getD_Con() const;
	void setD_Con(string nmajor);
	string getMinor() const;
	void setMinor(string nmajor);
	bool loadMinor(string str, Rules* pRegRules);
	float getGPA() const;

	// get error messages vector
	vector<string> getErrorMsg() const;

	//save the study plan into a file the inputs is the file object (ofstream)
	void saveStudyPlan(ofstream& outdata) const;

	//clear all the content of the plan (clear the courses in each year in each semester)
	void clearStudyPlan();

	//return the position of the course return -1 if not found || (position to int: year*3+semester)
	int getCoursePosition(Course_Code) const;

	//function overloading
	int getCoursePosition(Course_Code, int&) const;

	//check the preReq and coReq and return a string represent a message to the user
	vector<string> checkpreReqCoreReq();

	//check the program requirement 
	vector<string> checkProgramReq(Rules* r);

	//check the concentration requirement 
	vector<string> checkConcentrationReq(Rules* r);

	//check the double concentration
	vector<string> checkD_Con(Rules* pRules);

	//return the student level based on the number of credits of the done classes
	string getStudLevel() const;

	//check Number of credits per semester is within Range 
	vector<string> checkCrSem(Rules* r);
	//decrease the old status credits in the coursesStatus array and increase the new status credits
	void changeCStatusCrd(CStatus Old, CStatus New, int crd);

	//calaculate GPA
	void calculateGPA(Registrar *);

	//convert letter to GPA Points 
	float getLetterGPA(string letter) const;

	void virtual DrawMe(GUI*) const;
	virtual ~StudyPlan();
};

