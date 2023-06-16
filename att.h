#ifndef ATT_H
#define ATT_H
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <set>

using namespace std;

class Attendance{
    public:
        enum Action{
            MARK,
            UNMARK,
            UNAWARE
        };
        explicit Attendance(char* db_name, char* csv_file_name, bool validate) :
            db(db_name),
            csv(csv_file_name),
            allowValidation(validate)
            {init();}
        void init();
        bool isValidationEnabled();
        void validateAttendees();
        int setCountLadiesAndGents(int countLadies,int countGents);
        int setDate(string date);
        string getDate();
        void clearCurrentDate();
        void printMarkedAttendees();
        int getNametoId(const string& name);
        bool isValidAttendeeId(int attendeeId);
        int updateAttendance(int attendeeId,Action action);
        void render();
    private:
        vector<string> _mAttendees;
        vector<string> _mDate;
        vector<int> _mCountLadies;
        vector<int> _mCountGents;
        int _mCurrentDateId;
        vector<set<int>> _mMarkedAttendeeIds;
        char* db;
        char* csv;
        bool allowValidation;
};

string gatherStrFromStream(istringstream &iss);

inline bool Attendance::isValidationEnabled(){
    return allowValidation;
}

inline string Attendance::getDate(){
    return _mDate.at(_mCurrentDateId);
}

#endif 