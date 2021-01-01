#include<bits/stdc++.h>

using namespace std;

class Meeting;

/******************* Room Class *********************************/
typedef unordered_map<int, vector<Meeting>> Calander;
class Room {
    string name;
    Calander calander;
    public:
    Room(string name) {
        this->name = name;
    }
    const string getName();
    bool book(int day, int start, int end);
};

const string Room::getName() {
    return name;
}

/*****************************************************************/

/******************** Meeting **********************************/
class Meeting {
    public:
        Meeting(int start, int end, Room room):room(room) {
            this->start = start;
            this->end = end;
        }
        int getEnd();
        int getStart();
    private:
        int start, end;
        Room room;
};
int Meeting::getStart() {
    return start;
}
int Meeting::getEnd() {
    return end;
}
/****************************************************************/

bool Room::book(int day, int start, int end) {  // This function is kept seperate to access Meeting.
    for(Meeting &m: calander[day]) {
        if(m.getStart() < end && start < m.getEnd())
            return false;
    }
    Meeting meeting(start, end, *this);
    calander[day].push_back(meeting);

    return true;
}

/************************ Scheduler ******************************/
// This acts as an interface to book the rooms
class Scheduler {
    private:
    vector<Room> rooms;

    public:
    Scheduler(vector<Room> rooms) {
        this->rooms = rooms;
    }
    string book(int day, int start, int end) {   // This functions returns the name of the booked room.
        for(Room &room: rooms) {
            bool booked = room.book(day, start, end);
            if(booked) return room.getName();
        }
        return "No Available rooms at the moment!!";
    }
};
/*****************************************************************/

int main() {
    Room room1("Atlas");
    Room room2("Nexus");
    Room room3("HolyCow");

    Scheduler scheduler({ room1, room2, room3 });

    cout<<scheduler.book(1, 2, 5)<<endl;   // Atlas
    cout<<scheduler.book(1, 5, 8)<<endl;   // Atlas
    cout<<scheduler.book(1, 4, 8)<<endl;   // Nexus
    cout<<scheduler.book(1, 3, 6)<<endl;   // HolyCow
    cout<<scheduler.book(1, 7, 8)<<endl;   // HolyCow
    cout<<scheduler.book(1, 7, 8)<<endl;   // No Available rooms at the moment
    return 0;
}

