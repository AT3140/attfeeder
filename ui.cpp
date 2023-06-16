//#include <boost/algorithm/string/trim.hpp>
#include "ui.h"

using namespace std;

string gatherStrFromStream(istringstream &iss){
    string str="";
    string token="";
    bool firstToken=true;
    while(iss>>token){
        if(firstToken){
            firstToken=false;
        }
        else{
            str+=" ";
        }
        str+=token;
    }
    return str;
}

void UserInterface::startDateUI(){
    do{
        printf("(%s) ",att.getDate().c_str());
        char cinput[256];
        cin.getline(cinput,256);
        string input(cinput);
        string command;
        istringstream is(input);
        is>>command;
        if(command=="exit"){
            break;
        }
        else if(command=="m"){
            att.printMarkedAttendees();
        }
        else if(command=="d"){
            string date=gatherStrFromStream(is);
            att.setDate(date);
        }
        else if(command=="l"){
            att.validateAttendees();
        }
        else if(command=="clear"){
            att.clearCurrentDate();
        }
        else if(command=="man"){
            printManual();
        }
        else{
            string name="";
            Attendance::Action action=Attendance::UNAWARE;
            if(command=="rm"){
                name=gatherStrFromStream(is);
                action=Attendance::UNMARK;
            }
            else{
                name=command+" "+gatherStrFromStream(is);
                action=Attendance::MARK;
            }
            int pid=att.getNametoId(name);
            if(pid>=0){
                att.updateAttendance(pid,action);
            }
            else cout<<"Name Not Found!\n";
        }
    }while(true);
}

void UserInterface::startUI(){
    char inputStr[256];
    string command="";
    string Args="";
    do{
        cout<<"(att) ";
        cin.getline(inputStr,256);
        istringstream iss(inputStr);
        iss>>command;
        if(command==string("d")){
            string date=gatherStrFromStream(iss);
            att.setDate(date);
            startDateUI();
        }
        else if(command=="m"){
            att.printMarkedAttendees();
        }
        else if(command=="man"){
            printManual();
        }
        else if(command=="r"){
            att.render();
        }
    }while(command!=string("exit"));
}