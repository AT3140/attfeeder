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
    char temp[256];
    string tempStr;
    ifstream ifs(db,ifstream::in);
    while(ifs){
        ifs.getline(temp,256);
        tempStr = string(temp);
        if(!tempStr.empty()){
            _mAttendees.push_back(string(temp)); 
        }
    }
}

int Attendance::registerAttendee(const string& name){
    _mAttendees.push_back(name);
    return _mAttendees.size() - 1;
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
    _mAttributes[_mCurrentAttributeId].markedAttendeeIds.clear();    
    printf("%s cleared\n",_mAttributes[_mCurrentAttributeId].date.c_str());
}

bool Attendance::isValidAttendeeId(int attendeeId){
    if(attendeeId<0 || attendeeId>=_mAttendees.size()){
        return false;
    }
    else return true;
}

int Attendance::setCountLadiesAndGents(int countLadies, int countGents){
    _mAttributes[_mCurrentAttributeId].countLadies=countLadies;
    _mAttributes[_mCurrentAttributeId].countGents=countGents;
}

void Attendance::adjustEmplaceAtIndex(int& index){
    if(index < _mAttributes.size() - 1){
        index++;
    }
}

void Attendance::setSession(const string& date, const string& title){
    int emplaceAtIndex = -1;
    for(int i=0;i<_mAttributes.size();i++){
        if((date == _mAttributes[i].date) && (title == _mAttributes[i].title)){
            _mCurrentAttributeId=i;
            return;
        }
        else if(date == _mAttributes[i].date){
            emplaceAtIndex = i;
        }
    }

    adjustEmplaceAtIndex(emplaceAtIndex);

    attribute currentAttribute;
    
    currentAttribute.date = date;
    currentAttribute.title = title;
    currentAttribute.markedAttendeeIds = set<int>();
    currentAttribute.countLadies = 0;
    currentAttribute.countGents = 0;

    if((emplaceAtIndex == -1) || (emplaceAtIndex == _mAttributes.size() - 1)){
        _mAttributes.push_back(currentAttribute);
        _mCurrentAttributeId = _mAttributes.size()-1;
    }
    else if((emplaceAtIndex>=0) && (emplaceAtIndex<_mAttributes.size())){
        _mAttributes.emplace(_mAttributes.begin()+emplaceAtIndex, currentAttribute);
        _mCurrentAttributeId = emplaceAtIndex;
    }
    else{
        cerr<<"emplaceAtIndex out of bounds";
        exit;
    }

}

const string& Attendance::getSessionTitle(int id){
    return _mAttributes[id].title;
}

set<int> Attendance::getActiveSessionIds(const string& date){
    set<int> ids;
    for(int i=0;i<_mAttributes.size();i++){
        if(_mAttributes[i].date == date){
            ids.insert(i);
        }
    }
    return ids;
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
    if(_mCurrentAttributeId==-1){
        cerr<<"Date not set!";
        return -1;
    }
    else {
        attribute& currentAttribute = _mAttributes[_mCurrentAttributeId];
        if(action==MARK){
            if(currentAttribute.markedAttendeeIds.find(attendeeId) != currentAttribute.markedAttendeeIds.end()) {
               printf("%s\nalready marked!\n",_mAttendees[attendeeId].c_str());
            }
            else {         
                if(isValidAttendeeId(attendeeId)) {    
                    currentAttribute.markedAttendeeIds.insert(attendeeId);
                    printf("%s\n",_mAttendees[attendeeId].c_str());
                }
            }
        }
        else if(action==UNMARK){
            currentAttribute.markedAttendeeIds.erase(attendeeId);
            printf("%s unmarked\n",_mAttendees[attendeeId].c_str());
        }
        else if(action==UNAWARE){
            //do nothing
        }
        
        return 0;    
    }
}

void Attendance::renderColumnHeads(FILE* f){
    fprintf(f,"Name");

    //dates
    for(int date_id=0; date_id<_mAttributes.size(); date_id++){
        if(!_mAttributes[date_id].markedAttendeeIds.empty()){
            fprintf(f,",%s",_mAttributes[date_id].date.c_str());
        }
    }
    
    //session types
    fprintf(f,"\n");
    for(int date_id=0; date_id<_mAttributes.size(); date_id++){
        if(!_mAttributes[date_id].markedAttendeeIds.empty()){
            fprintf(f,",%s",_mAttributes[date_id].title.c_str());
        }
    }

}

void Attendance::renderRecords(FILE* f){
    for(int attendeeid=0;attendeeid<_mAttendees.size();attendeeid++){
        fprintf(f,"\n");
        string name=_mAttendees.at(attendeeid);
        fprintf(f,"%s",name.c_str());
        for(int dateid=0;dateid<_mAttributes.size();dateid++){
            auto markedAttendeeIds = _mAttributes[dateid].markedAttendeeIds;
            if(!markedAttendeeIds.empty()){
                if(markedAttendeeIds.find(attendeeid) != markedAttendeeIds.end()){
                    fprintf(f,",%d",1);
                }
                else
                    fprintf(f,",");
            }
        }
    }
}

void Attendance::renderCounts(FILE* f){
    fprintf(f,"\nL:");
    for(int date_id=0;date_id<_mAttributes.size();date_id++){
        if(_mAttributes[date_id].markedAttendeeIds.empty()){
                continue;
        }
        fprintf(f,",%d",_mAttributes[date_id].countLadies);    
    }
    fprintf(f,"\nG:");
    for(int date_id=0;date_id<_mAttributes.size();date_id++){
        if(_mAttributes[date_id].markedAttendeeIds.empty()){
                continue;
        }
        fprintf(f,",%d",_mAttributes[date_id].countGents);    
    }
}

void Attendance::render(){
    FILE *f = fopen(csv,"w");

    renderColumnHeads(f);
    renderRecords(f);
    fprintf(f,"\n");
    renderCounts(f);

    fclose(f); 
}

void Attendance::printMarkedAttendees(){
    attribute currentAttribute = _mAttributes[_mCurrentAttributeId];
    if(currentAttribute.markedAttendeeIds.empty()){
        cout<<"--\n";
    }
    else {
        bool firstEntryPrinted=false;
        for(int id:currentAttribute.markedAttendeeIds){
            if(firstEntryPrinted){
                cout<<", ";
            }
            else{
                firstEntryPrinted=true;
            }
            cout<<_mAttendees.at(id);
        }
        cout<<endl;
    }
}