#include "AcademicYear.h"
#include "../GUI/GUI.h"
#include "../GUI/Drawable.h"
#include <algorithm>
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
array<int, 3> AcademicYear::getSemCredits() const {
	return semCredits;
}
//Adds a course to this year in the spesified semester
bool AcademicYear::AddCourse(Course* pC, SEMESTER sem, Registrar* pReg)
{
	//TODO:
	//This function still needs many checks to be compelete
	bool found = 1; 
	vector<AcademicYearOfferings> offerings = pReg->getRules()->OfferingsList;
	/*for (auto year : offerings) {
		for (auto course_code : year.Offerings[sem]) {
			if (course_code == pC->getCode()) {
				found = 1;
				break;
			};
		}
	}*/
	if (found) {
		YearCourses[sem].push_back(pC);
		TotalCredits += pC->getCredits();
		semCredits[sem] += pC->getCredits();
		if (pC->getType() == "UNIV") TotalUnivCredits += pC->getCredits();
		if (pC->getType() == "MAJOR") TotalMajorCredits += pC->getCredits();
		if (pC->getType() == "CON") TotalConcentrationCredits += pC->getCredits();
		if (pC->getType() == "TRACK") TotalTrackCredits += pC->getCredits();
	}
	else {

		//TODO: acording to course type incremenet corrsponding toatl hours for that year

		string Msg = "This course " + pC->getCode() + " isn't offered in " + (sem ? sem == 1 ? "Spring" : "Summer" : "Fall") + " semester ";
		pReg->getGUI()->PrintMsg(Msg + " ... Press any key if you finished reading");
		char temp;
		pReg->getGUI()->getWindow()->WaitKeyPress(temp);  // wait for the user to finish
	}
	return found;
}

bool AcademicYear::DeleteCourse(int x, int y) {
	int cX, cY, i = 0;
	for (auto sem : YearCourses) {
		for (auto course = sem.begin(); course != sem.end(); ++course){
			if ((*course)->isCourse(x,y)) {
				auto pC = (*course);
				TotalCredits -= pC->getCredits();
				semCredits[i] -= pC->getCredits();
				if (pC->getType() == "UNIV") TotalUnivCredits -= pC->getCredits();
				if (pC->getType() == "MAJOR") TotalMajorCredits -= pC->getCredits();
				if (pC->getType() == "CON") TotalConcentrationCredits -= pC->getCredits();
				if (pC->getType() == "TRACK") TotalTrackCredits -= pC->getCredits();
				sem.erase(course);
				YearCourses[i] = sem;
				return true;//break;
			}
		}
		i++;
	}
	return false;
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

int AcademicYear::getCoursePosition(int year, Course_Code CC) const {
	for (int sem = FALL; sem < SEM_CNT; sem++) {
		for (auto course : YearCourses[sem]) {
			Course_Code code = course->getCode();				// code transformation to match all the posible cases of course code CC
			transform(code.begin(), code.end(), code.begin(), ::tolower);
			code.erase(remove_if(code.begin(), code.end(), ::isspace), code.end());

			if (code == CC) {  // check for every course for the given course code if found return the course position
				return year * 3 + sem;  //the position equation
			}
		}
	}
	return -1;  //if the course is not found in this year return -1
}

int AcademicYear::getCoursePosition(int year, Course_Code CC, int& crd) const {
	for (int sem = FALL; sem < SEM_CNT; sem++) {
		for (auto course : YearCourses[sem]) {
			Course_Code code = course->getCode();				// code transformation to match all the posible cases of course code CC
			transform(code.begin(), code.end(), code.begin(), ::tolower);
			code.erase(remove_if(code.begin(), code.end(), ::isspace), code.end());
			crd += course->getCredits();
			if (code == CC) {  // check for every course for the given course code if found return the course position
				return year * 3 + sem;  //the position equation
			}
		}
	}
	return -1;  //if the course is not found in this year return -1
}