#include "ActionLoadCourseOffering.h"
#include <iostream>
using namespace std;

ActionLoadCourseOffering::ActionLoadCourseOffering(Registrar* p) :Action(p){

}

ActionLoadCourseOffering::~ActionLoadCourseOffering()
{}

bool ActionLoadCourseOffering::Execute() {
    string filepath = pReg->openfilename();
    if (filepath != "") {
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
            pReg->getRules()->OffringsList.push_back(year);
        }
        finput.close();
        return true;
    }
    else {
        return false;
    }
}