
#include "Course.h"
#include "../GUI/GUI.h"


Course::Course(Course_Code r_code, string r_title, int crd) :code(r_code), Title(r_title)
{
	string g[] = { "A","A-","B+","B","B*","C+","C","C-","F" };
	for (int i = 0; i < 9; i++) {
		Grades[i] = g[i];
	}
	credits = crd;
	status = Done;
}

Course::~Course()
{
}
//getters

string Course::getGrade() const {
	return Grade;
}

Course_Code Course::getCode() const {
	return code;
}

string Course::getTitle() const {
	return Title;
}

int Course::getCredits() const {
	return credits;
}

vector<Course_Code> Course::getPreReq() const {
	return PreReq;
}

vector<Course_Code> Course::getCoReq() const {
	return CoReq;
}

string Course::getType() const {
	return type;
}

string Course::getIssue() const {
	return issue;
}

void Course::setIssue(string issue) {
	this->issue = issue;
}

CStatus Course::getStatus() const {
	return status;
}

bool Course::isCourse(int x, int y) const {
	int cY, cX;
	cX = getGfxInfo().x; cY = getGfxInfo().y;
	if (cX <= x && cX + 80 >= x && cY <= y && cY + 40 >= y) {  // checking if the x and y coordinates are inside the box of the course or not
		return true;
	}
	else {
		return false;
	}
}


void Course::DrawMe(GUI* pG) const
{
	pG->DrawCourse(this);
}
/* setters*/

void Course::setTitle(const string title) {
	this->Title = title;
};
void Course::setCode(Course_Code code) {
	this->code = code;
}
void Course::setCredits(int credits) {
	this->credits = credits;
}
void Course::setType(string type) {
	this->type = type;
}
void Course::setSatus(CStatus status) {
	this->status = status;
}
void Course::setPreReq(vector<Course_Code> PreReq) {
	this->PreReq = PreReq;
}
void Course::setCoReq(vector<Course_Code> CoReq) {
	this->CoReq = CoReq;
}
bool Course::setGrade(string letter) {
	bool found = 0;
	for (auto i : Grades) {
		if (letter == i) found = 1;
	}
	if(!found) return 0;
	this->Grade = letter;
	return true;
}
void Course::saveCourse(ofstream& outdata) const {
	outdata << "," << getCode();
}
