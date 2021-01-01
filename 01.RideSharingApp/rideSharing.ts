class Person {
    protected name: string;
    constructor(name: string) {
        this.name = name;
    }
};

class Rider extends Person {
    constructor(name: string) {
        super(name);
    }
    private currentRide: Ride;
    private completedRides: Ride[] = [];

    createRide(id: number, origin: number, destination: number, seats: number) {
        if(origin >= destination) {
            console.error("Error! Destination must be greater than origin!");
            return;
        }
        this.currentRide = new Ride();
        this.currentRide.id = id;
        this.currentRide.origin = origin;
        this.currentRide.destination = destination;
        this.currentRide.rideStatus = RideStatus.CREATED;
    }

    updateRide(id: number, origin: number, destination: number, seats: number) {
        if(this.currentRide.rideStatus == RideStatus.WITHDRAWN) {
            console.error("Can't update the ride which is withdrawn");
            return;
        }
        if(this.currentRide.rideStatus == RideStatus.COMPLETE) {
            console.error("Can't update the ride which is complete");
            return;
        }

        this.createRide(id, origin, destination, seats);
    }

    withdrawRide(id: number) {
        if(id != this.currentRide.id) {
            console.log("Unknown ID");
            return;
        }
        if(this.currentRide.rideStatus != RideStatus.CREATED) {
            console.log("Can only withdraw a ride which is in progress!!");
            return;
        }
        this.currentRide.rideStatus = RideStatus.WITHDRAWN;
    }

    closeRide(): number {
        if(this.currentRide.rideStatus != RideStatus.CREATED) {
            console.log("Can only close a ride which is in progress!!");
            return 0;
        }
        this.currentRide.rideStatus = RideStatus.COMPLETE;
        this.completedRides.push(this.currentRide);
        return this.currentRide.calculateFare(this.completedRides.length >= 10);
    } 
};

class Driver extends Person {
    constructor(name: string) {
        super(name);
    }
};

enum RideStatus {CREATED, IDLE, WITHDRAWN, COMPLETE};

class Ride {
    static amountPerKM = 20;
    private _id: number;
    private _origin: number;
    private _destination: number;
    private _seats: number;
    private _rideStatus: RideStatus;
    constructor(){
        this._id = this._origin = this._destination = this._seats = 0;
        this._rideStatus = RideStatus.IDLE;
    }
    get id():number {
        return this._id;
    }
    set id(rideId: number) {
        this._id = rideId;
    }
    set origin(rideOrigin: number) {
        this._origin = rideOrigin;
    }
    set destination(rideDestination: number) {
        this._destination = rideDestination;
    }
    set seats(rideSeats: number) {
        this._seats = rideSeats;
    }
    get rideStatus():RideStatus {
        return this._rideStatus;
    }
    set rideStatus(status: RideStatus) {
        this._rideStatus = status;
    }
    calculateFare(isPrivileged: boolean): number {
        let distance = this._destination - this._origin; 
        if(this._seats >= 2) {
            return this._seats * distance * Ride.amountPerKM * (isPrivileged ? 0.5 : 0.75);
        }
        return distance * Ride.amountPerKM * (isPrivileged ? 0.75 : 1);
    }
};

function main() {
    let rider = new Rider('Lucifer');
    let driver = new Driver('Amenadeil');

}

main();