#include "StudyPlan.h"
#include <algorithm>
#include <sstream>


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
bool StudyPlan::loadMinor(string minor, Rules * pRegRules)
{
	
	//
	char result[MAX_PATH];
	string str = string(result, GetModuleFileName(NULL, result, MAX_PATH));
	str = str.erase(str.length() - 18, 18);
	int indx = str.find("\\");
	while (indx != string::npos) {
		str.replace(indx, 1, "/");
		indx = str.find("\\");
	}
	string file_name = str+ minor +"-minor.txt";
	ifstream rfile_(file_name);
	if (rfile_.is_open())
	{
		//line by line
		string line;
		vector<string> lines;
		while (getline(rfile_, line))
		{
			lines.push_back(line);
		}
		pRegRules->totalMinorCredit = stoi(lines[0]);
		pRegRules->totalCredit += stoi(lines[0]);
		if (lines[1].size() > 0)
		{
			stringstream minorComp(lines[1]);
			while (minorComp.good())
			{
				string substr;
				getline(minorComp, substr, ',');
				pRegRules->MinorCompulsory.push_back(substr);
			}
		}
		

		rfile_.close();
		return true;
	}
	return false;
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

int StudyPlan::getCoursePosition(Course_Code CC, int& crd) const {
	// code transformation to match all the posible cases of course code 
	transform(CC.begin(), CC.end(), CC.begin(), ::tolower);
	CC.erase(remove_if(CC.begin(), CC.end(), ::isspace), CC.end());

	for (int i = 0; i < plan.size(); i++) {
		int position = plan[i]->getCoursePosition(i, CC, crd);  // check for every year if the course code exist or not
		if (position != -1) {  // if the course exist return the course position
			return position;
		}
	}
	return -1;  // if the course is not exist return -1
}

vector<string> StudyPlan::checkProgramReq(Rules *r)  {
	string errorMsg;
	vector<string> errorMsgs;
	if (TotalCredits < r->totalCredit) {
		errorMsg = "Number of Credits " + to_string(TotalCredits) + " is less than the required total number which is " + to_string(r->totalCredit);
		msg_errors.push_back(errorMsg);
		errorMsgs.push_back(errorMsg);
	}
	if (TotalCredits > (r->totalCredit)+15) {
		errorMsg = "Number of Credits " + to_string(TotalCredits) + " is more than the required allowed number which is " + to_string((r->totalCredit)+15);
		msg_errors.push_back(errorMsg);
		errorMsgs.push_back(errorMsg);
	}
	if (TotalMajorCredits < r->ReqMajorCredits) {
		errorMsg = "Number of Major Credits " + to_string(TotalMajorCredits) + " is less than required Major number which is " + to_string(r->ReqMajorCredits);
		msg_errors.push_back(errorMsg);
		errorMsgs.push_back(errorMsg);
	}
	if (TotalTrackCredits < r->ReqTrackCredits) {
		errorMsg = "Number of Track Credits " + to_string(TotalTrackCredits) + " is less than required Track number which is " + to_string(r->ReqTrackCredits);
		msg_errors.push_back(errorMsg);
		errorMsgs.push_back(errorMsg);
	}
	if (TotalUnivCredits < r->ReqUnivCredits) {
		errorMsg = "Number of University Credits " + to_string(TotalUnivCredits) + " is less than required University number which is " + to_string(r->ReqUnivCredits);
		msg_errors.push_back(errorMsg);
		errorMsgs.push_back(errorMsg);
	}
	for (auto courseCode : r->UnivCompulsory) {
		if (getCoursePosition(courseCode) == -1) {
			errorMsg = "Error Course : " + courseCode + " is University Compulsory but not found in the plan";
			msg_errors.push_back(errorMsg);
			errorMsgs.push_back(errorMsg);
		}
	}
	for (auto courseCode : r->TrackCompulsory) {
		if (getCoursePosition(courseCode) == -1) {
			errorMsg = "Error Course : " + courseCode + " is Track Compulsory but not found in the plan";
			msg_errors.push_back(errorMsg);
			errorMsgs.push_back(errorMsg);
		}
	}
	for (auto courseCode : r->MajorCompulsory) {
		if (getCoursePosition(courseCode) == -1) {
			errorMsg = "Error Course : " + courseCode + " is Major Compulsory but not found in the plan";
			msg_errors.push_back(errorMsg);
			errorMsgs.push_back(errorMsg);
		}
	}
	if (errorMsgs.empty()) {
		errorMsgs.push_back("Everything is OK");
	}
	return errorMsgs;
}
vector<string> StudyPlan::checkCrSem(Rules* r) {
	string errorMsg;
	vector<string> errorMsgs;
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
					msg_errors.push_back(errorMsg);
					errorMsgs.push_back(errorMsg);
				}
				if (semCredit < minCredits) {
					errorMsg = "In this semester you need an underload petetion.";
					msg_errors.push_back(errorMsg);
					errorMsgs.push_back(errorMsg);
				}
				if (semCredit > maxCredits) {
					errorMsg = "In this semester you need an overload petetion.";
					msg_errors.push_back(errorMsg);
					errorMsgs.push_back(errorMsg);
				}
				

			}
			else {
				if (semCredit < 0 || semCredit > 8) {
					errorMsg = "In Year " + to_string(yearN) + "Summer Semester has " + to_string(semCredit) + " credits which is out of bounds.";
					msg_errors.push_back(errorMsg);
					errorMsgs.push_back(errorMsg);
				}
			}
			semN++;
		} 
		yearN++;
	}
	if (errorMsgs.empty()) {
		errorMsgs.push_back("Everything is OK");
	}
	return errorMsgs;
}
vector<string> StudyPlan::checkpreReqCoreReq() {
	vector<string> errorMsgs;
	for (int i = 0; i < plan.size(); i++) {						// loop over every year
		for (int sem = FALL; sem < SEM_CNT; sem++) {
			for (auto course : plan[i]->getCourses(sem)) {		// loop over every course in every year
				int cPosition = i * 3 + sem;					// get the course position;

				for (Course_Code CC : course->getPreReq()) {	// loop over every course in the PreReq list in the course
					int preReqPosition = getCoursePosition(CC); // get the preReq course position
					course->setIssue("None");
					// if the preReq course position is more than or equal the course position (the preReq course in a higher year or semesyter) or the preReq 
					// is not found return the error message
					if (preReqPosition >= cPosition) {
						//string errorMsg = "Error in course " + course->getCode() + " : the PreReq course " + CC + " exist in year or semester higher";
						string errorMsg = "Error in course " + course->getCode() + " : the PreReq course " + CC + " does not exist in year or semester lower";
						course->setIssue("Critical");
						msg_errors.push_back(errorMsg);
						errorMsgs.push_back(errorMsg);
					}
					else if (preReqPosition == -1) {
						string errorMsg = "Error in course " + course->getCode() + " : the PreReq course " + CC + " is not found";
						course->setIssue("Critical");
						msg_errors.push_back(errorMsg);
						errorMsgs.push_back(errorMsg);
					}
				}
				for (Course_Code CC : course->getCoReq()) {	// loop over every course in the CoReq list in the course
					int coReqPosition = getCoursePosition(CC); // get the coReq course position

					// if the coReq course position is not the same as course position (the coReq course in a higher year or semesyter) or the coReq 
					// is not found return the error message
					if (coReqPosition != cPosition) {
						string errorMsg = "Error in course " + course->getCode() + " : the CoReq course " + CC + " exist in year or semester different from the course";
						course->setIssue("Critical");
						msg_errors.push_back(errorMsg);
						errorMsgs.push_back(errorMsg);
					}
					else if (coReqPosition == -1) {
						string errorMsg = "Error in course " + course->getCode() + " : the CoReq course " + CC + " is not found";
						course->setIssue("Critical");
						msg_errors.push_back(errorMsg);
						errorMsgs.push_back(errorMsg);
					}
				}
			}
		}
	}
	if (errorMsgs.empty()) {
		errorMsgs.push_back("Everything is OK");
	}
	return errorMsgs;
}

