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
        void printManual();
        Attendance& att;
};

inline void printManual(){
    cout<<"#UI (att)"
        <<"d <date> : set date and start marking\n"
        <<"r : render into csv\n"
        <<"exit : exit application\n"
        <<"#\n"
        <<"#DateUI (<date>)\n"
        <<"rm <name> : unmark attendee by name\n"
        <<"l : lists all attendees\n"
        <<"m : prints marked attendees for each date\n"
        <<"clear : clears all marked entries for current date\n"
        <<"exit : switch to (att)\n"
    ;
}
#endif