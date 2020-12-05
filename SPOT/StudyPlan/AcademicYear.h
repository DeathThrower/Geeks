#pragma once
#include <vector>
#include "../Registrar.h"
#include "..\Courses\Course.h"
#include "../GUI/Drawable.h"
//Represent one year in the student's study plan
class AcademicYear:public Drawable
{
	int TotalCredits=0;		//total no. of credit hours for courses registred in this year
	int TotalUnivCredits=0, TotalMajorCredits=0,
		TotalTrackCredits=0, TotalConcentrationCredits=0,
		TotalMinorCredits=0;

	//Each year is an array of 3 lists of courses. Each list cossrsponds to a semester
	//So YearCourses[FALL] is the list of FALL course in that year
	//So YearCourses[SPRING] is the list of SPRING course in that year
	//So YearCourses[SUMMER] is the list of SUMMER course in that year
	vector<Course*> YearCourses[SEM_CNT];
	
public:
	AcademicYear();
	virtual ~AcademicYear();
	vector<Course*> getCourses(int sem) const;
	bool AddCourse(Course*, SEMESTER );
	bool DeleteCourse(int, int);
	void clearYear();
	Course* getCourse(int x,int y)const;
	int getSem(int, int); // get Semester & Year
	void virtual DrawMe(GUI*) const;

	void saveAcademicYear(ofstream& outdata, int yearnum) const;
};

