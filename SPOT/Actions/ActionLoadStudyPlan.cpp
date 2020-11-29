#include "ActionLoadStudyPlan.h"

ActionLoadStudyPlan::ActionLoadStudyPlan(Registrar* p) :Action(p)
{
}

bool ActionLoadStudyPlan::Execute() {
    string filepath = pReg->openfilename("Open Study Plan file");
    if (filepath != "") {
        pReg->clearStudyPlan();
        ifstream finput;
        finput.open(filepath);
        char* pch;
        char* context = nullptr;
        const int size = 100;
        char line[size];
        int index, year, x = 0, y = 85;
        SEMESTER sem = FALL;
        CourseInfo course;
        while (finput.getline(line, size)) {
            index = 0;
            y = 85;
            pch = strtok_s(line, ",", &context);
            year = pch[5] - '0';
            while (pch != NULL) {
                if (index == 1) {
                    sem = pReg->str2sem(pch);
                    if (sem==SEM_CNT) {
                        pReg->getGUI()->PrintMsg("Error!!!! unknown Semester name in the file: " + string(pch));
                        Sleep(8000);
                        break;
                    }
                }
                else if(index!=0){
                    //course = pReg->getCourseInfo(pReg->getRules(), pch);
                    //if (course.Code!="") {
                        Course* pC = new Course(pch, /*course.Title*/ "hi", 3 /*course.Credits*/);
                        switch (sem)
                        {
                        case FALL:
                            x = (year - 1) * 265 + 5;
                            break;
                        case SPRING:
                            x = (year - 1) * 265 + 90;
                            break;
                        case SUMMER:
                            x = (year - 1) * 265 + 175;
                            break;
                        default:
                            break;
                        }
                        graphicsInfo gInfo{ x, y };
                        pC->setGfxInfo(gInfo);
                        //StudyPlan* pS = 
                        pReg->getStudyPlan()->AddCourse(pC, year, sem);
                        //pS->AddCourse(pC, year, sem);
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
