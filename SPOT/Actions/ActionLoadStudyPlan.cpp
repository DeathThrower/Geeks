#include "ActionLoadStudyPlan.h"
#include "ActionLoadRules.h"
#include <fstream>

////funciton that opens file selection window to let the user chose the path of file to open it
string ActionLoadStudyPlan::openfilename(string title, char* filter, HWND owner) const {
    OPENFILENAME ofn;
    char fileName[MAX_PATH] = "";
    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(OPENFILENAME);
    ofn.hwndOwner = owner;
    ofn.lpstrFilter = filter;
    ofn.lpstrFile = fileName;
    ofn.nMaxFile = MAX_PATH;
    ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
    ofn.lpstrDefExt = "";
    ofn.lpstrTitle = title.c_str();
    string fileNameStr = "";
    if (GetOpenFileName(&ofn)) {
        fileNameStr = fileName;
    }
    return fileNameStr;
}

ActionLoadStudyPlan::ActionLoadStudyPlan(Registrar* p) :Action(p)
{
}

bool ActionLoadStudyPlan::Execute() {
    string filepath = openfilename("Open Study Plan file");
    if (filepath != "") {
        pReg->getStudyPlan()->clearStudyPlan();

        //setting the major from the file path of file
        string major = filepath.substr(filepath.find("Files") + 6, filepath.find("StudyPlan") - filepath.find("Files") - 7);
        //pReg->getStudyPlan()->setMajor(pReg->str2maj(major));
        pReg->getStudyPlan()->setMajor(major);
        ActionLoadRules(pReg).Execute();
        //open the file and get the data from it 
        ifstream finput;
        finput.open(filepath);
        char* pch;
        char* context = nullptr;
        const int size = 100;
        char line[size];
        int index, year, x = 0, y=0;   // represent the index of the line each "," is a separate between 2 indexes
        SEMESTER sem = FALL;
        CourseInfo course;
        while (finput.getline(line, size)) {
            index = 0;
            y = 215;
            pch = strtok_s(line, ",", &context);
            year = pch[5] - '0';   // for the first index of the line get the year
            while (pch != NULL) {
                if (index == 1) {

                    sem = pReg->str2sem(pch); // from the second index of line get the semester

                    //error checking if the file has a wrong semester name if so return false and clear studyplan
                    if (sem==SEM_CNT) {
                        pReg->getGUI()->PrintMsg("Error!!!! unknown Semester name in the file: " + string(pch));
                        Sleep(5000);
                        pReg->getStudyPlan()->clearStudyPlan();
                        return false;
                    }
                }
                else if(index!=0){
                    //error checking if the file has a wrong course code and get the course info
                    course = pReg->getCourseInfo(pch);   //get the course info of the course according to the course code gotten from the user
                    if (course.Code!="") {
                        Course* pC = new Course(pch, course.Title, course.Credits);
                        x = (year - 1) * 263 + 20 + static_cast<int>(sem) * 88;  // get the x coordinate of the course from the year and semester
						//setting everything in the new course corresponding to the course gotten from getCourseInfo funtion
                        graphicsInfo gInfo{ x, y };
                        pC->setGfxInfo(gInfo);
                        pC->setPreReq(course.PreReqList);
                        pC->setCoReq(course.CoReqList);
                        pC->setType(pReg->getCourseType(course.Code));
                        pReg->getStudyPlan()->AddCourse(pC, year, sem);
                        y += 45;  // at every new course update the y coordinates of course 
                    }
                    else {
                        pReg->getGUI()->PrintMsg("Error!!!! unknown course in the file: "+string(pch));
                        Sleep(5000);
                        pReg->getStudyPlan()->clearStudyPlan();
                        return false;
                    }
                }

                pch = strtok_s(NULL, ",", &context);
                index++;
            }
        }
        finput.close();
        return true;
    }
    else {
        return false;
    }
}


ActionLoadStudyPlan::~ActionLoadStudyPlan()
{
}
