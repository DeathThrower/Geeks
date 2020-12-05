#include "ActionLoadStudyPlan.h"
#include <fstream>

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
        pReg->getStudyPlan()->setMajor(pReg->str2maj(major));

        //open the file and get the data from it 
        ifstream finput;
        finput.open(filepath);
        char* pch;
        char* context = nullptr;
        const int size = 100;
        char line[size];
        int index, year, x = 0, y;
        SEMESTER sem = FALL;
        CourseInfo course;
        while (finput.getline(line, size)) {
            index = 0;
            y = 215;
            pch = strtok_s(line, ",", &context);
            year = pch[5] - '0';
            while (pch != NULL) {
                if (index == 1) {
                    //error checking if the file has a wrong semester name
                    sem = pReg->str2sem(pch);
                    if (sem==SEM_CNT) {
                        pReg->getGUI()->PrintMsg("Error!!!! unknown Semester name in the file: " + string(pch));
                        Sleep(8000);
                        break;
                    }
                }
                else if(index!=0){
                    //error checking if the file has a wrong course code
                    //course = pReg->getCourseInfo(pch);
                    //if (course.Code!="") {
                        Course* pC = new Course(pch, /*course.Title*/ "hi", 3 /*course.Credits*/);
                        switch (sem)
                        {
                        case FALL:
                            x = (year - 1) * 263 + 20;
                            break;
                        case SPRING:
                            x = (year - 1) * 263 + 106;
                            break;
                        case SUMMER:
                            x = (year - 1) * 263 + 194;
                            break;
                        default:
                            break;
                        }
                        graphicsInfo gInfo{ x, y };
                        pC->setGfxInfo(gInfo);
                        //pC->setPreReq(course.PreReqList);
                        //pC->setCoReq(course.CoReqList);
                        //pC->setType(pReg->getCourseType(course.Code));
                        pReg->getStudyPlan()->AddCourse(pC, year, sem);
                        y += 45;
                    //}
                    //else {
                    //    pReg->getGUI()->PrintMsg("Error!!!! unknown course in the file: "+string(pch));
                    //    Sleep(8000);
                    //}
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
