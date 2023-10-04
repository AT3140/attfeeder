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

void UserInterface::respondToDateCommand(istringstream& is){
    string date=gatherStrFromStream(is);
    string title;
    cout<<"Active Sessions: ";
    set<int> activeSessionIds = att.getActiveSessionIds(date); 
    if(activeSessionIds.empty()){
        cout<<"--\n";
    }
    else {
        for(int id:activeSessionIds){
            string title = att.getSessionTitle(id);
            cout<<att.getSessionTitle(id)<<" ";
        }
        cout<<endl;
    }
    cout<<"Enter Session Title: ";
    cin>>title;
    fflush(stdin);
    att.setSession(date,title);
}

void UserInterface::startDateUI(){
    do{
        printf("(%s:%s) ",att.getCurrentSessionDate().c_str(),att.getCurrentSessionTitle().c_str());
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
            respondToDateCommand(is);
        }
        else if(command=="ls"){
            att.validateAttendees();
        }
        else if(command=="clear"){
            att.clearCurrentDate();
        }
        else if(command=="man"){
            printManual();
        }
        else if(command=="count"){
            string countLadiesStr="0",countGentsStr="0";
            is>>countLadiesStr; is>>countGentsStr;
	    try {
              att.setCountLadiesAndGents(stoi(countLadiesStr),stoi(countGentsStr));
	    }
	    catch(invalid_argument& e) {
	      cout<<"Only integers allowed!"<<endl;
	    }
        }    
        else { 
            string name="";
            int pid = -1;
            Attendance::Action action = Attendance::UNAWARE;
            if(command=="rm"){
                name = gatherStrFromStream(is);
                pid = att.getNametoId(name);
                action = Attendance::UNMARK;
            }
            else if(command=="register"){
                name=gatherStrFromStream(is);
                pid=att.registerAttendee(name);
                cout<<"Registered "<<endl;
                action = Attendance::UNAWARE;
            }
            else{
                name=command+" "+gatherStrFromStream(is);
                pid=att.getNametoId(name);
                if(att.isValidAttendeeId(pid)){
                    action = Attendance::MARK;
                }
                else {
                    action = Attendance::UNAWARE;
                    char response;
                    cout<<"Name Not Found!\n";
                    while(true){
                        cout<<"Register this Attendee? (y/n): ";
                        cin>>response;
                        fflush(stdin);
                        if(response == 'y') {
                            pid = att.registerAttendee(name);
                            action = Attendance::UNAWARE;
                            break;
                        }
                        else if(response == 'n') {
                            break;
                        }
                    }
                }
            }
            att.updateAttendance(pid,action); 
        }
    } while(true);
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
            respondToDateCommand(iss);
            startDateUI();
        }
        else if(command=="ls"){
            att.validateAttendees();
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
        else if(command=="exit"){
            break;
        }
        else{
            cout<<"unrecognized command... enter man to view manual\n";
        }
    }while(command!=string("exit"));
}
