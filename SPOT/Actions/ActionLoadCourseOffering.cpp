#include "ActionLoadCourseOffering.h"
#include <fstream>

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
    int index ;  // represent the index of the line each "," is a separate between 2 indexes
    SEMESTER sem=FALL;
    AcademicYearOfferings year;
    while (finput.getline(line, size)){
        index=0;
        pch = strtok_s(line, ",", &context);
        year.Year = pch;  //assign the year (2020/2021) to the academic year from the first index of the line
        while (pch != NULL) {
            if (index == 1) {
                sem = pReg->str2sem(pch);  //get the semester from the second index of the line 
                if (sem == SEM_CNT) {
                    pReg->getGUI()->PrintMsg("Error!!!! unknown Semester name in the file: " + string(pch));
                    Sleep(5000);
                    break;
                }
            }
            else if (index!=0) {
                //if (pReg->getCourseInfo(pch).Code=="") {
                //   pReg->getGUI()->PrintMsg("Error!!!! unknown course in the file: " + string(pch));
                //   Sleep(10000);
                //}
                //else {
                    year.Offerings[sem].push_back(pch);  // for the indexes other than 0 or 1 the indexes represent the courses and it will be added to the academic year
                //}
            }
            pch = strtok_s(NULL, ",", &context);
            index++;
        }
        pReg->getRules()->OfferingsList.push_back(year);  // add the academic year to the offeringlist of the rules
    }
    finput.close();
    return true;
}