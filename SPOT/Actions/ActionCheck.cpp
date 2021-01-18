#include "ActionCheck.h"
ActionCheck::ActionCheck(Registrar* p) :Action(p)
{
}
ActionCheck::~ActionCheck()
{
}

void ActionCheck::generateReport() const {
	vector<string> errorMsgs = pReg->getStudyPlan()->getErrorMsg();
	string file_path = "report.txt";
	ofstream file;
	file.open(file_path);
	for (auto msg : errorMsgs) {
		file << msg << endl;
	}
	file.close();
}

bool ActionCheck::Execute() {
	vector<string> checkPreCo, checkProg, checkCrSem, checkD_Con, conReq, minorReq , offering;
	checkPreCo = pReg->getStudyPlan()->checkpreReqCoreReq();
	checkProg = pReg->getStudyPlan()->checkProgramReq(pReg->getRules());
	checkCrSem = pReg->getStudyPlan()->checkCrSem(pReg->getRules());
	checkD_Con = pReg->getStudyPlan()->checkD_Con(pReg->getRules());
	conReq = pReg->getStudyPlan()->checkConcentrationReq(pReg->getRules());
	offering = pReg->getStudyPlan()->checkOffering(pReg->getRules());
	minorReq = pReg->getStudyPlan()->checkMinorReq(pReg->getRules());
	window* win = new window(1320, 768, -10, 0);
	win->SetPen(BLACK, 1);
	win->SetBrush(RED);
	win->DrawRectangle(1180, 680, 1300, 750);
	win->SetFont(55, BOLD, BY_NAME, "Arial");
	win->DrawString(1186, 686, "EXIT");
	int x, y = 0;
	win->SetPen(RED, 2);
	win->SetFont(25, BOLD, BY_NAME, "Arial");
	win->DrawString(5, 5 + y, "Prereq and Coreq Check (Critical issue) : ");
	win->SetPen(BLACK, 2);
	win->SetFont(20, BOLD, BY_NAME, "Arial");
	for (string msg : checkPreCo) {
		y += 25;
		win->DrawString(5, 5 + y, msg);
	}
	y += 25;
	win->SetPen(RED, 2);
	win->SetFont(25, BOLD, BY_NAME, "Arial");
	win->DrawString(5, 5 + y, "Program requirement Check (Critical issue) :");
	win->SetPen(BLACK, 2);
	win->SetFont(20, BOLD, BY_NAME, "Arial");
	for (string msg : checkProg) {
		y += 25;
		win->DrawString(5, 5 + y, msg);
	}
	y += 25;
	win->SetPen(YELLOW, 2);
	win->SetFont(25, BOLD, BY_NAME, "Arial");
	win->DrawString(5, 5 + y, "Course Offering Check (Moderate issue) :");
	win->SetPen(BLACK, 2);
	win->SetFont(20, BOLD, BY_NAME, "Arial");
	for (string msg : offering) {
		y += 25;
		win->DrawString(5, 5 + y, msg);
	}
	y += 25;
	win->SetPen(YELLOW, 2);
	win->SetFont(25, BOLD, BY_NAME, "Arial");
	win->DrawString(5, 5 + y, "Credit per Semester Check (Moderate issue) :");
	win->SetPen(BLACK, 2);
	win->SetFont(20, BOLD, BY_NAME, "Arial");
	for (string msg : checkCrSem) {
		y += 25;
		win->DrawString(5, 5 + y, msg);
	}

	y += 25;
	win->SetPen(RED, 2);
	win->SetFont(25, BOLD, BY_NAME, "Arial");
	win->DrawString(5, 5 + y, "Concentration validity Check (Critical issue) :");
	win->SetPen(BLACK, 2);
	win->SetFont(20, BOLD, BY_NAME, "Arial");
	for (string msg : conReq) {
		y += 25;
		win->DrawString(5, 5 + y, msg);
	}
	y += 25;
	win->SetPen(RED, 2);
	win->SetFont(25, BOLD, BY_NAME, "Arial");
	win->DrawString(5, 5 + y, "Double Concentration Check (Critical issue) :");
	win->SetPen(BLACK, 2);
	win->SetFont(20, BOLD, BY_NAME, "Arial");
	for (string msg : checkD_Con) {
		y += 25;
		win->DrawString(5, 5 + y, msg);
	}
	y += 25;
	win->SetPen(RED, 2);
	win->SetFont(25, BOLD, BY_NAME, "Arial");
	win->DrawString(5, 5 + y, "Minor Requirements Check (Moderate issue) :");
	win->SetPen(BLACK, 2);
	win->SetFont(20, BOLD, BY_NAME, "Arial");
	for (string msg : minorReq) {
		y += 25;
		win->DrawString(5, 5 + y, msg);
	}
	while (true) {
		win->WaitMouseClick(x, y);
		if (1180 < x && x < 1300 && 680 < y && y < 750) {
			delete win;
			break;
		}
	}
	generateReport();
	return true;
}