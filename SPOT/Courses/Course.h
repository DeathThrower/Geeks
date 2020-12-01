#pragma once
#include <string>
#include <vector>
#include <fstream>
using namespace std;
#include "..\DEFs.h"

#include "../GUI/Drawable.h"

//Base class for all types of courses
class Course : public Drawable
{
	// Title and code were const
	Course_Code code;	//course code: e.g. "CIE202". This is the course ID
	string Title;		//course title: e.g. "Fundamentals of Computer Programming"
	int credits;	//no. of course credits
	string type;	//Univ, track, or major.....etc.
	bool Done;		//Done or not yet?
	vector<Course_Code> PreReq;	//list of prerequisites
	vector<Course_Code> CoReq;	//list of prerequisites
public:
	Course(Course_Code r_code,string r_title, int crd);
	string getTitle() const;
	string getCode() const;
	int getCredits() const;
	//return true if the point(x,y) is in the box of the course
	bool isCourse(int x, int y) const;
	void DrawMe(GUI*) const;
	virtual ~Course();
	/* setters*/
	void setTitle(string title) ;
	void setCode(Course_Code code)  ;
	void setCredits(int credits) ;
	void setType(string type) ;
	void setDone(bool Done);
	void setPreReq(vector<Course_Code> PreReq);
	void setCoReq(vector<Course_Code> CoReq);

	void saveCourse(ofstream & outdata) const;

};
