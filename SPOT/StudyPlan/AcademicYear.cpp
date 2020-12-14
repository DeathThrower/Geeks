#include "AcademicYear.h"
#include "../GUI/GUI.h"
#include "../GUI/Drawable.h"

AcademicYear::AcademicYear()
{
	//TODO: make all necessary initializations
}


AcademicYear::~AcademicYear()
{
}

vector<Course*> AcademicYear::getCourses(int sem) const {
	return YearCourses[sem];
}

//Adds a course to this year in the spesified semester
bool AcademicYear::AddCourse(Course* pC, SEMESTER sem)
{
	//TODO:
	//This function still needs many checks to be compelete

	YearCourses[sem].push_back(pC);
	TotalCredits += pC->getCredits();

	//TODO: acording to course type incremenet corrsponding toatl hours for that year


	return true;
}

bool AcademicYear::DeleteCourse(int x, int y) {
	int cX, cY, i =0;
	for (auto sem : YearCourses) {
		for (auto course = sem.begin(); course != sem.end(); ++course){
			if ((*course)->isCourse(x,y)) {
				TotalCredits -= (*course)->getCredits();
				sem.erase(course);
				YearCourses[i] = sem;
				break;
			}
		}
		i++;
	}
	return true;
}

int AcademicYear::getSem(int x, int y, int year) {
	int cX = 0,i = 0;
	for (auto sem : YearCourses) {
		int nCourses = sem.size();
		if (!nCourses) {
			if (x >= (year ) * 263 + 20 && x <= (year ) * 263 + 108) {
				return 0;
			}
			else if (x >= (year ) * 263 + 108 && x <= (year ) * 263 + 196) {
				return 1;
			}
			else if (x >= (year ) * 263 + 196 && x <= (year ) * 263 + 196 + 88) {
				return 2;
			}
			return -1;
		};
	}
	return -1;
}

void AcademicYear::DrawMe(GUI* pGUI) const
{
	pGUI->DrawAcademicYear(this);
	//Draw all semesters inside this year by iterating on each semester list
	//to get courses and draw each course
	
	for (int sem = FALL; sem < SEM_CNT; sem++) {
		//for (auto it = YearCourses[sem].begin(); it != YearCourses[sem].end(); ++it)
		//{
		//	(*it)->DrawMe(pGUI);	//call DrawMe for each course in this semester
		//}
		for (auto it: YearCourses[sem]) {
			it->DrawMe(pGUI);
		}
	}
}

void AcademicYear::saveAcademicYear(ofstream& outdata, int yearnum) const {
	for (int sem = FALL; sem < SEM_CNT; sem++) {
		outdata << "Year " << yearnum+1;
		outdata << "," << Registrar::sem2str(SEMESTER(sem));
		for (Course* course : getCourses(sem)) {
			course->saveCourse(outdata);
		}
		outdata << "\n";
	}
}

Course* AcademicYear::getCourse(int x, int y)const {
	for (int sem = FALL; sem < SEM_CNT; sem++) {
		for (Course* course : getCourses(sem)) {
			if (course->isCourse(x, y)) {
				return course;
			}
		}
	}
	return NULL;
}

int AcademicYear::getnCourse(int x, int y)const {
	int n = 0;
	for (int sem = FALL; sem < SEM_CNT; sem++) {
		for (Course* course : getCourses(sem)) {
			if (course->isCourse(x, y)) {
				n++;
			}
		}
	}
	return n;
}

void AcademicYear::clearYear() {
	for (int sem = FALL; sem < SEM_CNT; sem++) {
		YearCourses[sem].clear();
	}
	TotalCredits = 0;
	TotalUnivCredits = 0;
	TotalMajorCredits = 0;
	TotalTrackCredits = 0;
	TotalConcentrationCredits = 0;
	TotalMinorCredits = 0;
}