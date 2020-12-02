#include "ActionImportCatalog.h"
#include <algorithm>
#include <iostream>
ActionImportCatalog::ActionImportCatalog(Registrar* p) :Action(p)
{
}

bool ActionImportCatalog::Execute() {
    char result[MAX_PATH];
    string str = string(result, GetModuleFileName(NULL, result, MAX_PATH));
    str = str.erase(str.length() - 18, 18);
    int ind = str.find("\\");
    while (ind != string::npos) {
        str.replace(ind, 1, "/");
        ind = str.find("\\");
    }
    string filepath = str + "SPOT/Files/CourseCatalog.txt";
    //ifstream finput;
    //finput.open(filepath);
    ifstream finput(filepath);
    char* pch;
    char* context = nullptr;
    const int size = 500;
    char line[size];
    int index;
    CourseInfo course;
    while (finput.getline(line, size)) {
        index = 0;
        pch = strtok_s(line, ",", &context);
        while (pch != NULL) {
            switch (index)
            {
            case 0:
                course.Title = pch;
                break;
            case 1:
                course.Code = pch;
                break;
            case 2:
                course.Credits = stoi(pch);
                break;
            case 3:
                if (pch[0] == 'C') {
                    string coreq = pch;
                    coreq.erase(0 , 6);
                    std::string delimiter = " and ";
                    size_t pos = 0;
                    std::string token;
                    while ((pos = coreq.find(delimiter)) != std::string::npos) {
                        token = coreq.substr(0, pos);
                        course.CoReqList.push_back(token);
                        coreq.erase(0, pos + delimiter.length());
                    }
                    course.CoReqList.push_back(coreq);
                }
                else {
                    string prereq = pch;
                    prereq.erase(0, 7);
                    std::string delimiter = " and ";
                    size_t pos = 0;
                    std::string token;
                    while ((pos = prereq.find(delimiter)) != std::string::npos) {
                        token = prereq.substr(0, pos);
                        course.PreReqList.push_back(token);
                        prereq.erase(0, pos + delimiter.length());
                    }
                    course.PreReqList.push_back(prereq);
                }
                break;
            case 4:
                string prereq = pch;
                prereq.erase(0, 7);
                std::string delimiter = " and ";
                size_t pos = 0;
                std::string token;
                while ((pos = prereq.find(delimiter)) != std::string::npos) {
                    token = prereq.substr(0, pos);
                    course.PreReqList.push_back(token);
                    prereq.erase(0, pos + delimiter.length());
                }
                course.PreReqList.push_back(prereq);
                break;

            }
            pch = strtok_s(NULL, ",", &context);
            index++;
        }
        cout << "been calles and here is course data:" << course.Title << endl;
        pReg->getRules()->CourseCatalog.push_back(course);
    }
    finput.close();
    return true;
    

}


ActionImportCatalog::~ActionImportCatalog()
{
}
