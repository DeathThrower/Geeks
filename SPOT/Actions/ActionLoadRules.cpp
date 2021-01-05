#include "ActionLoadRules.h"
#include <fstream>

ActionLoadRules::ActionLoadRules(Registrar* p) :Action(p)
{
}

ActionLoadRules::~ActionLoadRules()
{
}

bool ActionLoadRules::Execute() {
    pReg->clearRules();
    Rules* myRules = pReg->getRules();

    //generate the file path      
    char result[MAX_PATH];
    string str = string(result, GetModuleFileName(NULL, result, MAX_PATH));
    str = str.erase(str.length() - 18, 18);
    int indx = str.find("\\");
    while (indx != string::npos) {
        str.replace(indx, 1, "/");
        indx = str.find("\\");
    }
    string filepath = str + "SPOT/Files/"+pReg->getStudyPlan()->getMajor()+"-Requirements.txt";

    //open the file and get the data from it. every case represent a line in the file and the default
    //represent the concentration courses  
	// see the file format if you need more details
    ifstream finput;
    finput.open(filepath);
    char* pch;
    char* context = nullptr;
    const int size = 410;
    char line[size];
    int mline = 0,index=0;
    while (finput.getline(line, size)) {
        index = 0;
        mline++;
        pch = strtok_s(line, ",", &context);
        switch (mline)
        {
        case 1:
            myRules->totalCredit = stoi(pch);
            break;
        case 2:
            myRules->ReqUnivCredits = stoi(pch);
            break;
        case 3:
            myRules->ReqTrackCredits = stoi(pch);
            break;
        case 4:
            myRules->ReqMajorCredits = stoi(pch);
            break;
        case 5:
            myRules->NumConcentration = stoi(pch);
            break;
        case 6:
            index++;
            while (pch != NULL) {
                if (index%2==1) {
                    myRules->ReqConCredits.push_back(stoi(pch));
                }
                pch = strtok_s(NULL, ",", &context);
                index++;
            }
            break;
        case 7:
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
            break;
        case 10:
            while (pch != NULL) {
                myRules->MajorCompulsory.push_back(pch);
                pch = strtok_s(NULL, ",", &context);
            }
            break;
        case 11:
            while (pch != NULL) {
                myRules->MajorElective.push_back(pch);
                pch = strtok_s(NULL, ",", &context);
            }
            break;
        default:
            if (mline%2==0) {
                vector<Course_Code> Cvec;
                while (pch != NULL) {
                    Cvec.push_back(pch);
                    pch = strtok_s(NULL, ",", &context);
                }
                myRules->ConCompulsory.push_back(Cvec);
            }
            else {
                vector<Course_Code> Evec;
                while (pch != NULL) {
                    Evec.push_back(pch);
                    pch = strtok_s(NULL, ",", &context);
                }
                myRules->ConElective.push_back(Evec);
            }
            break;
        }
    }
    return true;
}