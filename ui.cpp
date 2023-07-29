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
        printf("(%s) ",att.getSession().c_str());
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
        else if(command=="l"){
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
            att.setCountLadiesAndGents(stoi(countLadiesStr),stoi(countGentsStr));
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
            respondToDateCommand(iss);
            startDateUI();
        }
        else if(command=="l"){
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