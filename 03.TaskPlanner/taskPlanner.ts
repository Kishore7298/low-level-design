class Sprint {
    private _name: string;
    private _begin: number;
    private _end: number;
    private _tasks: Task[];
    constructor(begin: number, end: number, name: string) {
        this._name = name;
        this._begin = begin;
        this._end = end;
        this._tasks = [];
    }
    get name() { 
        return this._name
    };

    get begin() {
        return this._begin;
    }

    get end() {
        return this._end;
    }

    addTask(task:Task) {
        this._tasks.push(task);
    }
    removeTask(task: Task) {
        for(let t of this._tasks) {
            if(t == task) {
                this._tasks = this._tasks.filter(tsk => tsk == task);
                return true;
            }
        }
        return false;
    }
    printDetails() {
        console.log("Sprint name: ", this._name);
        console.log(`Sprint begin: ${this._begin}, Sprint end: ${this._end}`);
    }
};

enum TaskType { STORY, BUG, FEATURE };
enum TaskStatus { OPENED, IN_PROGRESS, RESOLVED, DELAYED, COMPLETED };

class Task {
    private _id: number;
    private _subtract: string;
    private _taskType: TaskType;
    private _taskStatus: TaskStatus;
    private _user: User;
    static taskId = 1;
    constructor() {
        this._id = Task.generateId();
        this._taskStatus = TaskStatus.OPENED;
        if(Task.taskId == undefined)
            Task.taskId = 1;
    }
    static generateId() {
        return this.taskId++;
    }
    get id() {
        return this._id;
    }
    set subtract(s:string) {
        this._subtract = s;
    }
    set taskType(t: TaskType) {
        this._taskType = t;
    }
    set taskStatus(t: TaskStatus) {
        this._taskStatus = t;
    }
    set user(u: User) {
        this._user = u;
    }
};

class User {
    private sprints: Sprint[];
    private tasks: Task[];
    constructor() {
        this.sprints = [];
        this.tasks = [];
    }
    createSprint(begin: number, end: number, name: string) {
        let sprint = new Sprint(begin, end, name);
        this.sprints.push(sprint);
        return sprint;
    }

    createTask(elem: TaskType | string) {
        let task = new Task();
        task.user = this;
        if(typeof elem == "string") {
            task.taskType = TaskType.STORY;
            task.subtract = elem;
            this.tasks.push(task);
            return task;
        } else {
            if(elem == TaskType.STORY) {
                console.log("Warning! Creating task without a subtract!!");
            }
            task.taskType = elem;
            this.tasks.push(task);
            return task;
        }
    }

    addToSprint(sprint: Sprint, task: Task) {
        for(let spr of this.sprints) {
            if(spr == sprint) {
                sprint.addTask(task);
                return true;
            }
        }
        return false;
    }

    removeFromSprint(sprint: Sprint, task: Task) {
        for(let spr of this.sprints) {
            if(spr == sprint) {
                return sprint.removeTask(task);
            }
        }
        return false;
    }

    printAllTasks() {
        console.log("---------------------------------------");
        for(let task of this.tasks) {
            console.log(`${task.id} `);
        }
        console.log("---------------------------------------");
    }

    changeStatus(task:Task, taskStatus: TaskStatus) {
        for(let tsk of this.tasks) {
            if(tsk == task) {
                task.taskStatus = taskStatus;
                return true;
            }
        }
        return false;
    }
};

function main() {
    let user1 = new User();
    let user2 = new User();

    let task1 = user1.createTask(TaskType.FEATURE);
    let task11 = user1.createTask(TaskType.BUG);

    let task2 = user2.createTask(TaskType.BUG);
    let task22 = user2.createTask("This is a subtract!!");

    let sprint1 = user1.createSprint(22, 33, "Sprint1");
    let sprint2 = user2.createSprint(44, 55, "sprint2");

    user1.changeStatus(task1, TaskStatus.IN_PROGRESS);

    console.log(user1.addToSprint(sprint1, task1));
	console.log(user1.addToSprint(sprint1, task11));
	console.log(user1.addToSprint(sprint2, task1));
	console.log(user1.removeFromSprint(sprint1, task11));
	console.log(user2.addToSprint(sprint1, task1));
	console.log(user2.removeFromSprint(sprint1, task2));
	console.log(user2.addToSprint(sprint2, task1));
    console.log(user2.addToSprint(sprint2, task2));
    
    sprint1.printDetails();
	user1.printAllTasks();
	user2.printAllTasks();
}

main();