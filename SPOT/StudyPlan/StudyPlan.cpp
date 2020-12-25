#include "StudyPlan.h"



StudyPlan::StudyPlan(int yearnum)
{
	//By default, the study plan starts with 5 years
	//More year can be added
	for (int i = 0; i < yearnum; i++)
		plan.push_back(new AcademicYear);
}

StudyPlan::~StudyPlan()
{
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

int StudyPlan::getCoursePosition(Course_Code CC) const {
	for (int i = 0; i < plan.size(); i++) {
		int position = plan[i]->getCoursePosition(i, CC);  // check for every year if the course code exist or not

		if (position != -1) {  // if the course exist return the course position
			return position;
		}
	}
	return -1;  // if the course is not exist return -1
}

string StudyPlan::checkpreReqCoreReq() const {
	for (int i = 0; i < plan.size(); i++) {						// loop aver every year
		for (int sem = FALL; sem < SEM_CNT;sem++) {
			for (auto course : plan[i]->getCourses(sem)) {		// loop over every course in every year
				int cPosition = i * 3 + sem;					// get the course position;

				for (Course_Code CC : course->getPreReq()) {	// loop over every course in the PreReq list in the course
					int preReqPosition = getCoursePosition(CC); // get the preReq course position

					// if the preReq course position is more than the course position (the preReq course in a higher year or semesyter) or the preReq 
					// is not found return the error message
					if (preReqPosition > cPosition) {
						string errorMsg = "Error in course " + course->getCode() + " : the PreReq course " + CC + " exist in year or semester higher";
						return errorMsg;
					}
					else if(preReqPosition == -1){
						string errorMsg = "Error in course " + course->getCode() + " : the PreReq course " + CC + " is not found";
						return errorMsg;
					}
				}
				for (Course_Code CC : course->getCoReq()) {	// loop over every course in the CoReq list in the course
					int coReqPosition = getCoursePosition(CC); // get the coReq course position

					// if the coReq course position is not the same as course position (the coReq course in a higher year or semesyter) or the coReq 
					// is not found return the error message
					if (coReqPosition != cPosition) {
						string errorMsg = "Error in course " + course->getCode() + " : the CoReq course " + CC + " exist in year or semester different from the course";
						return errorMsg;
					}
					else if(coReqPosition == -1){
						string errorMsg = "Error in course " + course->getCode() + " : the CoReq course " + CC + " is not found";
						return errorMsg;
					}
				}
			}
		}
	}
	return "Every thing is ok in the PreReq and CoReq Check";
}
