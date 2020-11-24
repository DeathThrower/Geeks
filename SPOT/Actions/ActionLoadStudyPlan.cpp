#include "ActionLoadStudyPlan.h"

ActionLoadStudyPlan::ActionLoadStudyPlan(Registrar* p) :Action(p)
{
}

bool ActionLoadStudyPlan::Execute() {
    string filepath = pReg->openfilename();
    if (filepath != "") {
        ifstream finput(filepath);
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
                }
                else if(index!=0){
                    //course = pReg->getCourseInfo(pReg->getRules(), pch);
                    Course* pC = new Course(pch, /*course.Title*/ "hi", 3 /*course.Credits*/);
                    switch (sem)
                    {
                    case FALL:
                        x = (year-1) * 265 +5;
                        break;
                    case SPRING:
                        x = (year-1) * 265 + 90;
                        break;
                    case SUMMER:
                        x = (year-1) * 265 + 175;
                        break;
                    default:
                        break;
                    }
                    graphicsInfo gInfo{ x, y };
                    pC->setGfxInfo(gInfo);
                    StudyPlan* pS = pReg->getStudyPlay();
                    pS->AddCourse(pC, year, sem);
                    y += 45;
                }

                pch = strtok_s(NULL, ",", &context);
                index++;
            }
        }
        return true;
    }
}


ActionLoadStudyPlan::~ActionLoadStudyPlan()
{
}