vector<string> StudyPlan::checkOffering(Rules* r) {
	vector<AcademicYearOfferings> offerings = r->OfferingsList;
	vector<string> errorMsgs;
	string errorMsg;
	bool found;
	for (auto year : plan) {
		for (int sem = FALL;  sem < SEM_CNT ; sem++) {
			for (auto course : year->getCourses(sem)) {
				found = 0;
				course->setIssue("None");
				for (auto year : offerings) {
					for (auto course_code : year.Offerings[sem]) {
						if (course_code == course->getCode()) {
							found = 1;
							break;
						};
					}
					if (found)break;
				}
				if (!found) {
					errorMsg = "This course " + course->getCode() + " isn't offered in " + (sem ? sem == 1 ? "Spring" : "Summer" : "Fall") + " semester ";
					course->setIssue("Moderate");
					msg_errors.push_back(errorMsg);
					errorMsgs.push_back(errorMsg);
				}
				else {
					continue;
				}
			}
		}
	}
	if (errorMsgs.empty()) {
		errorMsgs.push_back("Everything is OK");
	}
	return errorMsgs;
}
vector<string> StudyPlan::checkConcentrationReq(Rules* r)
{
	vector<string> errorMsgs;
	string errorMsg;
	if (con != "") {
		int conNum = stoi(con) - 1;
		if (TotalConcentrationCredits < (r->ReqConCredits).at(conNum))
		{
			errorMsg = "Number of Credits " + to_string(TotalConcentrationCredits) + " is less than the required total number which is " + to_string((r->ReqConCredits).at(conNum));
			msg_errors.push_back(errorMsg);
			errorMsgs.push_back(errorMsg);
		}
		if (TotalConcentrationCredits > (r->ReqConCredits).at(conNum))
		{
			errorMsg = "Number of Credits " + to_string(TotalConcentrationCredits) + " is more than the required total number which is " + to_string((r->ReqConCredits).at(conNum));
			msg_errors.push_back(errorMsg);
			errorMsgs.push_back(errorMsg);
		}
		for (auto courseCode : (r->ConCompulsory).at(conNum)) {
			if (getCoursePosition(courseCode) == -1) {
				errorMsg = "Error Course : " + courseCode + " is Concentration Compulsory but not found in the concentration";
				msg_errors.push_back(errorMsg);
				errorMsgs.push_back(errorMsg);
			}
		}
		if (errorMsgs.empty()) {
			errorMsgs.push_back("Everything is OK");
		}
	}
	else {
		errorMsgs.push_back("You have not choosen a concentration");
	}
	return errorMsgs;
}

