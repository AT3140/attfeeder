#include <cstdio>       
#include <sstream>
#include<cctype>
//#include <boost/algorithm/string/case_conv.hpp>


#include "att.h"

using namespace std;

void string_to_lowercase(string& target){
    for(int i=0;i<target.size();i++){
        target[i]=tolower(target[i]);
    }
}

void Attendance::init(){
    _mCurrentDateId=-1;
    char temp[256];
    ifstream ifs(db,ifstream::in);
    while(ifs){
    ifs.getline(temp,256);
    _mAttendees.push_back(string(temp)); 
    }
}

void Attendance::validateAttendees(){
    cout<<"No of Attendees: "<<_mAttendees.size()<<endl;
    cout<<"Listed Attendees: ";
    for(string name:_mAttendees){
            cout<<name<<" | ";
    }
    cout<<endl;
}

void Attendance::clearCurrentDate(){
    _mMarkedAttendeeIds[_mCurrentDateId].clear();    
    printf("%s cleared\n",_mDate[_mCurrentDateId].c_str());
}

bool Attendance::isValidAttendeeId(int attendeeId){
    if(attendeeId<0 || attendeeId>=_mAttendees.size()){
        return false;
    }
    else return true;
}

int Attendance::setCountLadiesAndGents(int countLadies, int countGents){
    _mCountLadies[_mCurrentDateId]=countLadies;
    _mCountGents[_mCurrentDateId]=countGents;
}

int Attendance::setDate(string date){
    string dateStr=string(date);
    for(int i=0;i<_mDate.size();i++){
        if(dateStr==_mDate[i]){
            _mCurrentDateId=i;
            return 0;
        }
    }
    _mDate.push_back(dateStr);
    _mMarkedAttendeeIds.push_back(set<int>());
    _mCountLadies.push_back(0);
    _mCountGents.push_back(0);
    _mCurrentDateId=_mDate.size()-1;
    return 0;
}

int Attendance::getNametoId(const string& name){
    istringstream is(name);
    vector<string> tokens_to_match;
    string temp;
    while(is>>temp){
        string_to_lowercase(temp);
        tokens_to_match.push_back(temp);
    }
    float best_match_index=0;
    int best_match_id=-1;
    for(int i=0;i<_mAttendees.size();i++){
        istringstream is_target(_mAttendees[i]); //input stream target
        int match=0;
        int total_tokens_in_target=0;
        float match_index=0;
        int is_match[tokens_to_match.size()]={0};
        while(is_target>>temp){
            string_to_lowercase(temp);
            total_tokens_in_target++;
            for(int j=0;j<tokens_to_match.size();j++){
                if(is_match[j]==0 && temp==tokens_to_match.at(j)){
                    is_match[j]=1;
                    match++;
                }
            }
        }
        match_index=(float)match/total_tokens_in_target;
        if(match_index>best_match_index){
            best_match_index=match_index;
            best_match_id=i;
        }
    }
    if(best_match_id>=0){
    }   
    return best_match_id;
}

int Attendance::updateAttendance(int attendeeId, Action action){
    if(_mCurrentDateId==-1){
        cerr<<"Date not set!";
        return -1;
    }
    else if(!isValidAttendeeId(attendeeId)){
        cerr<<"Attendee not found!";
        return -1;
    }
    else {
        if(action==MARK){
            _mMarkedAttendeeIds[_mCurrentDateId].insert(attendeeId);
            printf("%s\n",_mAttendees[attendeeId].c_str());
        }
        else if(action==UNMARK){
            _mMarkedAttendeeIds[_mCurrentDateId].erase(attendeeId);
            printf("%s unmarked\n",_mAttendees[attendeeId].c_str());
        }
        else{
            //do nothing
        }
        
        return 0;    
    }
}

void Attendance::render(){
    FILE *f = fopen(csv,"w");
    fprintf(f,"Name");
    int date_id=0;
    for(string dateStr:_mDate){
        if(_mMarkedAttendeeIds[date_id++].empty()){
                continue;
        }
        fprintf(f,",%s",dateStr.c_str());
    }
    for(int attendeeid=0;attendeeid<_mAttendees.size();attendeeid++){
        fprintf(f,"\n");
        string name=_mAttendees.at(attendeeid);
        fprintf(f,"%s",name.c_str());
        for(int dateid=0;dateid<_mDate.size();dateid++){
            if(_mMarkedAttendeeIds[dateid].empty()){
                continue;
            }
            if(_mMarkedAttendeeIds[dateid].find(attendeeid)!=_mMarkedAttendeeIds[dateid].end()){
                fprintf(f,",%d",1);
            }
            else
                fprintf(f,",");
        }
    }

    fprintf(f,"\nL:");
    for(int date_id=0;date_id<_mDate.size();date_id++){
        if(_mMarkedAttendeeIds[date_id].empty()){
                continue;
        }
        fprintf(f,",%d",_mCountLadies[date_id]);    
    }
    fprintf(f,"\nG:");
    for(int date_id=0;date_id<_mDate.size();date_id++){
        if(_mMarkedAttendeeIds[date_id].empty()){
                continue;
        }
        fprintf(f,",%d",_mCountGents[date_id]);    
    }
    fclose(f); 
}

void Attendance::printMarkedAttendees(){
    for(int date_id=0;date_id<_mDate.size();date_id++){
        if(_mMarkedAttendeeIds[date_id].empty()){
            continue;
        }
        cout<<"Date Id: "<<date_id;
        cout<<"\nDate: "<<_mDate[date_id];
        cout<<"\n";
        bool firstEntryPrinted=false;
        for(int id:_mMarkedAttendeeIds.at(date_id)){
            if(firstEntryPrinted){
                cout<<",";
            }
            else{
                firstEntryPrinted=true;
            }
            cout<<_mAttendees.at(id);
        }
        cout<<endl;
    }
}