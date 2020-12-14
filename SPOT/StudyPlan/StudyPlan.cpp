#include "StudyPlan.h"



StudyPlan::StudyPlan(int yearnum)
{
	//By default, the study plan starts with 5 years
	//More year can be added
	for (int i = 0; i < yearnum; i++)
		plan.push_back(new AcademicYear);
}

vector<AcademicYear*> StudyPlan::getPlan() const {
	return plan;
}

//adds a course to the study plan in certain year, semester
//year idetifies year number to add course to 1=first, 2 = 2nd,....
bool StudyPlan::AddCourse(Course* pC, int year, SEMESTER sem)
{

	plan[year - 1]->AddCourse(pC, sem);
	TotalCredits += pC->getCredits();



	return true;
}

bool StudyPlan::DeleteCourse(int x, int y)
{
	for (auto i : plan)
		i->DeleteCourse(x, y);
	return true;
}

vector<int> StudyPlan::getSem_Year(int x, int y) 
{
	vector<int> sy;
	int sem = -1, j = 0;
	for (auto i : plan) {
		sem = i->getSem(x, y, j);
		if (sem != -1) {
			sy.insert(sy.end(), { sem,j });
			return sy;
		}
		j++;
	}
	sy.insert(sy.end(), { -1,-1 });
	return sy;
}

Course* StudyPlan::getCourse(int x, int y) const {
	for (auto year :plan) {  // loop for every year
		Course* course = year->getCourse(x, y);  // get the course from the year if the course is not found return null
		if (course!=NULL) {
			return course;
		}
	}
	return NULL;
}

int StudyPlan::getnCourse(int x, int y) const {
	int n = 0;
	for (auto year : plan) {  // loop for every year
		n += year->getnCourse(x, y);
	}
	return n;
}

string StudyPlan::getMajor() {
	return major;
}

void StudyPlan::setMajor(string nmajor)
{
	major = nmajor;
}

void StudyPlan::clearStudyPlan() {
	for (auto year : plan) {
		year->clearYear();
	}
	major = "";
	TotalCredits = 0;
	TotalUnivCredits = 0;
	TotalMajorCredits = 0;
	TotalTrackCredits = 0;
	TotalConcentrationCredits = 0;
	TotalMinorCredits = 0;
}

void StudyPlan::DrawMe(GUI* pGUI) const
{
	//Plan draws all year inside it.
	for (int i = 0; i < plan.size(); i++)
		plan[i]->DrawMe(pGUI);
}

void StudyPlan::saveStudyPlan(ofstream& outdata) const {
	for (int i = 0; i < plan.size();i++) {
		plan[i]->saveAcademicYear(outdata, i);  // let every year save it self
	}
}

StudyPlan::~StudyPlan()
{
}
