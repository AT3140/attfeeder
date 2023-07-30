#ifndef ATT_H
#define ATT_H
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <set>

using namespace std;

typedef struct attribute {
    string date;
    string title;
    set<int> markedAttendeeIds;
    int countLadies;
    int countGents;
} attribute;

class Attendance{
    public:
        enum Action{
            MARK,
            UNMARK,
            UNAWARE
        };

        explicit Attendance(char* db_name, char* csv_file_name, bool validate) :
            _mCurrentAttributeId(-1),
            db(db_name),
            csv(csv_file_name),
            allowValidation(validate)
        {
            init(); 
        }

        void init();
        
        const string& getCurrentSessionDate();
        const string& getCurrentSessionTitle();
        const string& getSessionTitle(int id); 
        set<int> getActiveSessionIds(const string& date); 

        bool isValidationEnabled();
        void validateAttendees();
        int setCountLadiesAndGents(int countLadies,int countGents);
        void setSession(const string& date, const string& title); 
        void clearCurrentDate();
        void printMarkedAttendees();
        int getNametoId(const string& name);
        bool isValidAttendeeId(int attendeeId);
        int updateAttendance(int attendeeId,Action action);
        int registerAttendee(const string& name);

        void render();
    
    private:
        void renderColumnHeads(FILE* f);
        void renderRecords(FILE* f);
        void renderCounts(FILE* f);

        void adjustEmplaceAtIndex(int& index); //TODO: called in setSession

    private:
        vector<attribute> _mAttributes;
        vector<string> _mAttendees;
        int _mCurrentAttributeId;
        char* db;
        char* csv;
        bool allowValidation;
};

string gatherStrFromStream(istringstream &iss);

inline bool Attendance::isValidationEnabled(){
    return allowValidation;
}

inline const string& Attendance::getCurrentSessionDate(){
    return _mAttributes.at(_mCurrentAttributeId).date;
}

inline const string& Attendance::getCurrentSessionTitle(){
    return _mAttributes.at(_mCurrentAttributeId).title;
}

#endif 