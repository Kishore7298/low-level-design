#include<bits/stdc++.h>

using namespace std;

class Person {
    public:
    string name;
};

class Driver: private Person {
    Driver(string name) {
        this->name = name;
    }

};

class Rider: private Person {
    private: 
    vector<Ride> completedRides;
    Ride currentRide;

    public:
    Rider(string name) {
        this->name = name;
    }
    void createRide(int, int, int, int);
    void updateRide(int, int, int, int);
    void withdrawRide(int);
    int closeRide();
};

enum RideStatus {IDLE, CREATED, WITHDRAWN, COMPLETED };

class Ride {
    public:
    Ride(){
        id = origin = dest = seats = 0;
        rideStatus = RideStatus::IDLE;
    }
    static const int AMT_PER_KM = 20;   // Amount per kilometer
    int calculateFare(bool);    //boolean is to check if the user is previliged or not

    int getId()const;   // getter for Id
    void setId(int id); // setter for Id

    void setOrigin(int origin); //setter for origin

    void setDest(int dest); // setter for destination

    void setSeats(int seats); // setter for seats

    RideStatus getRideStatus(void)const; // getter for ride status
    void setRideStatus(RideStatus rideStatus); // setter for ride status


    private:
    int id; // ride id
    int origin;
    int dest;
    int seats;
    RideStatus rideStatus;
};
/************* Setter and Getters for Ride class *****************/
int Ride::getId() const {
    return id;
}
void Ride::setId(int id) {
    this->id = id;
}

void Ride::setOrigin(int origin) {
    this->origin = origin;
}

void Ride::setDest(int dest) {
    this->dest = dest;
}

void Ride::setSeats(int seats) {
    this->seats = seats;
}

RideStatus Ride::getRideStatus() const {
    return rideStatus;
}

void Ride::setRideStatus(RideStatus rideStatus) {
    this->rideStatus = rideStatus;
}
/************************************************************/

/*********** Functions from Ride class *********************/
int Ride::calculateFare(bool isPriorityRider) {
    int distance = dest - origin;
    if(seats >= 2) {
        return distance * AMT_PER_KM * seats * (isPriorityRider ? 0.5 : 0.75);
    }
    return distance * AMT_PER_KM * (isPriorityRider ? 0.75 : 1);
}
/***********************************************************/

/************ Functions of rider class *********************/
void Rider::createRide(int id, int origin, int destination, int seats) {
    if(origin >= destination) {
        cout<<"Error! Wrong parameters passes, origin can't be greater than destination!"<<endl;
        return;
    }
    currentRide.setId(id);
    currentRide.setOrigin(origin);
    currentRide.setDest(destination);
    currentRide.setSeats(seats);
    currentRide.setRideStatus(RideStatus::CREATED);
}

void Rider::updateRide(int id, int origin, int destination, int seats) {
    if(currentRide.getRideStatus() == RideStatus::WITHDRAWN) {
        cout<<"Can't update the withdrawn ride!"<<endl;
        return;
    }
    if(currentRide.getRideStatus() == RideStatus::COMPLETED) {
        cout<<"Can't update the completed ride!"<<endl;
        return;
    }
    createRide(id, origin, destination, seats);
}

void Rider::withdrawRide(int id) {
    if(id != currentRide.getId()) {
        cout<<"Unknown rider id"<<endl;
        return;
    }
    if(currentRide.getRideStatus() != RideStatus::CREATED) {
        cout<<"Ride wasn't in progress. Can't withdraw ride"<<endl;
        return;
    }
    currentRide.setRideStatus(RideStatus::WITHDRAWN);
}

int Rider::closeRide() {
    if(currentRide.getRideStatus() != RideStatus::CREATED) {
        cout<<"Can't close the ride which is not in progress!"<<endl;
        return 0;
    }
    currentRide.setRideStatus(RideStatus::COMPLETED);
    completedRides.push_back(currentRide);
    return currentRide.calculateFare(completedRides.size() >= 10);
}
/***********************************************************/

int main() {
    Rider* r = new Rider("kishore");

}