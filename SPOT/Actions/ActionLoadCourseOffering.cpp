#include "ActionLoadCourseOffering.h"
#include <iostream>
using namespace std;

ActionLoadCourseOffering::ActionLoadCourseOffering(Registrar* p) :Action(p){

}

ActionLoadCourseOffering::~ActionLoadCourseOffering()
{}

bool ActionLoadCourseOffering::Execute() {
    char result[MAX_PATH];
    string str = string(result, GetModuleFileName(NULL, result, MAX_PATH));
    str = str.erase(str.length() - 18, 18);
    int ind = str.find("\\");
    while (ind != string::npos) {
        str.replace(ind, 1, "/");
        ind = str.find("\\");
    }
    string filepath = str+"SPOT/Files/CourseOffering.txt";
    ifstream finput(filepath);
    char* pch;
    char* context = nullptr;
    const int size = 500;
    char line[size];
    int index ;
    SEMESTER sem=FALL;
    AcademicYearOfferings year;
    while (finput.getline(line, size)){
        index=0;
        pch = strtok_s(line, ",", &context);
        year.Year = pch;
        while (pch != NULL) {
            if (index == 1) {
                sem = pReg->str2sem(pch);
                if (sem == SEM_CNT) {
                    pReg->getGUI()->PrintMsg("Error!!!! unknown Semester name in the file: " + string(pch));
                    Sleep(10000);
                    break;
                }
            }
            else if (index!=0) {
                //if (pReg->getCourseInfo(pReg->getRules(), pch).Code=="") {
                //   pReg->getGUI()->PrintMsg("Error!!!! unknown course in the file: " + string(pch));
                //   Sleep(10000);
                //}
                //else {
                    year.Offerings[sem].push_back(pch);
                //}
            }
            pch = strtok_s(NULL, ",", &context);
            index++;
        }
        pReg->getRules()->OfferingsList.push_back(year);
    }
    finput.close();
    return true;
}