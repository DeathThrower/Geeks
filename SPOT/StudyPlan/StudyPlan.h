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
	Major major=Major_NUM;
	vector<AcademicYear*> plan;	//plan is a list of academic years

	string PlanNotes;
public:
	StudyPlan(int yearnum=5);
	vector<AcademicYear*> getPlan() const;
	bool AddCourse(Course*, int year, SEMESTER);
	Course* getCourse(int x, int y) const;
	bool DeleteCourse(int ,int);
	vector<int> getSem_Year(int, int);
	Major getMajor();
	void setMajor(Major nmajor);
	void virtual DrawMe(GUI*) const;
	void saveStudyPlan(ofstream& outdata) const;
	void clearStudyPlan();
	virtual ~StudyPlan();
};

