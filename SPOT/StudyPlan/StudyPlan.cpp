#include "StudyPlan.h"
#include <algorithm>


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
bool StudyPlan::AddCourse(Course* pC, int year, SEMESTER sem , Registrar* pReg)
{

	if (plan[year - 1]->AddCourse(pC, sem, pReg)) {
		TotalCredits += pC->getCredits();
		coursesStatus[0] += pC->getCredits();
		if (pC->getType() == "UNIV") TotalUnivCredits += pC->getCredits();
		if (pC->getType() == "MAJOR") TotalMajorCredits += pC->getCredits();
		if (pC->getType() == "CON") TotalConcentrationCredits += pC->getCredits();
		if (pC->getType() == "TRACK") TotalTrackCredits += pC->getCredits();
		return true;
	}
	else {
		return false;
	}
}

bool StudyPlan::DeleteCourse(int x, int y)
{	
	for (auto i : plan) {
		auto pC = getCourse(x, y);
		bool t = i->DeleteCourse(x, y);
		if (t) {
			int deleted_crd = pC->getCredits();
			TotalCredits -= deleted_crd;
			if (pC->getType() == "UNIV") TotalUnivCredits -= deleted_crd;
			if (pC->getType() == "MAJOR") TotalMajorCredits -= deleted_crd;
			if (pC->getType() == "CON") TotalConcentrationCredits -= deleted_crd;
			if (pC->getType() == "TRACK") TotalTrackCredits -= deleted_crd;
			break;
		}
	}
	
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

string StudyPlan::getMajor() const{
	return major;
}

void StudyPlan::setMajor(string nmajor)
{
	major = nmajor;
}

string StudyPlan::getD_Major() const{
	return D_major;
}

void StudyPlan::setD_Major(string nmajor)
{
	D_major = nmajor;
}

string StudyPlan::getCon() const{
	return con;
}

void StudyPlan::setCon(string Con)
{
	con = Con;
}

string StudyPlan::getD_Con() const{
	return D_con;
}

void StudyPlan::setD_Con(string Con)
{
	D_con = Con;
}
string StudyPlan::getMinor() const{
	return minor;
}

void StudyPlan::setMinor(string Minor)
{
	minor = Minor;
}
float StudyPlan::getGPA() const {
	return GPA;
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
	pGUI->DrawStuInfo(this);
}

void StudyPlan::saveStudyPlan(ofstream& outdata) const {
	for (int i = 0; i < plan.size();i++) {
		plan[i]->saveAcademicYear(outdata, i);  // let every year save it self
	}
}

void StudyPlan::changeCStatusCrd(CStatus Old, CStatus New, int crd) {
	coursesStatus[static_cast<int>(Old)] -= crd;
	coursesStatus[static_cast<int>(New)] += crd;
}

string StudyPlan::getStudLevel() const {
	if (coursesStatus[0] <= 32) {
		return "Freshman";
	}
	else if (coursesStatus[0] <= 64) {
		return "Sophomore";
	}
	else if (coursesStatus[0] <= 96){
		return "Junior";
	}
	else {
		return "Senior";
	}
}

int StudyPlan::getCoursePosition(Course_Code CC) const {
	// code transformation to match all the posible cases of course code 
	transform(CC.begin(), CC.end(), CC.begin(), ::tolower);
	CC.erase(remove_if(CC.begin(), CC.end(), ::isspace), CC.end());

	for (int i = 0; i < plan.size(); i++) {
		int position = plan[i]->getCoursePosition(i, CC);  // check for every year if the course code exist or not
		if (position != -1) {  // if the course exist return the course position
			return position;
		}
	}
	return -1;  // if the course is not exist return -1
}
string StudyPlan::checkProgramReq(Rules *r) const {
	string errorMsg;
	if (TotalCredits < r->totalCredit) {
		errorMsg = "Number of Credits " + to_string(TotalCredits) + " is less than the required total number which is " + to_string(r->totalCredit);
		return errorMsg;
	}
	if (TotalCredits > (r->totalCredit)+15) {
		errorMsg = "Number of Credits " + to_string(TotalCredits) + " is more than the required allowed number which is " + to_string((r->totalCredit)+15);
		return errorMsg;
	}
	if (TotalMajorCredits < r->ReqMajorCredits) {
		errorMsg = "Number of Major Credits " + to_string(TotalMajorCredits) + " is less than required Major number which is " + to_string(r->ReqMajorCredits);
		return errorMsg;
	}
	if (TotalTrackCredits < r->ReqTrackCredits) {
		errorMsg = "Number of Track Credits " + to_string(TotalTrackCredits) + " is less than required Track number which is " + to_string(r->ReqTrackCredits);
		return errorMsg;
	}
	if (TotalUnivCredits < r->ReqUnivCredits) {
		errorMsg = "Number of University Credits " + to_string(TotalUnivCredits) + " is less than required University number which is " + to_string(r->ReqUnivCredits);
		return errorMsg;
	}
	for (auto courseCode : r->UnivCompulsory) {
		if (getCoursePosition(courseCode) == -1) {
			errorMsg = "Error Course : " + courseCode + " is University Compulsory but not found in the plan";
			return errorMsg;
		}
	}
	for (auto courseCode : r->TrackCompulsory) {
		if (getCoursePosition(courseCode) == -1) {
			errorMsg = "Error Course : " + courseCode + " is Track Compulsory but not found in the plan";
			return errorMsg;
		}
	}
	for (auto courseCode : r->MajorCompulsory) {
		if (getCoursePosition(courseCode) == -1) {
			errorMsg = "Error Course : " + courseCode + " is Major Compulsory but not found in the plan";
			return errorMsg;
		}
	}
	return "Everything is ok with The Program Requirements";
}
string StudyPlan::checkCrSem(Rules* r) const {
	string errorMsg;
	// I will hardcode these values even though in the future they might retrieved from a file. it should be as follows
	// minCredits  = r->SemMinCredit 
	int minCredits = 12; int maxCredits = 21, yearN = 1, semN=0;
	for (auto year : plan) {
		semN = 0;
		for (auto semCredit : year->getSemCredits()) {
			if (semN != 2) //Not summer
			{
				if (semCredit < minCredits || semCredit > maxCredits) {
					errorMsg = "In Year " + to_string(yearN) + (!semN ? " Fall" :  " Spring" ) + " Semester has " + to_string(semCredit) + " credits which is out of bounds.";
					return errorMsg;
				}
			}
			else {
				if (semCredit < 0 || semCredit > 8) {
					errorMsg = "In Year " + to_string(yearN) + "Summer Semester has " + to_string(semCredit) + " credits which is out of bounds.";
					return errorMsg;
				}
			}
			semN++;
		} 
		yearN++;
	}
	return "SemCred Check: Success. Each Semester Total Credits is within bounds. ";
}
string StudyPlan::checkpreReqCoreReq() const {
	for (int i = 0; i < plan.size(); i++) {						// loop over every year
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