vector<string> StudyPlan::checkMinorReq(Rules* r)
{
	vector<string> errorMsgs;
	string errorMsg;
	vector<Course_Code> minorCourses = r->MinorCompulsory;
	if (getMinor() != "")
	{
		for (Course_Code course : minorCourses) {
			int crd = 0;
			if (getCoursePosition(course, crd) == -1) {
				errorMsg = "Course  " + course + " is in " + getMinor() + " Minor Compulsory but not found in the plan.";
				errorMsgs.push_back(errorMsg);
				msg_errors.push_back(errorMsg);
			}
		}
		if (errorMsgs.empty())
			errorMsgs.push_back("Minor Requirements are Fulfilled.");
	}
	else {
		errorMsgs.push_back("You haven't choosen a minor yet.");
	}
	return errorMsgs;
}

vector<string> StudyPlan::checkD_Con(Rules* pRules) {
	vector<string> msgs;
	if (D_con != "") {
		int index = stoi(D_con) - 1;
		int crd = 0;
		vector<Course_Code> conCourses = pRules->ConCompulsory[index];
		for (Course_Code course : conCourses) {
			if (getCoursePosition(course, crd) == -1) {
				msgs.push_back("Error Course : " + course + " is Double Concentration Compulsory but not found in the plan");
			}
		}
		if (crd < pRules->ReqConCredits[index]) {
			msgs.push_back("Number of Credits " + to_string(crd) + " is less than the required number for double concentration which is " + to_string(pRules->ReqConCredits[index]));
		}
		if (msgs.empty()) {
			msgs.push_back("Everything is OK");
		}
	}
	else {
		msgs.push_back("You have not choosen a double concentration");
	}
	return msgs;
}
vector<string> StudyPlan::getErrorMsg() const{
	return msg_errors;
}

float StudyPlan::getLetterGPA(string letter) const {
	string Grades[] = { "A","A-","B+","B","B*","C+","C","C-","F" };
	int index = distance(Grades, std::find(Grades, Grades + 9, letter));
	if (letter == "F" || index == 9 ) return 0;
	return 4 - (index / 3.0);
}
void StudyPlan::calculateGPA(Registrar *pReg){
	float tCrds = 0 , tPoints = 0;
	GUI* pGUI = pReg->getGUI();
	for (auto year : plan) {
		for (int sem = FALL; sem < SEM_CNT; sem++) {
			for (auto course : year->getCourses(sem)) {
				if (course->getStatus() == Done) {
					while (course->getGrade() == "") {
						pGUI->PrintMsg("Please Enter " + course->getCode() + " Grade or type Exit if you want to stop GPA Calculation : ");
						string grd = pGUI->GetSrting();
						if (grd == "Exit")  return;
						course->setGrade(grd);
					}
					tPoints += getLetterGPA(course->getGrade()) * course->getCredits();
					tCrds += course->getCredits();
				}
			}
		}
	}
	GPA = tPoints / tCrds;
}

