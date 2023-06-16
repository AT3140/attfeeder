#ifndef UI_H
#define UI_H
#include <iostream>
#include <string>
#include <sstream>
//#include <boost/algorithm/string/trim.hpp>

#include "att.h"

using namespace std;

class UserInterface{
    public:
        explicit UserInterface(Attendance& attendance):
            att(attendance)
            {}
        void startUI();
    private:
        void startDateUI();
        Attendance& att;
};

#endif