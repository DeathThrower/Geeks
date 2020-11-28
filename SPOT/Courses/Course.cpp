#include "Course.h"
#include "../GUI/GUI.h"

Course::Course(Course_Code r_code, string r_title, int crd):code(r_code),Title(r_title)
{
	credits = crd;
}

Course::~Course()
{
}

Course_Code Course::getCode() const
{
	return code;
}

string Course::getTitle() const
{
	return Title;
}

//return course credits
int Course::getCredits() const
{
	return credits;
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
void Course::setCredits(int credits){
	this->credits = credits;
}
void Course::setType(string type) {
	this->type = type;
}
void Course::setDone(bool Done) {
	this->Done = Done;
}
void Course::setPreReq(vector<Course_Code> PreReq) {
	this->PreReq = PreReq;
}
void Course::setCoReq(vector<Course_Code> CoReq) {
	this->CoReq = CoReq;
}