bool StudyPlan::loadDMajor(string DMajor, Rules* myRules)
{
	//generate the file path      
	char result[MAX_PATH];
	string str = string(result, GetModuleFileName(NULL, result, MAX_PATH));
	str = str.erase(str.length() - 18, 18);
	int indx = str.find("\\");
	while (indx != string::npos) {
		str.replace(indx, 1, "/");
		indx = str.find("\\");
	}
	string filepath = str + "SPOT/Files/" + DMajor + "-Requirements.txt";

	//open the file and get the data from it. every case represent a line in the file and the default
	//represent the concentration courses  
	// see the file format if you need more details
	bool condition = false; //condition for checking if the file exist or not
	ifstream finput;
	finput.open(filepath);
	char* pch;
	char* context = nullptr;
	const int size = 410;
	char line[size];
	int mline = 0, index = 0;
	if (finput.is_open()) {
		while (finput.getline(line, size)) {
			index = 0;
			mline++;
			pch = strtok_s(line, ",", &context);
			switch (mline)
			{
			case 1:
				//myRules->totalCredit = stoi(pch);
				break;
			case 2:
				//myRules->ReqUnivCredits = stoi(pch);
				break;
			case 3:
				//myRules->ReqTrackCredits = stoi(pch);
				break;
			case 4:
				myRules->totalCredit += stoi(pch);
				break;
			case 5:
				//myRules->NumConcentration = stoi(pch);
				break;
				/*case 6:
					index++;
					while (pch != NULL) {
						if (index % 2 == 1) {
							myRules->ReqConCredits.push_back(stoi(pch));
						}
						pch = strtok_s(NULL, ",", &context);
						index++;
					}
					break;*/
					/*case 7:
						while (pch != NULL) {
							myRules->UnivCompulsory.push_back(pch);
							pch = strtok_s(NULL, ",", &context);
						}
						break;
					case 8:
						while (pch != NULL) {
							myRules->UnivElective.push_back(pch);
							pch = strtok_s(NULL, ",", &context);
						}
						break;
					case 9:
						while (pch != NULL) {
							myRules->TrackCompulsory.push_back(pch);
							pch = strtok_s(NULL, ",", &context);
						}
						break;*/
			case 10:
				while (pch != NULL) {
					myRules->DMajorCompulsory.push_back(pch);
					pch = strtok_s(NULL, ",", &context);
				}
				break;
				/*case 11:
					while (pch != NULL) {
						myRules->MajorElective.push_back(pch);
						pch = strtok_s(NULL, ",", &context);
					}
					break;*/
					/*default:
						if (mline % 2 == 0) {
							vector<Course_Code> Cvec;
							while (pch != NULL) {
								Cvec.push_back(pch);
								pch = strtok_s(NULL, ",", &context);
							}
							myRules->ConCompulsory.push_back(Cvec);
						}*
						else {
							vector<Course_Code> Evec;
							while (pch != NULL) {
								Evec.push_back(pch);
								pch = strtok_s(NULL, ",", &context);
							}
							myRules->ConElective.push_back(Evec);
						}
						break;*/
			}
		}
		return true;

	}
	else
	{
		return false;
	}
}

void StudyPlan::viewFilter(bool all, int year, int sem_, bool major, bool univ, bool track) {
	int yearN = 1; int semN = 1;
	for (auto yearVec : plan) {
		for (int sem = 0; sem < 3; sem++) {
			for (auto course : yearVec->getCourses(sem)) {
				if (all)
				{
					course->setVisible(true);
				}
				else if (year > 0)
				{
					if (year == yearN) {
						course->setVisible(true);
					}
					else {
						course->setVisible(false);
					}
				}
				else if (sem_ > 0) {
					if (sem_ == semN) {
						course->setVisible(true);
					}
					else {
						course->setVisible(false);
					}
				}
				else if (major) {
					if (course->getType() == "MAJOR")
					{
						course->setVisible(true);
					}
					else {
						course->setVisible(false);
					}
				}
				else if (univ) {
					if (course->getType() == "UNIV")
					{
						course->setVisible(true);
					}
					else {
						course->setVisible(false);
					}
				}
				else if (track) {
					if (course->getType() == "TRACK")
					{
						course->setVisible(true);
					}
					else {
						course->setVisible(false);
					}
				}
				
			}
			semN++;
		}
		yearN++;
	}


}