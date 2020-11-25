#include "ActionSaveStudyPlan.h"
ActionSaveStudyPlan::ActionSaveStudyPlan(Registrar* p) :Action(p)
{
}

bool ActionSaveStudyPlan::Execute() {
	int y=0;
	string filepath = pReg->savefilename();
	if (filepath!="") {
		ofstream outdata;
		outdata.open(filepath,ios::trunc);
		for (AcademicYear* year : pReg->getStudyPlay()->getPlan()) {
			y++;
			for (int sem = FALL; sem < SEM_CNT; sem++) {
				outdata << "Year " << y;
				outdata << "," << pReg->sem2str(SEMESTER(sem));
				for (Course* course : year->getCourses(sem)) {
					outdata << "," << course->getCode();
				}
				outdata << "\n";
			}
		}
		outdata.close();
		return true;
	}
	else {
		return false;
	}
}

ActionSaveStudyPlan::~ActionSaveStudyPlan()
{
}
