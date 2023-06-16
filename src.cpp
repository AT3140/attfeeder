#include <cstring>
#include <iostream>
#include <string.h>

#include "att.h"
#include "ui.h"

#define DEFAULT_CSV "abc.csv"

using namespace std;

int main(int argc,char *argv[]){
    char *db=NULL,*csv=NULL;
    bool validate=false;
    for(int i=1;i<argc;i++){
        if(string(argv[i-1])==string("-db")){
            db=argv[i];
        }
        else if(string(argv[i-1])==string("-csv")){
            csv=argv[i];
        }
        else if(string(argv[i])=="-v"){
            validate=true;
        }
        else continue;
    }
    if(!db){
        cout<<"\nDatabase not specified!";
        return -1;
    }
    if(!csv){
        //csv=DEFAULT_CSV;
    }

    Attendance att(db,csv,validate);
    UserInterface ui(att);
    if(att.isValidationEnabled()){
        att.validateAttendees();  
    } 
    ui.startUI();

    return 0;    
}