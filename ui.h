#ifndef UI_H
#define UI_H
#include <iostream>
#include <string>
#include <set>
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
        void respondToDateCommand(istringstream& is);
        void printManual();
        Attendance& att;
};

inline void UserInterface::printManual(){
    cout<<"  #UI (att)\n"
        <<"  d <date>\t: set date and switch to DateUI\n"
        <<"  r\t\t: render\n"
        <<"  l\t\t: lists all attendees\n"
        <<"  man\t\t: print manual\n"
        <<"  exit\t\t: exit application\n"
        <<"\n"
        <<"  #DateUI (<date>)\n"
        <<"  <name>\t\t: mark attendee by name\n"
        <<"  rm <name>\t: unmark attendee by name\n"
        <<"  count <ladies> <gents> : set count\n"
        <<"  m\t\t: prints marked attendees for each date\n"
        <<"  clear\t\t: clears all marked entries for current date\n"
        <<"  l\t\t: lists all attendees\n"
        <<"  man\t\t: print manual\n"
        <<"  exit\t\t: switch to (att)\n";
}
#endif