#include <iostream>
#include <string>
#include <vector>

using namespace std;

enum class RideStatus { IDLE, CREATED, WITHDRAW, COMPLETED };

class Person {
public:
    string name;
};

class Ride {
private:
    int id;
    int origin, dest;
    int seats;
    RideStatus rideStatus;

public:
    static const int AMT_CHARGE = 20;
    Ride();
    int calculateFare(bool);
    int getId() const;
    void setId(int newId);
    int getOrigin() const;
    void setOrigin(int newOrigin);
    int getDest() const;
    void setDest(int newDest);
    int getSeats() const;
    void setSeats(int newSeats);
    RideStatus getRideStatus() const;
    void setRideStatus(RideStatus rideStatus);
};

class Rider : private Person {
private:
    vector<Ride> allRide;

public:
    Rider(string);
    void createRide(int, int, int, int);
    void updateRide(int, int, int, int);
    void withdrawRide(int);
    int closeRide(int);
};

Ride::Ride() {
    id = origin = dest = seats = 0;
    rideStatus = RideStatus::IDLE;
}

int Ride::calculateFare(bool isPriorityRider) {
    int dist = dest - origin;
    if (seats < 2) {
        return dist * AMT_CHARGE * (isPriorityRider ? 0.75 : 1);
    }
    return dist * seats * AMT_CHARGE * (isPriorityRider ? 0.5 : 0.75);
}

int Ride::getId() const {
    return id;
}

void Ride::setId(int newId) {
    id = newId;
}

int Ride::getOrigin() const {
    return origin;
}

void Ride::setOrigin(int newOrigin) {
    origin = newOrigin;
}

int Ride::getDest() const {
    return dest;
}

void Ride::setDest(int newDest) {
    dest = newDest;
}

int Ride::getSeats() const {
    return seats;
}

void Ride::setSeats(int newSeats) {
    seats = newSeats;
}

RideStatus Ride::getRideStatus() const {
    return rideStatus;
}

void Ride::setRideStatus(RideStatus newStatus) {
    rideStatus = newStatus;
}

Rider::Rider(string name) {
    this->name = name;
}

void Rider::createRide(int id, int origin, int dest, int seats) {
    if (origin >= dest) {
        cout << "Wrong Values of Origin and destination!";
        return;
    }
    Ride currentRide;
    currentRide.setId(id);
    currentRide.setOrigin(origin);
    currentRide.setDest(dest);
    currentRide.setSeats(seats);
    currentRide.setRideStatus(RideStatus::CREATED);
    allRide.push_back(currentRide);
}

void Rider::updateRide(int id, int origin, int dest, int seats) {
    for (auto& ride : allRide) {
        if (ride.getId() == id) {
            if (ride.getRideStatus() == RideStatus::WITHDRAW) {
                cout << "Can't update ride. Ride was Withdrawn";
            } else if (ride.getRideStatus() == RideStatus::COMPLETED) {
                cout << "Can't update ride. Ride was already Completed";
            } else {
                ride.setOrigin(origin);
                ride.setDest(dest);
                ride.setSeats(seats);
            }
            break;
        }
    }
}

void Rider::withdrawRide(int id) {
    auto iter = allRide.begin();
   
    for (; iter != allRide.end(); ++iter) {
        if (iter->getId() == id) {
            if (iter->getRideStatus() != RideStatus::CREATED) {
                cout << "Ride wasn't in progress. Can't Withdraw";
            } else {
                iter->setRideStatus(RideStatus::WITHDRAW);
                allRide.erase(iter); // Correctly remove the specific ride
            }
            break;
        }
    }
}

int Rider::closeRide(int id) {
    for (auto& ride : allRide) {
        if (ride.getId() == id) {
            if (ride.getRideStatus() != RideStatus::CREATED) {
                cout << "Ride wasn't in progress. Can't Close";
                return 0;
            }
            ride.setRideStatus(RideStatus::COMPLETED);
            return ride.calculateFare(allRide.size() >= 10);
        }
    }
    return 0;
}

  int main() {
      	cout << "******************** RIDE APPLICATION ******************" << endl;

   Rider rider("Lucifer");

    // Test Case Set 1
    rider.createRide(1, 500, 690, 4);
    rider.createRide(2, 100, 200, 2);
    rider.createRide(3, 300, 400, 3);

    rider.updateRide(2, 150, 250, 5);

    int fare1 = rider.closeRide(2);
    int fare2 = rider.closeRide(3);

    cout << "Fare for ride 2: " << fare1 << endl;
    cout << "Fare for ride 3: " << fare2 << endl;
    cout << "*****************************************************************" << endl;

    // Test Case Set 2
    rider.createRide(4, 200, 350, 2);
    rider.createRide(5, 50, 120, 5);
    rider.createRide(6, 600, 700, 1);

    int fare3 = rider.closeRide(4);
    int fare4 = rider.closeRide(5);

    cout << "Fare for ride 4: " << fare3 << endl;
    cout << "Fare for ride 5: " << fare4 << endl;
    	cout << "*****************************************************************" << endl;


    return 0;
}

