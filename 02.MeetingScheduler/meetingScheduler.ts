class Meeting {
    private _startTime: number;
    private _endTime: number;
    private _room: Room;
    constructor(startTime, endTime, room) {
        this._startTime = startTime;
        this._endTime = endTime;
        this._room = room;
    }
    get startTime(): number {
        return this._startTime;
    }
    get endTime(): number {
        return this._endTime;
    }
};

class Room {
    private _name: string;
    private calander: {[day: number]: Meeting[]};
    constructor(name: string) {
        this._name = name;
        this.calander = {};
    }
    get name(): string {
        return this._name;
    }
    book(day: number, start: number, end: number):boolean {
        if(this.calander[day] == undefined) 
            this.calander[day] = [];
        for(let meeting of this.calander[day]) {
            if(meeting.startTime < end && meeting.endTime > start)
                return false;
        }
        let m = new Meeting(start, end, this);
        this.calander[day].push(m);
        return true;
    }
};

class Scheduler {
    private rooms:Room[];
    constructor(rooms: Room[]) {
        this.rooms = rooms;
    }
    book(day: number, start: number, end: number): string {
        for(let room of this.rooms) {
            if(room.book(day, start, end))
                return room.name;
        }
        return "No rooms available at the moment!!";
    }
};


function main() {
    let room1 = new Room("Atlas");
    let room2 = new Room("Nexus");
    let room3 = new Room("HolyCow");

    let scheduler = new Scheduler([ room1, room2, room3]);

    console.log(scheduler.book(1, 2, 5));   // Atlas
    console.log(scheduler.book(1, 5, 8));   // Atlas
    console.log(scheduler.book(1, 4, 8));   // Nexus
    console.log(scheduler.book(1, 3, 6));   // HolyCow
    console.log(scheduler.book(1, 7, 8));   // HolyCow
    console.log(scheduler.book(2, 7, 8));   // No Available rooms at the moment
}

main();