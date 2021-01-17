#include "ActionCheck.h"

ActionCheck::ActionCheck(Registrar* p) :Action(p)
{
}
ActionCheck::~ActionCheck()
{
}

void ActionCheck::generateReport() const {
	vector<string> errorMsgs = pReg->getStudyPlan()->getErrorMsg();
	string file_name = "report.txt";
	ofstream file;
	file.open(file_name);
	for (auto msg : errorMsgs) {
		file << msg << endl;
	}
	file.close();
}

bool ActionCheck::Execute() {
	vector<string> checkPreCo, checkProg, checkCrSem;
	checkPreCo = pReg->getStudyPlan()->checkpreReqCoreReq();
	checkProg = pReg->getStudyPlan()->checkProgramReq(pReg->getRules());
	checkCrSem = pReg->getStudyPlan()->checkCrSem(pReg->getRules());
	window* win = new window(1320, 768, -10, 0);
	win->SetPen(BLACK, 1);
	win->SetBrush(RED);
	win->DrawRectangle(1250, 720, 1300, 750);
	win->SetFont(20, BOLD, BY_NAME, "Arial");
	win->DrawString(1256, 726, "EXIT");
	int x, y = 0;
	win->SetPen(RED, 2);
	win->SetFont(20, BOLD, BY_NAME, "Arial");
	win->DrawString(5, 5 + y, "Prereq and Coreq Check (Critical issue) : ");
	win->SetPen(BLACK, 2);
	win->SetFont(15, BOLD, BY_NAME, "Arial");
	for (string msg : checkPreCo) {
		y += 20;
		win->DrawString(5, 5 + y, msg);
	}
	y += 20;
	win->SetPen(RED, 2);
	win->SetFont(20, BOLD, BY_NAME, "Arial");
	win->DrawString(5, 5 + y, "Program requirement Check (Critical issue) :");
	win->SetPen(BLACK, 2);
	win->SetFont(15, BOLD, BY_NAME, "Arial");
	for (string msg : checkProg) {
		y += 20;
		win->DrawString(5, 5 + y, msg);
	}
	y += 20;
	win->SetPen(RED, 2);
	win->SetFont(20, BOLD, BY_NAME, "Arial");
	win->DrawString(5, 5 + y, "Crediet per Semester Check (Moderate issue) :");
	win->SetPen(BLACK, 2);
	win->SetFont(15, BOLD, BY_NAME, "Arial");
	for (string msg : checkCrSem) {
		y += 20;
		win->DrawString(5, 5 + y, msg);
	}
	while (true) {
		win->WaitMouseClick(x, y);
		if (1250 < x && x < 1300 && 720 < y && y < 750) {
			delete win;
			break;
		}
	}
	generateReport();
	return true;
}