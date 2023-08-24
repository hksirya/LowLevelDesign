#include <bits/stdc++.h>
using namespace std;

class Meeting;
typedef vector<Meeting> Calender;

class Room {
    string name;
    Calender calender;
    
public:
    Room(string name) {
        this->name = name;
    }
    
    // Setter for name
    void setName(string newName) {
        name = newName;
    }
    
    // Getter for name
    string getName() const {
        return name;
    }
    
    bool bookRoom(int start, int end) {
        
        for(auto &it:calender){
            if(it.getEndTime()>=start && it.getStartTime()<=end){
                return false;
            }
        }
        
        Meeting meeting(start, end, *this);
        calender.push_back(meeting);
        
        return true;
    }
};

class Meeting {
    int start;
    int end;
    Room& room; // Change from Room room to Room& room
    
public:
    Meeting(int start, int end, Room& room) : room(room) {
        this->start = start;
        this->end = end;
    }
    
    // Setter for start time
    void setStartTime(int newStart) {
        start = newStart;
    }
    
    // Getter for start time
    int getStartTime() const {
        return start;
    }
    
    // Setter for end time
    void setEndTime(int newEnd) {
        end = newEnd;
    }
    
    // Getter for end time
    int getEndTime() const {
        return end;
    }
};


class Scheduler {
    vector<Room> room;
    
public:
    Scheduler(vector<Room>&room) {
        this->room = room;
    }
    
    string scheduleMeeting(int start, int end) {
        for (auto &it : room) {
            bool flag = it.bookRoom(start, end);
            if (flag == true) {
                return it.getName();
            }
        }   
       return "No Room Available, Try Later";
    }
};

int main() {
    Room room("Conference Room 1");
    vector<Room> rooms = {room};
    Scheduler scheduler(rooms);

    string meetingRoom = scheduler.scheduleMeeting(9, 11);
    if (meetingRoom != "No Room Available, Try Later") {
        cout << "Meeting booked in: " << meetingRoom << endl;
    } else {
        cout << "No available rooms for the meeting." << endl;
    }

    return 0;
}
