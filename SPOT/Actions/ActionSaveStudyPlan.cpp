#include "ActionSaveStudyPlan.h"

string ActionSaveStudyPlan::savefilename(char* filter, HWND owner) const {
	OPENFILENAME ofn;
	char fileName[MAX_PATH] = ".txt";
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = owner;
	ofn.lpstrFilter = filter;
	ofn.lpstrFile = fileName;
	ofn.nMaxFile = MAX_PATH;
	ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
	ofn.lpstrDefExt = "";
	string fileNameStr;
	if (GetSaveFileName(&ofn)) {
		fileNameStr = fileName;
	}
	return fileNameStr;
}

ActionSaveStudyPlan::ActionSaveStudyPlan(Registrar* p) :Action(p)
{
}

bool ActionSaveStudyPlan::Execute() {
	int y=0;
	string filepath = savefilename();
	if (filepath!="") {
		ofstream outdata;
		outdata.open(filepath,ios::trunc);
		pReg->getStudyPlan()->saveStudyPlan(outdata);
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
